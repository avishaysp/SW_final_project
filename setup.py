from setuptools import Extension, setup

module = Extension("symnmfssp", sources=['symnmfmodule.c'])
setup(name='symnmfssp',
     version='1.0',
     description='Python wrapper for custom C extension',
     ext_modules=[module])