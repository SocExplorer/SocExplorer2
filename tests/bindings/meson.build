test_scripts = [
    'test_pysocmodule.py',
    'test_soc.py',
    'test_socexplorerobject.py',
    'test_workspace.py',
    'test_factory.py'
]

foreach test:test_scripts
    test(test.split('.')[0], python3,
        args:[meson.current_source_dir()+'/'+test, '--verbose'],
        env:['PYTHONPATH='+meson.project_build_root()+'/src/bindings']
    )
endforeach

library('tests_fake',[],
        extra_files:test_scripts)
