project('kingLearBot', 'cpp',
  version : '1.0.0',
  license : 'MIT')

add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

inc = include_directories('include')

proj_sources = ['src/main.cpp', 'src/robotState.cpp', 'src/robotControlSM.cpp', 'src/serial.cpp', 'src/communicatorSM.cpp']
proj_headers = ['include/robotControlSM.h', 'include/robotControlSM.h', 'include/serial.h', 'include/communicatorSM.h']
install_headers(proj_headers)

executable('botCode', proj_sources, include_directories : inc,)
