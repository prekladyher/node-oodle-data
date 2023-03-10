{
  'targets': [
    {
      'target_name': 'noodle',
      'sources': [ 'src/noodle.cc' ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        "N:/games/epic/UE_4.27/Engine/Plugins/Compression/OodleData/Sdks/2.9.0/include/"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'libraries': [
        "N:/games/epic/UE_4.27/Engine/Plugins/Compression/OodleData/Sdks/2.9.0/lib/Win64/oo2core_win64.lib"
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}