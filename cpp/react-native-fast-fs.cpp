#include "react-native-fast-fs.h"
#include "filesystem.hpp"

#include <iostream>
#include <sstream>


namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

void install(jsi::Runtime &jsiRuntime) {
    auto readDirectory = jsi::Function::createFromHostFunction(
                                                               jsiRuntime,
                                                               jsi::PropNameID::forAscii(jsiRuntime, "readDirectory"),
                                                               1, // path
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
    jsiRuntime.global().setProperty(jsiRuntime, "readDirectory", move(readDirectory));
    
    auto readFile = jsi::Function::createFromHostFunction(
                                                          jsiRuntime,
                                                          jsi::PropNameID::forAscii(jsiRuntime, "readFile"),
                                                          1, // path
                                                          [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                              if(!arguments[0].isString()) {
                                                                  jsi::detail::throwJSError(runtime, "Path is not a string");
                                                              }
                                                              
                                                              // TODO: Add encoding arg
                                                              
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
                                                              
                                                              try {
                                                                  fs::ifstream ifs(filePath);
                                                                  ifs.seekg(0, std::ios::end);
                                                                  size_t size = ifs.tellg();
                                                                  std::string buffer(size, ' ');
                                                                  ifs.seekg(0);
                                                                  ifs.read(&buffer[0], size);
                                                                  ifs.close();
                                                                  return jsi::String::createFromUtf8(runtime, buffer);
                                                              } catch (...) {
                                                                  jsi::detail::throwJSError(runtime, "Content read file");
                                                              }
                                                              
                                                              return jsi::Value().undefined();
                                                          }
                                                          );
    jsiRuntime.global().setProperty(jsiRuntime, "readFile", move(readFile));
    
    auto writeFile = jsi::Function::createFromHostFunction(
                                                           jsiRuntime,
                                                           jsi::PropNameID::forAscii(jsiRuntime, "writeFile"),
                                                           2, // path, content
                                                           [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                               if(!arguments[0].isString()) {
                                                                   jsi::detail::throwJSError(runtime, "Path is not a string");
                                                               }
                                                               
                                                               if (!arguments[1].isString()) {
                                                                   jsi::detail::throwJSError(runtime, "File content is not a string");
                                                               }
                                                               
                                                               string content = arguments[1].asString(runtime).utf8(runtime);
                                                               string file = arguments[0].asString(runtime).utf8(runtime);
                                                               fs::path filePath = fs::path(file);
                                                               
                                                               /*
                                                               bool fileCreationSuccess = fs::create_directory(filePath);
                                                               if (!fileCreationSuccess) {
                                                                   jsi::detail::throwJSError(runtime, "Directory could not be created");
                                                               }
                                                                */
                                                               
                                                               try {
                                                                   fs::ofstream ofs(filePath);
                                                                   ofs.write(&content[0], content.size());
                                                                   ofs.close();
                                                               } catch (...) {
                                                                   jsi::detail::throwJSError(runtime, "Content could not be written to file");
                                                               }
                                                               
                                                               return jsi::Value(true);
                                                           }
                                                           );
    jsiRuntime.global().setProperty(jsiRuntime, "writeFile", move(writeFile));
    
}
