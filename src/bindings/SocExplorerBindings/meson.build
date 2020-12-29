
# 😠 https://github.com/mesonbuild/meson/issues/2320

shiboken2_generator_out = custom_target('socexplorer_bindings',
                                build_by_default:true,
                                output:generated_srcs,
                                input:'../bindings.xml',
                                depend_files:socexplorer_bindings_src,
                                command:[shiboken2,
                                meson.current_source_dir()+'/../bindings.h',
                                meson.current_source_dir()+'/../bindings.xml',
                                '--generator-set=shiboken',
                                '--enable-parent-ctor-heuristic',
                                '--enable-return-value-heuristic',
                                '--use-isnull-as-nb_nonzero',
                                '--avoid-protected-hack',
                                '--enable-pyside-extensions',
                                '-std=c++17',
                                '--typesystem-paths='+shiboken2_typesystem,
                                socexplorer_bindings_incs,
                                '--output-directory='+meson.current_build_dir()+'/../']
                                )

