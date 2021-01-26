shiboken2 = find_program('shiboken2')
qmake = find_program('qmake-qt5','qmake')

python3_dep = python3.dependency(embed:true)
numpy_inc = run_command(python3, '-c', 'import numpy;print(numpy.get_include())').stdout().strip('\n')

qt5_modules = ['QtCore','QtGui','QtWidgets']

qt_headers_path = run_command(qmake, '-query', 'QT_INSTALL_HEADERS').stdout().strip('\n')
generated_srcs  = run_command(python3, 'src_list.py', 'meson').stdout().split(';')

modules_arg = '--modules=@0@'.format(','.join(qt5_modules))

shiboken2_build_flags = run_command(python3, 'shiboken-helper.py', '--includes', modules_arg).stdout().strip('\n').split(' ')
shiboken2_link_flags  = run_command(python3, 'shiboken-helper.py', '--libs', modules_arg).stdout().strip('\n').split(' ')
shiboken2_typesystem  = run_command(python3, 'shiboken-helper.py', '--typesystem').stdout().strip('\n')

socexplorer_bindings_incs = shiboken2_build_flags + [
    '-I'+meson.current_source_dir()+'/../',
    '-I'+meson.current_source_dir()+'/../plugins/bundled',
    '-I'+meson.current_source_dir()+'/../../'+opaque_inc_dir,
    '-I'+meson.current_source_dir()+'/../../subprojects/range-v3-0.10.0/include',
    '-I'+meson.current_source_dir()+'/../../subprojects/hedley-11',
    '-I'+meson.current_source_dir()+'/../../subprojects/cpp_utils/include',
    '-I'+meson.current_source_dir()+'/../../subprojects/spdlog-1.8.1/include',
    '-I'+meson.build_root()+'/subprojects/cpp_utils',
    '-I'+python3.get_path('include'),
    '-I'+qt_headers_path
    ]

foreach mod:qt5_modules
    socexplorer_bindings_incs += ['-I'+qt_headers_path+'/'+mod]
endforeach

socexplorer_bindings_src = [files('PySocModule.cpp', 'SocExplorerApp.cpp'), socexplorer_headers]

subdir('SocExplorerBindings')

shiboken_dep = declare_dependency(compile_args: shiboken2_build_flags,
                                  link_args: shiboken2_link_flags)

socexplorer_bindings_moc_files = qt5.preprocess(moc_headers : ['PySocModule.hpp', 'SocExplorerApp.hpp'],
                                                dependencies : [socexplorer_dep, bundled_plugins_dep])


socexplorer_bindings = python3.extension_module('SocExplorerBindings',
            socexplorer_bindings_src,shiboken2_generator_out,
            socexplorer_bindings_moc_files,
            dependencies : [socexplorer_dep, python3_dep, shiboken_dep, bundled_plugins_dep],
            include_directories : [numpy_inc],
            extra_files: ['bindings.h','PySocModule.hpp', 'main.py', 'SocExplorerApp.hpp']
)

