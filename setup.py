from setuptools import Extension, setup

CLASSIFIERS = """
Development Status :: 5 - Production/Stable
Intended Audience :: Developers
License :: OSI Approved :: BSD License
Programming Language :: C
Programming Language :: Python :: 3
Programming Language :: Python :: 3.5
Programming Language :: Python :: 3.6
Programming Language :: Python :: 3.7
Programming Language :: Python :: 3.8
Programming Language :: Python :: 3 :: Only
"""


module1 = Extension(
    "afctest",
    sources=[
        "./python/cacheddict.c",
        "./python/other.c",
        "./python/afctest.c",
    ],
    include_dirs=["./python"],
    extra_compile_args=["-D_GNU_SOURCE"],
    extra_link_args=["-lstdc++", "-lm"],
)


def get_version():
    return "0.1"


setup(
    name="afctest",
    description="testing stuff",
    ext_modules=[module1],
    download_url="https://github.com/albertferras/cpython_test",
    platforms=["any"],
    url="https://github.com/albertferras/cpython_test",
    project_urls={"Source": "https://github.com/albertferras/cpython_test"},
    python_requires=">=3.5",
    classifiers=[x for x in CLASSIFIERS.split("\n") if x],
)
