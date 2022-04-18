#import "FastFs.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <Foundation/Foundation.h>
#import "react-native-fast-fs.h"

@implementation FastFs

@synthesize bridge= _bridge;
@synthesize methodQueue = _methodQueue;

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup {
  return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
  _bridge = bridge;
  _setBridgeOnMainQueue = RCTIsMainQueue();

  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
  if (!cxxBridge.runtime) {
    return;
  }

  install(*(facebook::jsi::Runtime *)cxxBridge.runtime);
}

@end
