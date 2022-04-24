#import "FastFs.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <jsi/jsi.h>
#import "FastFilesystemModule.h"


using namespace facebook;
@implementation FastFs

RCT_EXPORT_MODULE()
//
//+ (BOOL)requiresMainQueueSetup {
//    return YES;
//}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
    RCTBridge* bridge = [RCTBridge currentBridge];
    
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)bridge;
    if (cxxBridge == nil) {
        NSLog(@"Could not install react-native-fast-fs.");
        return @false;
    }
    
    auto jsiRuntime = (jsi::Runtime*) cxxBridge.runtime;
    if (jsiRuntime == nil) {
        return @false;
    }
    auto& runtime = *jsiRuntime;
    install(runtime);
    
    return @true;
}

@end
