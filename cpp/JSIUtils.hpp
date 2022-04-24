//
//  JSIUtils.hpp
//  react-native-fast-fs
//
//  Created by Baran Yildirim on 24.04.22.
//

#ifndef JSIUtils_hpp
#define JSIUtils_hpp

#include <stdio.h>
#import <jsi/jsi.h>

using namespace facebook;

struct Promise {
    Promise(jsi::Runtime &rt, jsi::Function resolve, jsi::Function reject);

    void resolve(const jsi::Value &result);
    void reject(const std::string &error);

    jsi::Runtime &runtime_;
    jsi::Function resolve_;
    jsi::Function reject_;
};

using PromiseSetupFunctionType =
std::function<void(jsi::Runtime &rt, std::shared_ptr<Promise>)>;
jsi::Value createPromiseAsJSIValue(
                                   jsi::Runtime &rt,
                                   const PromiseSetupFunctionType func);

#endif /* JSIUtils_hpp */
