//
//  Directory.cpp
//  react-native-fast-fs
//
//  Created by Baran Yildirim on 24.04.22.
//

#include "Directory.hpp"
#include "filesystem.hpp"
#include "JSIUtils.hpp"

#include <string>


namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

void installDirectoryFunctions(jsi::Runtime& rt) {
    auto readDirectorySync = jsi::Function::createFromHostFunction(
                                                                   rt,
                                                                   jsi::PropNameID::forAscii(rt, "readDirectorySync"),
                                                                   1, // path
                                                                   [](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                       if(!arguments[0].isString()) {
                                                                           jsi::detail::throwJSError(rt, "Path is not a string");
                                                                       }
                                                                       
                                                                       string directoryPath = arguments[0].asString(rt).utf8(rt);
                                                                       fs::path dir = fs::path(directoryPath);
                                                                       
                                                                       if(!fs::is_directory(dir)) {
                                                                           jsi::detail::throwJSError(rt, "Path is not a directory");
                                                                       }
                                                                       
                                                                       auto files = vector<fs::directory_entry>();
                                                                       for (auto de : fs::directory_iterator(dir)) {
                                                                           files.emplace_back(de);
                                                                       }
                                                                       
                                                                       auto result = jsi::Array(rt, files.size());
                                                                       for (int i = 0; i < files.size(); i++)
                                                                       {
                                                                           // TODO: Add lastModified and created
                                                                           auto file = jsi::Object(rt);
                                                                           auto name = jsi::String::createFromUtf8(rt, files[i].path().filename().string());
                                                                           auto size = jsi::Value((int)files[i].file_size());
                                                                           auto path = jsi::String::createFromUtf8(rt, files[i].path().string());
                                                                           auto isFile = jsi::Value(files[i].is_regular_file());
                                                                           auto isDirectory = jsi::Value(files[i].is_directory());
                                                                           file.setProperty(rt, "name", name);
                                                                           file.setProperty(rt, "size", size);
                                                                           file.setProperty(rt, "path", path);
                                                                           file.setProperty(rt, "isFile", isFile);
                                                                           file.setProperty(rt, "isDirectory", isDirectory);
                                                                           result.setValueAtIndex(rt, i, move(file));
                                                                       }
                                                                       
                                                                       return result;
                                                                   }
                                                                   );
    rt.global().setProperty(rt, "readDirectorySync", move(readDirectorySync));
    
    auto readdirSync = jsi::Function::createFromHostFunction(
                                                             rt,
                                                             jsi::PropNameID::forAscii(rt, "readdirSync"),
                                                             1, // path
                                                             [](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                 if(!arguments[0].isString()) {
                                                                     jsi::detail::throwJSError(rt, "Path is not a string");
                                                                 }
                                                                 
                                                                 string directoryPath = arguments[0].asString(rt).utf8(rt);
                                                                 fs::path dir = fs::path(directoryPath);
                                                                 
                                                                 if(!fs::is_directory(dir)) {
                                                                     jsi::detail::throwJSError(rt, "Path is not a directory");
                                                                 }
                                                                 
                                                                 auto files = vector<fs::directory_entry>();
                                                                 for (auto de : fs::directory_iterator(dir)) {
                                                                     files.push_back(de);
                                                                 }
                                                                 
                                                                 auto result = jsi::Array(rt, files.size());
                                                                 for (int i = 0; i < files.size(); i++)
                                                                 {
                                                                     auto name = jsi::String::createFromUtf8(rt, files[i].path().filename().string());
                                                                     result.setValueAtIndex(rt, i, move(name));
                                                                 }
                                                                 
                                                                 return result;
                                                             }
                                                             );
    rt.global().setProperty(rt, "readdirSync", move(readdirSync));
    
    auto mkdirSync = jsi::Function::createFromHostFunction(
                                                           rt,
                                                           jsi::PropNameID::forAscii(rt, "mkdirSync"),
                                                           2, // path, recursive
                                                           [](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                               if(!arguments[0].isString()) {
                                                                   jsi::detail::throwJSError(rt, "Path is not a string");
                                                               }
                                                               
                                                               if(!arguments[1].isBool()) {
                                                                   jsi::detail::throwJSError(rt, "Param recursive is not a boolean");
                                                               }
                                                               
                                                               bool recursive = arguments[1].getBool();
                                                               string directoryPath = arguments[0].asString(rt).utf8(rt);
                                                               fs::path dir = fs::path(directoryPath);
                                                               
                                                               if(fs::exists(dir)) {
                                                                   jsi::detail::throwJSError(rt, "Directory or file at path already exists");
                                                               }
                                                               
                                                               bool status = false;
                                                               try {
                                                                   if (recursive) {
                                                                       status = fs::create_directories(dir);
                                                                   } else {
                                                                       status = fs::create_directory(dir);
                                                                   }
                                                               } catch (...) {
                                                                   jsi::detail::throwJSError(rt, "Could not create directory");
                                                               }
                                                               return jsi::Value(status);
                                                           }
                                                           );
    rt.global().setProperty(rt, "mkdirSync", move(mkdirSync));
}


