#include <cstdarg>
#include <cstdlib>
#include <napi.h>

#include "oodle2.h"

using namespace Napi;

#define Noodle_IsDebug() std::getenv("NOODLE_DEBUG") != NULL

Napi::Number Noodle_Compress(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32_t type = info[0].As<Napi::Number>().Uint32Value();
    Napi::Uint8Array input = info[1].As<Napi::Uint8Array>();
    uint32_t length = info[2].As<Napi::Number>().Uint32Value();
    Napi::Uint8Array output = info[3].As<Napi::Uint8Array>();

    int result = OodleLZ_Compress((OodleLZ_Compressor) type, input.Data(), length, output.Data(), OodleLZ_CompressionLevel_Normal);

    return Napi::Number::New(env, result);
}

Napi::Number Noodle_Decompress(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Uint8Array input = info[0].As<Napi::Uint8Array>();
    Napi::Uint8Array output = info[1].As<Napi::Uint8Array>();
    uint32_t length = info[2].As<Napi::Number>().Uint32Value();
    uint32_t context = !info[3].IsUndefined() ? info[3].As<Napi::Number>().Uint32Value() : 0;

    int result = OodleLZ_Decompress(
        input.Data(),
        input.ByteLength(),
        output.Data(),
        length,
        OodleLZ_FuzzSafe_Yes,
        OodleLZ_CheckCRC_Yes,
        Noodle_IsDebug() ? OodleLZ_Verbosity_Lots : OodleLZ_Verbosity_None,
        context > 0 ? output.Data() - context : NULL,
        context + length
    );

    return Napi::Number::New(env, result);
}

Napi::Number Noodle_GetFirstChunkCompressor(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Uint8Array input = info[0].As<Napi::Uint8Array>();

    int result = OodleLZ_GetFirstChunkCompressor(input.Data(), input.ByteLength(), NULL);

    return Napi::Number::New(env, result);
}

void OodleDebugPrintf(int verboseLevel, const char * file, int line, const char * fmt, ...) {
    std::va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    if (Noodle_IsDebug()) {
        OodleCore_Plugins_SetPrintf(OodleDebugPrintf);
    }

    exports.Set(Napi::String::New(env, "Compress"), Napi::Function::New(env, Noodle_Compress));
    exports.Set(Napi::String::New(env, "Decompress"), Napi::Function::New(env, Noodle_Decompress));
    exports.Set(Napi::String::New(env, "GetFirstChunkCompressor"), Napi::Function::New(env, Noodle_GetFirstChunkCompressor));
    return exports;
}

NODE_API_MODULE(noodle, InitAll)
