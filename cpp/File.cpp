//
//  File.cpp
//  react-native-fast-fs
//
//  Created by Baran Yildirim on 24.04.22.
//

#include "File.hpp"
#include "filesystem.hpp"
#include "JSIUtils.hpp"


#include <string>

namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

void installFileFunctions(jsi::Runtime& rt) {
    auto readFile = jsi::Function::createFromHostFunction(
                                                          rt,
                                                          jsi::PropNameID::forAscii(rt, "readFile"),
                                                          2, // path, encoding
                                                          [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                              if(!arguments[0].isString()) {
                                                                  jsi::detail::throwJSError(runtime, "Path is not a string");
                                                              }
                                                              
                                                              if(!arguments[1].isString()) {
                                                                  jsi::JSError(runtime, "Encoding is not a string");
                                                              }
                                                              
                                                              string encoding = arguments[1].asString(runtime).utf8(runtime);
                                                              
                                                              if (encoding != "utf8" && encoding != "base64") {
                                                                  jsi::JSError(runtime, "Encoding is neither utf8 nor base64");
                                                              }
                                                              
                                                              string file = arguments[0].asString(runtime).utf8(runtime);
                                                              fs::path filePath = fs::path(file);
                                                              
                                                              if(!fs::exists(filePath)) {
                                                                  jsi::detail::throwJSError(runtime, "File does not exist");
                                                              }
                                                              
                                                              if (!fs::is_regular_file(filePath)) {
                                                                  jsi::detail::throwJSError(runtime, "Provided path is not a file");
                                                              }
                                                              
                                                              // TODO: Throw exception if file does not have read permission
                                                              fs::perms permissions = fs::status(filePath).permissions();
                                                              std::string result;
                                                              result.reserve(9);
                                                              for (int i = 0; i < 9; ++i) {
                                                                  result = ((static_cast<int>(permissions) & (1 << i)) ? "xwrxwrxwr"[i] : '-') + result;
                                                              }
                                                              
                                                              //cout << result << endl;
                                                              
                                                              
                                                              //cout << static_cast<int>(permissions) << endl;
                                                              
                                                              
                                                              /*
                                                               if(!fs::permissions(filePath, )) {
                                                               jsi::detail::throwJSError(runtime, "You don't have read permissions");
                                                               }
                                                               */
                                                              
                                                              try {
                                                                  fs::ifstream ifs(filePath);
                                                                  ifs.seekg(0, ios::end);
                                                                  size_t size = ifs.tellg();
                                                                  string buffer(size, ' ');
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
    rt.global().setProperty(rt, "readFile", move(readFile));
    
    auto read = jsi::Function::createFromHostFunction(
                                                          rt,
                                                          jsi::PropNameID::forAscii(rt, "read"),
                                                          2, // path, encoding
                                                          [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                              if(!arguments[0].isString()) {
                                                                  jsi::detail::throwJSError(runtime, "Path is not a string");
                                                              }
                                                              
                                                              if(!arguments[1].isString()) {
                                                                  jsi::JSError(runtime, "Encoding is not a string");
                                                              }
                                                              
                                                              string encoding = arguments[1].asString(runtime).utf8(runtime);
                                                              
                                                              if (encoding != "utf8" && encoding != "base64") {
                                                                  jsi::JSError(runtime, "Encoding is neither utf8 nor base64");
                                                              }
                                                              
                                                              string file = arguments[0].asString(runtime).utf8(runtime);
                                                              fs::path filePath = fs::path(file);
                                                              
                                                              if(!fs::exists(filePath)) {
                                                                  jsi::detail::throwJSError(runtime, "File does not exist");
                                                              }
                                                              
                                                              if (!fs::is_regular_file(filePath)) {
                                                                  jsi::detail::throwJSError(runtime, "Provided path is not a file");
                                                              }
                                                              
                                                              // TODO: Throw exception if file does not have read permission
                                                              fs::perms permissions = fs::status(filePath).permissions();
                                                              std::string result;
                                                              result.reserve(9);
                                                              for (int i = 0; i < 9; ++i) {
                                                                  result = ((static_cast<int>(permissions) & (1 << i)) ? "xwrxwrxwr"[i] : '-') + result;
                                                              }
                                                              
                                                              //cout << result << endl;
                                                              
                                                              
                                                              //cout << static_cast<int>(permissions) << endl;
                                                              
                                                              
                                                              /*
                                                               if(!fs::permissions(filePath, )) {
                                                               jsi::detail::throwJSError(runtime, "You don't have read permissions");
                                                               }
                                                               */
                                                              
                                                              try {
                                                                  fs::ifstream ifs(filePath);
                                                                  ifs.seekg(0, ios::end);
                                                                  size_t size = ifs.tellg();
                                                                  string buffer(size, ' ');
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
    rt.global().setProperty(rt, "read", move(read));
    
    auto readFileAsync = jsi::Function::createFromHostFunction(
                                                               rt,
                                                               jsi::PropNameID::forAscii(rt, "readFileAsync"),
                                                               2, // path, encoding
                                                               [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                   if(!arguments[0].isString()) {
                                                                       jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                   }
                                                                   
                                                                   if(!arguments[1].isString()) {
                                                                       jsi::JSError(runtime, "Encoding is not a string");
                                                                   }
                                                                   
                                                                   string encoding = arguments[1].asString(runtime).utf8(runtime);
                                                                   string file = arguments[0].asString(runtime).utf8(runtime);
                                                                   
                                                                   return createPromiseAsJSIValue(runtime, [file, encoding](jsi::Runtime &rt, std::shared_ptr<Promise> promise) {
                                                                       
                                                                       if (encoding != "utf8" && encoding != "base64") {
                                                                           jsi::detail::throwJSError(rt, "Encoding is neither utf8 nor base64");
                                                                       }
                                                                       
                                                                       fs::path filePath = fs::path(file);
                                                                       
                                                                       if(!fs::exists(filePath)) {
                                                                           jsi::detail::throwJSError(rt, "File does not exist");
                                                                       }
                                                                       
                                                                       if (!fs::is_regular_file(filePath)) {
                                                                           jsi::detail::throwJSError(rt, "Provided path is not a file");
                                                                       }
                                                                       
                                                                       // TODO: Throw exception if file does not have read permission
                                                                       fs::perms permissions = fs::status(filePath).permissions();
                                                                       std::string result;
                                                                       result.reserve(9);
                                                                       for (int i = 0; i < 9; ++i) {
                                                                           result = ((static_cast<int>(permissions) & (1 << i)) ? "xwrxwrxwr"[i] : '-') + result;
                                                                       }
                                                                       
                                                                       try {
                                                                           fs::ifstream ifs(filePath);
                                                                           ifs.seekg(0, ios::end);
                                                                           size_t size = ifs.tellg();
                                                                           string buffer(size, ' ');
                                                                           ifs.seekg(0);
                                                                           ifs.read(&buffer[0], size);
                                                                           ifs.close();
                                                                           promise->resolve(jsi::String::createFromUtf8(rt, buffer));
                                                                       } catch (...) {
                                                                           promise->reject("Content read file");
                                                                       }
                                                                   });
                                                               }
                                                               );
    rt.global().setProperty(rt, "readFileAsync", move(readFileAsync));
    
    auto writeFile = jsi::Function::createFromHostFunction(
                                                           rt,
                                                           jsi::PropNameID::forAscii(rt, "writeFile"),
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
                                                               
                                                               /* TODO: handle
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
                                                               
                                                               return jsi::Value().undefined();
                                                           }
                                                           );
    rt.global().setProperty(rt, "writeFile", move(writeFile));
    
    auto writeFileAsync = jsi::Function::createFromHostFunction(
                                                                rt,
                                                                jsi::PropNameID::forAscii(rt, "writeFileAsync"),
                                                                2, // path, content
                                                                [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                    if(!arguments[0].isString()) {
                                                                        jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                    }
                                                                    
                                                                    if (!arguments[1].isString()) {
                                                                        jsi::detail::throwJSError(runtime, "File content is not a string");
                                                                    }
                                                                    
                                                                    const string content = arguments[1].asString(runtime).utf8(runtime);
                                                                    const string file = arguments[0].asString(runtime).utf8(runtime);
                                                                    // fs::path filePath = fs::path(file);
                                                                    
                                                                    /* TODO: handle
                                                                     bool fileCreationSuccess = fs::create_directory(filePath);
                                                                     if (!fileCreationSuccess) {
                                                                     jsi::detail::throwJSError(runtime, "Directory could not be created");
                                                                     }
                                                                     */
                                                                    
                                                                    return createPromiseAsJSIValue(runtime, [content, file](jsi::Runtime &rt, std::shared_ptr<Promise> promise) {
                                                                        try {
                                                                            fs::path filePath = fs::path(file);
                                                                            fs::ofstream ofs(filePath);
                                                                            ofs.write(&content[0], content.size());
                                                                            ofs.close();
                                                                            promise->resolve(jsi::Value().undefined());
                                                                        } catch (...) {
                                                                            promise->reject("Content could not be written to file");
                                                                        }
                                                                    });
                                                                }
                                                                );
    rt.global().setProperty(rt, "writeFileAsync", move(writeFileAsync));
    
    auto moveFile = jsi::Function::createFromHostFunction(
                                                            rt,
                                                            jsi::PropNameID::forAscii(rt, "moveFile"),
                                                            2, // oldPath, newPath
                                                            [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                if(!arguments[0].isString()) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                }
                                                                if(!arguments[1].isString()) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                }
                                                                
                                                                
                                                                string oldPath = arguments[0].asString(runtime).utf8(runtime);
                                                                fs::path oldFile = fs::path(oldPath);
                                                                
                                                                string newPath = arguments[1].asString(runtime).utf8(runtime);
                                                                fs::path newFile = fs::path(newPath);
                                                                
                                                                if(!fs::exists(oldPath)) {
                                                                    jsi::detail::throwJSError(runtime, "File does not exist");
                                                                }
                                                                
                                                                if(!fs::is_regular_file(oldPath)) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not pointing to a file");
                                                                }
                                                                
                                                                if(fs::exists(newFile)) {
                                                                    jsi::detail::throwJSError(runtime, "File at new path already exists");
                                                                }
                                                                
                                                                try {
                                                                    fs::rename(oldFile, newFile);
                                                                } catch (...) {
                                                                    jsi::detail::throwJSError(runtime, "Could not rename file");
                                                                }
                                                                
                                                                return jsi::Value().undefined();
                                                            }
                                                            );
    rt.global().setProperty(rt, "moveFile", move(moveFile));
    
    auto copyFile = jsi::Function::createFromHostFunction(
                                                            rt,
                                                            jsi::PropNameID::forAscii(rt, "copyFile"),
                                                            2, // sourcePath, targetPath
                                                            [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                if(!arguments[0].isString()) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                }
                                                                if(!arguments[1].isString()) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                }
                                                                
                                                                
                                                                string source = arguments[0].asString(runtime).utf8(runtime);
                                                                fs::path sourcePath = fs::path(source);
                                                                
                                                                string target = arguments[1].asString(runtime).utf8(runtime);
                                                                fs::path targetPath = fs::path(target);
                                                                
                                                                if(!fs::exists(sourcePath)) {
                                                                    jsi::detail::throwJSError(runtime, "File does not exist");
                                                                }
                                                                
                                                                if(!fs::is_regular_file(sourcePath)) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not pointing to a file");
                                                                }
                                                                
                                                                if(fs::exists(targetPath)) {
                                                                    jsi::detail::throwJSError(runtime, "File at new path already exists");
                                                                }
                                                                
                                                                try {
                                                                    fs::copy(sourcePath, targetPath);
                                                                } catch (...) {
                                                                    jsi::detail::throwJSError(runtime, "Could not rename file");
                                                                }
                                                                
                                                                return jsi::Value().undefined();
                                                            }
                                                            );
    rt.global().setProperty(rt, "copyFile", move(copyFile));
    
    auto removeFile = jsi::Function::createFromHostFunction(
                                                            rt,
                                                            jsi::PropNameID::forAscii(rt, "removeFile"),
                                                            1, // path
                                                            [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                                                                if(!arguments[0].isString()) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not a string");
                                                                }
                                                                
                                                                string file = arguments[0].asString(runtime).utf8(runtime);
                                                                fs::path filePath = fs::path(file);
                                                                
                                                                if(!fs::exists(filePath)) {
                                                                    jsi::detail::throwJSError(runtime, "File does not exist");
                                                                }
                                                                
                                                                if(!fs::is_regular_file(filePath)) {
                                                                    jsi::detail::throwJSError(runtime, "Path is not pointing to a file");
                                                                }
                                                                
                                                                try {
                                                                    bool status = fs::remove(filePath);
                                                                    return jsi::Value(status);
                                                                } catch (...) {
                                                                    jsi::detail::throwJSError(runtime, "Could not delete file");
                                                                }
                                                                
                                                                return jsi::Value().undefined();
                                                            }
                                                            );
    rt.global().setProperty(rt, "removeFile", move(removeFile));
}

