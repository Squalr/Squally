#include "LauncherAppDelegate.h"
#include "common/mac/MachIPC.h"

#include <unistd.h>
#include <memory>

int main(int argc, char * argv[])
{
    @autoreleasepool
    {
        // find game executable
        NSString *executable = [[NSBundle mainBundle] pathForAuxiliaryExecutable:@"Squally"];
        if (!executable)
        {
            NSLog(@"[Squally Launcher] failed to find squally executable");
            return EXIT_FAILURE;
        }

        // unique session name
        NSString* uniqueName = [NSUUID UUID].UUIDString;
        std::unique_ptr<google_breakpad::ReceivePort> receivePort(
                new google_breakpad::ReceivePort([uniqueName UTF8String]));

        // run game
        pid_t childId = fork();
        if(!childId)
        {
            return execl([executable UTF8String], [executable UTF8String], "-d", [uniqueName UTF8String], nullptr);
        }
        else if (childId < 0)
        {
            NSLog(@"[Squally Launcher] failed to fork game process.");
            return EXIT_FAILURE;
        }

        // run crash watcher app (start as accessory so no dock item is present)
        [[NSApplication sharedApplication] setDelegate:[[LauncherAppDelegate alloc] initWithReceivePort:receivePort.get()]];
        [[NSApplication sharedApplication] setActivationPolicy:NSApplicationActivationPolicyAccessory];
        [[NSApplication sharedApplication] run];
    }
    return EXIT_SUCCESS;
}