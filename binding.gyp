{
  'targets': [
    {
      'target_name': 'libtess2js',
      'include_dirs': [
          'src/libtess2src/Include',
          'src'
      ],
      'sources': [
          'src/bridge.cc',
          'src/libtess2src/Source/bucketalloc.c',
          'src/libtess2src/Source/dict.c',
          'src/libtess2src/Source/geom.c',
          'src/libtess2src/Source/mesh.c',
          'src/libtess2src/Source/priorityq.c',
          'src/libtess2src/Source/sweep.c',
          'src/libtess2src/Source/tess.c'
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions', '-g', '-O0' ],
      'conditions': [
        ['OS=="win"', {
          'defines': [
            'WIN32', 'UNICODE'
          ]
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}
