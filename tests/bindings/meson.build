bindings_path=meson.project_build_root()+'/src/bindings'
scrip_path = meson.current_source_dir()+'/@0@'

test('pysocmodule_tests', python3, args:[scrip_path.format('pysocmodule_tests.py'), '--verbose'],
    env:['PYTHONPATH='+bindings_path]
)

test('soc_tests', python3, args:[scrip_path.format('soc_tests.py'), '--verbose'],
    env:['PYTHONPATH='+bindings_path]
)

test('socexplorerobject_tests', python3, args:[scrip_path.format('socexplorerobject_tests.py'), '--verbose'],
    env:['PYTHONPATH='+bindings_path]
)

test('workspace_tests', python3, args:[scrip_path.format('workspace_tests.py'), '--verbose'],
    env:['PYTHONPATH='+bindings_path]
)
