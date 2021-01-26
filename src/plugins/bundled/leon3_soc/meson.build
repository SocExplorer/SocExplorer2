leon3_soc_moc_files = qt5.preprocess(moc_headers : 'Leon3Soc.hpp', dependencies:[socexplorer_dep])

leon3_soc = static_library('leon3_soc', ['Leon3Soc.cpp', leon3_soc_moc_files],
        extra_files:['Leon3Soc.hpp'],
        dependencies:[socexplorer_dep])

leon3_soc_dep = declare_dependency(link_with: leon3_soc, include_directories: '.')
