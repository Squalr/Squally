// mild reimplementation of crash_generation_server.cc that better integrates with Cocoa

#import "LauncherAppDelegate.h"

#include "client/mac/crash_generation/client_info.h"
#include "client/mac/handler/minidump_generator.h"
#include "common/mac/MachIPC.h"
#include "common/mac/scoped_task_suspend-inl.h"

// forward declare some structures so we don't have to include large headers
namespace google_breakpad
{
    enum
    {
        kDumpRequestMessage     = 1,
        kAcknowledgementMessage = 2,
        kQuitMessage            = 3
    };

    struct ExceptionInfo
    {
        int32_t exception_type;
        int32_t exception_code;
        int32_t exception_subcode;
    };
}

@interface LauncherAppDelegate ()
{
    google_breakpad::ReceivePort* gameExceptionPort;
    dispatch_source_t gameExceptionSource;
    dispatch_source_t gameExitSource;
}
@end

@implementation LauncherAppDelegate

#pragma mark - Constructors

// initialize crash monitor with a receive port to monitor for crashes
- (id) initWithReceivePort:(google_breakpad::ReceivePort*)port
{
    self = [super init];
    if (self)
    {
        gameExceptionPort = port;
    }
    return self;
}

#pragma mark - Crash Report Helpers

// capture crash report from game
- (NSString*)captureCrashReport
{
    // get message
    google_breakpad::MachReceiveMessage message;
    kern_return_t result = gameExceptionPort->WaitForMessage(&message, MACH_MSG_TIMEOUT_NONE);
    if (result != KERN_SUCCESS)
    {
        NSLog(@"failed to read mach message!");
        return nil;
    }

    google_breakpad::ExceptionInfo& info = (google_breakpad::ExceptionInfo&) *message.GetData();
    mach_port_t remoteTask = message.GetTranslatedPort(0);
    mach_port_t crashingThread = message.GetTranslatedPort(1);
    mach_port_t handlerThread = message.GetTranslatedPort(2);
    mach_port_t acknowledgePort = message.GetTranslatedPort(3);
    
    pid_t remotePid = -1;
    pid_for_task(remoteTask, &remotePid);
    google_breakpad::ClientInfo client(remotePid);

    // generate dump
    NSString* crashReportPath = nil;
    {
        google_breakpad::ScopedTaskSuspend suspend(remoteTask);
        google_breakpad::MinidumpGenerator generator(remoteTask, handlerThread);
        if (info.exception_type && info.exception_code)
        {
            generator.SetExceptionInformation(info.exception_type,
                    info.exception_code, info.exception_subcode,
                    crashingThread);
        }

        // generate crash dump path
        NSString *cachePath = [[NSFileManager defaultManager].temporaryDirectory.path
                stringByAppendingPathComponent:@"com.squalr.squally"];
        crashReportPath = [cachePath stringByAppendingPathComponent:[[NSUUID UUID].UUIDString stringByAppendingString:@".dmp"]];
        [[NSFileManager defaultManager] createDirectoryAtPath:cachePath
                                  withIntermediateDirectories:YES
                                                   attributes:nil
                                                        error:nil];
        // write crash dump
        result = generator.Write([crashReportPath UTF8String]);
    }

    // acknowledge game, tell it to exit
    if (acknowledgePort != MACH_PORT_DEAD && acknowledgePort != MACH_PORT_NULL)
    {
        google_breakpad::MachPortSender sender(acknowledgePort);
        google_breakpad::MachSendMessage acknowledgement(google_breakpad::kAcknowledgementMessage);
        const mach_msg_timeout_t kSendTimeoutMs = 2 * 1000;
        sender.SendMessage(acknowledgement, kSendTimeoutMs);
    }
    return crashReportPath;
}

// schedule an upload for a crash report
- (void)uploadCrashReport:(NSString*)path
{
    // show alert box
    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
    [alert addButtonWithTitle:@"Yes"];
    [alert addButtonWithTitle:@"No"];
    [alert setMessageText:@"Squally crashed out of the Vapor Web and his head exploded"];
    [alert setInformativeText:@"Mr Muskrat will be cleaning the walls for weeks, can you send us a bug report so we can keep this from happening again?"];
    [alert setAlertStyle:NSWarningAlertStyle];

    // use the result
    if ([alert runModal] == NSAlertFirstButtonReturn)
    {
        NSLog(@"TODO implement upload for: %@", path);
    } 
}

#pragma mark - NSApplicationDelegate Implementation

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    return NSTerminateNow;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    // called when the game process exits
    gameExitSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGCHLD, 0, dispatch_get_main_queue());
    dispatch_source_set_event_handler(gameExitSource, ^
    {
        // in theory we should check whether or not operations are still pending
        [NSApp terminate:self];
    });

    // capture and upload crash report when we receive a crash event from the game
    gameExceptionSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_MACH_RECV, gameExceptionPort->GetPort(),
            0, dispatch_get_global_queue(QOS_CLASS_UTILITY, 0));
    dispatch_source_set_event_handler(gameExceptionSource, ^
    {
        NSString* crashReportPath = [self captureCrashReport];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self uploadCrashReport:crashReportPath];
        });
    });

    // start event sources
    dispatch_resume(gameExitSource);
    dispatch_resume(gameExceptionSource);
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
}

@end
