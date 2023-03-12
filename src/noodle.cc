#include <napi.h>

#include "oodle2.h"

using namespace Napi;

int OodleCompress(uint32_t type, Napi::Uint8Array input, uint32_t length, Napi::Uint8Array output) {
    return OodleLZ_Compress((OodleLZ_Compressor) type, input.Data(), length, output.Data(), OodleLZ_CompressionLevel_Normal);
}

Napi::Number Node_Compress(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32_t type = info[0].As<Napi::Number>().Uint32Value();
    Napi::Uint8Array input = info[1].As<Napi::Uint8Array>();
    uint32_t length = info[2].As<Napi::Number>().Uint32Value();
    Napi::Uint8Array output = info[3].As<Napi::Uint8Array>();

    int result = OodleCompress(type, input, length, output);

    return Napi::Number::New(env, result);
}

int OodleDecompress(Napi::Uint8Array input, Napi::Uint8Array output, uint32_t length) {
    return OodleLZ_Decompress(input.Data(), input.ByteLength(), output.Data(), length);
}

Napi::Number Node_Decompress(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Uint8Array input = info[0].As<Napi::Uint8Array>();
    Napi::Uint8Array output = info[1].As<Napi::Uint8Array>();
    uint32_t length = info[2].As<Napi::Number>().Uint32Value();

    int result = OodleDecompress(input, output, length);

    return Napi::Number::New(env, result);
}

Napi::Number Node_GetFirstChunkCompressor(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Uint8Array input = info[0].As<Napi::Uint8Array>();

    int result = OodleLZ_GetFirstChunkCompressor(input.Data(), input.ByteLength(), NULL);

    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    int32_t OodleDecoderMemorySize = OodleLZDecoder_MemorySizeNeeded(OodleLZ_Compressor_Invalid, -1);

    exports.Set(Napi::String::New(env, "Compress"), Napi::Function::New(env, Node_Compress));
    exports.Set(Napi::String::New(env, "Decompress"), Napi::Function::New(env, Node_Decompress));
    exports.Set(Napi::String::New(env, "GetFirstChunkCompressor"), Napi::Function::New(env, Node_GetFirstChunkCompressor));
    return exports;
}

NODE_API_MODULE(addon, Init)
