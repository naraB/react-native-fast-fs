#import <React/RCTBridgeModule.h>
#import "react-native-fast-fs.h"

@interface FastFs : NSObject <RCTBridgeModule>

@property (nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
