#import <Cocoa/Cocoa.h>

namespace google_breakpad
{
    class ReceivePort;
}

@interface LauncherAppDelegate : NSObject <NSApplicationDelegate>
- (id) initWithReceivePort:(google_breakpad::ReceivePort*)port;
@end