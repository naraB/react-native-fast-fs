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
                                                               jsi::PropNameID::forAscii(jsiRuntime, "__readDirectory"),
                                                               1,
                                                               [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                   if(!arguments[0].isString()) {
                                                                       jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                   }
                                                                   
                                                                   string directoryPath = arguments[0].asString(runtime).utf8(runtime);
                                                                   fs::path dir = fs::path(directoryPath);
                                                                   
                                                                   if(!fs::is_directory(dir)) {
                                                                       jsi::detail::throwJSError(runtime, "Path is not a directory");
                                                                   }
                                                                   
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
    jsiRuntime.global().setProperty(jsiRuntime, "__readDirectory", move(readDirectory));
    
    auto readFile = jsi::Function::createFromHostFunction(
                                                               jsiRuntime,
                                                               jsi::PropNameID::forAscii(jsiRuntime, "__readFile"),
                                                               1,
                                                               [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                   if(!arguments[0].isString()) {
                                                                       jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                   }
                                                                   
                                                                   // TODO: Add encoding
                                                                   
                                                                   string file = arguments[0].asString(runtime).utf8(runtime);
                                                                   fs::path filePath = fs::path(file);
                                                                   
                                                                   if (!fs::is_regular_file(filePath)) {
                                                                       jsi::detail::throwJSError(runtime, "Provided path is not a file");
                                                                   }
                                                                   
                                                                   if(!fs::exists(filePath)) {
                                                                       jsi::detail::throwJSError(runtime, "File does not exist");
                                                                   }
                                                                   
                                                                   /* TODO: Throw exception if file does not have read permission
                                                                   if(!fs::permissions(filePath, )) {
                                                                       jsi::detail::throwJSError(runtime, "You don't have read permissions");
                                                                   }
                                                                    */
                                                                   
                                                                   fs::ifstream t(filePath);
                                                                   t.seekg(0, std::ios::end);
                                                                   size_t size = t.tellg();
                                                                   std::string buffer(size, ' ');
                                                                   t.seekg(0);
                                                                   t.read(&buffer[0], size);
                                                                   
                                                                   return jsi::String::createFromUtf8(runtime, buffer);
                                                               }
                                                               );
    jsiRuntime.global().setProperty(jsiRuntime, "__readFile", move(readFile));
    
    auto writeFile = jsi::Function::createFromHostFunction(
                                                               jsiRuntime,
                                                               jsi::PropNameID::forAscii(jsiRuntime, "__writeFile"),
                                                               1,
                                                               [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                   if(!arguments[0].isString()) {
                                                                       jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                   }
                                                                   
                                                                   // TODO: Check if 2nd and 3rd arguments are of correct type
                                                                   
                                                                   string directoryPath = arguments[0].asString(runtime).utf8(runtime);
                                                                   fs::path dir = fs::path(directoryPath);
                                                                   if(fs::exists(dir)) {
                                                                       jsi::detail::throwJSError(runtime, "File or directory already exists");
                                                                   }
                                                                   
                                                                   
                                                                   
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
                                                                   
                                                                   return jsi::Value().undefined();
                                                               }
                                                               );
    jsiRuntime.global().setProperty(jsiRuntime, "__writeFile", move(writeFile));
    
}
