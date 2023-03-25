{
  'targets': [
    {
      'target_name': 'noodle',
      'sources': [ 'src/noodle.cc' ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/Users/horal/Documents/repository/l10n-toolbox/work/OodleData/Sdks/2.9.0/include/"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'libraries': [
        "/Users/horal/Documents/repository/l10n-toolbox/work/OodleData/Sdks/2.9.0/lib/Linux/liboo2corelinux64.a"
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCLinkerTool': {
          'AdditionalOptions': [ '/NODEFAULTLIB:MSVCRT' ],
        },
        'VCCLCompilerTool': {
          'ExceptionHandling': 1,
          'RuntimeLibrary': 0
        },
      }
    }
  ],
}