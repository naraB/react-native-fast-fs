#include "FastFilesystemModule.h"
#include "filesystem/filesystem.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "JSIUtils.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace fs = ghc::filesystem;
using namespace std;
using namespace facebook;

void install(jsi::Runtime &rt)
{

    installDirectoryFunctions(rt);
    installFileFunctions(rt);

    auto exists = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "exists"),
        1, // path
        [](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
        {
            if (!arguments[0].isString())
            {
                jsi::detail::throwJSError(runtime, "Path is not a string");
            }

            string path = arguments[0].asString(runtime).utf8(runtime);
            fs::path filePath = fs::path(path);
            try
            {
                bool exists = fs::exists(filePath);
                return jsi::Value(exists);
            }
            catch (fs::filesystem_error &e)
            {
                jsi::detail::throwJSError(runtime, e.what());
            }

            return jsi::Value().undefined();
        });
    rt.global().setProperty(rt, "exists", move(exists));

    auto rm = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "rm"),
        2, // path, recursive
        [](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
        {
            if (!arguments[0].isString())
            {
                jsi::detail::throwJSError(runtime, "Argument 'path' is not a string.");
            }

            if (!arguments[1].isBool())
            {
                jsi::detail::throwJSError(runtime, "Argument 'recursive' is not a boolean.");
            }

            const string path = arguments[0].asString(runtime).utf8(runtime);
            const fs::path fsPath = fs::path(path);

            if (!fs::exists(fsPath))
            {
                jsi::detail::throwJSError(runtime, "Path is not pointing to a file or directory.");
            }

            const bool recursive = arguments[1].getBool();

            //                                                                if(!fs::is_regular_file(filePath)) {
            //                                                                    jsi::detail::throwJSError(runtime, "Path is not pointing to a file");
            //                                                                }

            try
            {
                bool status;
                if (recursive)
                {
                    status = fs::remove_all(fsPath);
                }
                else
                {
                    status = fs::remove(fsPath);
                }
                return jsi::Value(status);
            }
            catch (fs::filesystem_error &e)
            {
                jsi::detail::throwJSError(runtime, e.what());
            }

            return jsi::Value().undefined();
        });
    rt.global().setProperty(rt, "rm", move(rm));
    
    auto getPermissions = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "getPermissions"),
        2, // path
        [](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
        {
            if (!arguments[0].isString())
            {
                jsi::detail::throwJSError(runtime, "Argument 'path' is not a string.");
            }

            const string path = arguments[0].asString(runtime).utf8(runtime);
            const fs::path fsPath = fs::path(path);

            if (!fs::exists(fsPath))
            {
                jsi::detail::throwJSError(runtime, "Path is not pointing to a file or directory.");
            }

            int permissions = static_cast<int>(fs::status(fsPath).permissions());

            return jsi::Value(permissions);
        });
    rt.global().setProperty(rt, "getPermissions", move(getPermissions));

}
