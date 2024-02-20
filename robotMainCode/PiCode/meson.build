project(
  'kingLearBot',
  'cpp',
  version : '1.0.0',
  license : 'MIT',
  default_options : []
)

add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

inc = include_directories('include')

proj_sources = ['src/main.cpp', 'src/communicatorSM.cpp', 'src/communicator.cpp']
proj_headers = ['include/robotControlSM.h', 'include/communicatorSM.h', 'include/communicator.h']
install_headers(proj_headers)

asio = subproject('asio')
asio_dep = asio.get_variable('asio_dep')

executable('botCode', proj_sources, include_directories : inc,dependencies : asio_dep)
