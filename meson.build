project('SocExplorer', 'cpp',default_options : ['cpp_std=c++17'], license: 'GPL3', version: '2.0.0')

pymod = import('python')
python3 = pymod.find_installation('python3', modules:['PySide2','shiboken2', 'shiboken2_generator', 'numpy'])

qt5 = import('qt5')
qt5core = dependency('qt5', modules : 'Core')
qt5widgets = dependency('qt5', modules : 'Widgets')
qt5gui = dependency('qt5', modules : 'Gui')
qt5svg = dependency('qt5', modules : 'Svg')
qt5test = dependency('qt5', modules : 'Test')

opaque_inc_dir = 'opaque-1.3.0/include'
opaque_dep = declare_dependency(include_directories: opaque_inc_dir)

catch2_dep = dependency('catch2', main : true, fallback : ['catch2', 'catch2_dep'])
range_dep = dependency('range-v3', fallback : ['range-v3', 'range_dep'])
cpp_utils_dep = dependency('cpp_utils', fallback : ['cpp_utils', 'cpp_utils_dep'])
QtGuiTestUtils_dep = dependency('QtGuiTestUtils', fallback : ['QtGuiTestUtils', 'QtGuiTestUtils_dep'])

subdir('src')
subdir('tests')
