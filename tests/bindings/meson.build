test_scripts = [
    'pysocmodule_tests.py',
    'soc_tests.py',
    'socexplorerobject_tests.py',
    'workspace_tests.py',
    'factory_tests.py'
]

foreach test:test_scripts
    test(test.split('.')[0], python3,
        args:[meson.current_source_dir()+'/'+test, '--verbose'],
        env:['PYTHONPATH='+meson.project_build_root()+'/src/bindings']
    )
endforeach

library('tests_fake',[],
        extra_files:test_scripts)
