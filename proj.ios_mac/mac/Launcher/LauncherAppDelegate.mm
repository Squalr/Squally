// mild reimplementation of crash_generation_server.cc that better integrates with Cocoa

#import "LauncherAppDelegate.h"
#import "AFNetworking/AFNetworking.h"

#include "client/mac/crash_generation/client_info.h"
#include "client/mac/handler/minidump_generator.h"
#include "common/mac/MachIPC.h"
#include "common/mac/scoped_task_suspend-inl.h"

#include "Config.h"

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

// expose private placeholder string
@interface NSTextView (Placeholder)
@property(nonatomic) NSAttributedString *placeholderAttributedString;
@end

@interface LauncherAppDelegate ()
{
    google_breakpad::ReceivePort* gameExceptionPort;
    dispatch_source_t gameExceptionSource;
    dispatch_source_t gameExitSource;
}
@property(strong) AFURLSessionManager* sessionManager;
@property BOOL gameCrashed;
@end

@implementation LauncherAppDelegate

#pragma mark - Constructors

// initialize crash monitor with a receive port to monitor for crashes
- (id) initWithReceivePort:(google_breakpad::ReceivePort*)port
{
    self = [super init];
    if (self)
    {
        self.gameCrashed = NO;
        gameExceptionPort = port;
    }
    return self;
}

#pragma mark - Crash Report Helpers

// capture crash report from game
- (NSURL*)captureCrashReport
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
    NSURL* crashReportPath = nil;
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
        NSURL *cachePath = [[NSFileManager defaultManager].temporaryDirectory URLByAppendingPathComponent:@"com.squalr.squally"];
        crashReportPath = [cachePath URLByAppendingPathComponent:[[NSUUID UUID].UUIDString stringByAppendingString:@".dmp"]];
        [[NSFileManager defaultManager] createDirectoryAtURL:cachePath
                                 withIntermediateDirectories:YES
                                                  attributes:nil
                                                       error:nil];
        // write crash dump
        result = generator.Write([crashReportPath.path UTF8String]);
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
- (void)uploadCrashReport:(NSURL*)path
{
    // user entry text field
    NSTextView* textView = [[NSTextView alloc] initWithFrame:CGRectMake(0, 0, 275, 100)];
    NSColor *txtColor = [NSColor grayColor];
    NSDictionary *txtDict = [NSDictionary dictionaryWithObjectsAndKeys:txtColor, NSForegroundColorAttributeName, nil];
    textView.placeholderAttributedString = [[NSAttributedString alloc]
            initWithString:@"Please describe what you were doing when Squally crashed?"
            attributes:txtDict];

    // show alert box
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"Yes"];
    [alert addButtonWithTitle:@"No"];
    [alert setMessageText:@"Squally crashed out of the Vapor Web and his head exploded"];
    [alert setInformativeText:@"Mr Muskrat will be cleaning the walls for weeks, can you send us a bug report so we can keep this from happening again?"];
    [alert setAlertStyle:NSWarningAlertStyle];
    [alert setAccessoryView:textView];

    // if user doesn't want to send report, bail
    if ([alert runModal] != NSAlertFirstButtonReturn) {
        [NSApp terminate:self];
        return;
    }

    // build send form for crash report
    void (^formBuilder)(id<AFMultipartFormData>) = ^(id<AFMultipartFormData> formData)
    {
        [formData appendPartWithFileURL:path name:@"minidump" fileName:[path lastPathComponent]
                mimeType:@"application/octet-stream" error:nil];
    };

    // build url request
    NSDictionary* parameters = @{
        @"app-version" : [NSString stringWithFormat:@"%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH],
        @"platform-version" : [NSProcessInfo processInfo].operatingSystemVersionString,
        @"platform" : @"macos",
        @"report" : [textView.textStorage string]
    };

    NSMutableURLRequest* request = [[AFHTTPRequestSerializer serializer]
           multipartFormRequestWithMethod:@"POST"
           URLString:@"https://squallygame.com/api/v1/crashreport"
           parameters:parameters
           constructingBodyWithBlock:formBuilder
           error:nil];

    // completion handler
    void (^completionHandler)(NSURLResponse* _Nonnull, id _Nullable, NSError* _Nonnull) =
            ^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error)
    {
        if (error) {
            NSLog(@"crash report upload error: %@", error);
        }
        [NSApp terminate:self];
    };

    // start upload
    [[self.sessionManager uploadTaskWithStreamedRequest:request progress:nil
            completionHandler:completionHandler] resume];
}

#pragma mark - NSApplicationDelegate Implementation

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    return NSTerminateNow;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    // start afnetworking
    self.sessionManager = [[AFURLSessionManager alloc] initWithSessionConfiguration:
            [NSURLSessionConfiguration defaultSessionConfiguration]];

    // exit when game process exits
    gameExitSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGCHLD, 0, dispatch_get_main_queue());
    dispatch_source_set_event_handler(gameExitSource, ^
    {
        if (!self.gameCrashed) {
            [NSApp terminate:self];
        }
    });

    // capture and upload crash report when we receive a crash event from the game
    gameExceptionSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_MACH_RECV, gameExceptionPort->GetPort(),
            0, dispatch_get_global_queue(QOS_CLASS_UTILITY, 0));
    dispatch_source_set_event_handler(gameExceptionSource, ^
    {
        // flag that the game crashed to sigchld doesn't kill the process
        self.gameCrashed = YES;

        // get the crash report, and upload it
        NSURL* crashReportPath = [self captureCrashReport];
        NSLog(@"crash report generated: %@", crashReportPath);
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
    NSLog(@"application will terminate.");
}

@end
