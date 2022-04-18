#include "react-native-fast-fs.h"
#include "filesystem.hpp"

#include <iostream>
#include <sstream>


namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

class File {
public:
    string filename;
};


void install(jsi::Runtime &jsiRuntime) {
    auto readDirectory = jsi::Function::createFromHostFunction(
                                                               jsiRuntime,
                                                               jsi::PropNameID::forAscii(jsiRuntime, "readDirectory"),
                                                               1,
                                                               [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                   if(!arguments[0].isString()) {
                                                                       jsi::detail::throwJSError(runtime, "Directory path is not a string");
                                                                   }
                                                                   
                                                                   string directoryName = arguments[0].asString(runtime).utf8(runtime);
                                                                   fs::path dir = fs::path(directoryName);
                                                                   
                                                                   auto files = vector<fs::directory_entry>();
                                                                   for (auto de : fs::directory_iterator(dir)) {
                                                                       files.emplace_back(de);
                                                                   }
                                                                   
                                                                   auto result = jsi::Array(runtime, files.size());
                                                                   for (int i = 0; i < files.size(); i++)
                                                                   {
                                                                       // TODO: Add lastModified
                                                                       auto file = jsi::Object(runtime);
                                                                       auto name = jsi::String::createFromUtf8(runtime, files[i].path().filename().string());
                                                                       auto size = jsi::Value((int)files[i].file_size());
                                                                       auto path = jsi::String::createFromUtf8(runtime, files[i].path().string());
                                                                       auto isFile = jsi::Value(files[i].is_regular_file());
                                                                       auto isDirectory = jsi::Value(files[i].is_directory());
                                                                       file.setProperty(runtime, "name", name);
                                                                       file.setProperty(runtime, "size", size);
                                                                       file.setProperty(runtime, "path", path);
                                                                       file.setProperty(runtime, "isFile", isFile);
                                                                       file.setProperty(runtime, "isDirectory", isDirectory);
                                                                       result.setValueAtIndex(runtime, i, move(file));
                                                                   }
                                                                   
                                                                   return result;
                                                               }
                                                               );
    
    jsiRuntime.global().setProperty(jsiRuntime, "readDirectory", move(readDirectory));
}
