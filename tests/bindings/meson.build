bindings_path=meson.project_build_root()+'/src/bindings'
scrip_path = meson.current_source_dir()+'/@0@'

test('basic_tests', python3, args:[scrip_path.format('basic_tests.py'), '--verbose'],
    env:['PYTHONPATH='+bindings_path]
)
