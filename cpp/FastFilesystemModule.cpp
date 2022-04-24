#include "FastFilesystemModule.h"
#include "filesystem.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "JSIUtils.hpp"

#include <iostream>
#include <sstream>
#include <string>


namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

void install(jsi::Runtime& jsiRuntime) {
    
    installDirectoryFunctions(jsiRuntime);
    installFileFunctions(jsiRuntime);
    
    auto exists = jsi::Function::createFromHostFunction(
                                                        jsiRuntime,
                                                        jsi::PropNameID::forAscii(jsiRuntime, "exists"),
                                                        1, // path
                                                        [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                            if(!arguments[0].isString()) {
                                                                jsi::detail::throwJSError(runtime, "Path is not a string");
                                                            }
                                                            
                                                            string path = arguments[0].asString(runtime).utf8(runtime);
                                                            fs::path filePath = fs::path(path);
                                                            
                                                            bool exists = fs::exists(filePath);
                                                            return jsi::Value(exists);
                                                        }
                                                        );
    jsiRuntime.global().setProperty(jsiRuntime, "exists", move(exists));
    
   
    
}


