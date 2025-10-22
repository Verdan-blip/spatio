project(
  'spatio', 
  'c', 'cpp',
  version : '0.1.0',
  meson_version: '>= 0.56.0',
  default_options : [
    'warning_level=2'
  ]
)

add_project_arguments('-std=c++20', language: 'cpp')

louvre_dep = dependency('Louvre')
pixman_dep = dependency('pixman-1')

sources = [
  'src/main.cpp',
  'src/SpatioCompositor.cpp',
  'src/SpatioOutput.cpp',
  'src/SpatioTopbar.cpp'
]

executable('spatio',
  sources,
  dependencies: [louvre_dep, pixman_dep],
  install: false
)