__author__ = "Barre Kevin"
__maintainer__ = "Barre kevin"
__credits__ = ["https://github.com/neudinger"]
__email__ = "kevin.barre@epitech.eu"
__status__ = "Beta"

import os
import sys
import pathlib
import re
try:
    from skbuild import setup
except ImportError:
    print('Please update pip, you need pip 10 or greater,\n'
          ' or you need to install the PEP 518 requirements in pyproject.toml yourself', file=sys.stderr)
    raise

here = pathlib.Path(__file__).parent.resolve()
long_description = (here / "README.md").read_text(encoding="utf-8")


version = os.getenv("version", default="0.0.1")
version = re.match(r".*?(\d+\.?\d+\.?\d+).*?",
                   version, re.S).groups()[0]


print(f"__version__ = '{version}'",
      file=open(f"{here}/src/pdic/__version__.py", "w"))

setup(
    name="pdic",
    version=version,
    author_email="kevin.barre@epitech.eu",
    description="Python api (IDL) Transpiler Source-to-source compiler C/C++ to YAML Description based on clang",
    long_description_content_type="text/markdown",
    long_description=long_description,
    author="Barre Kevin",
    license="EUPL",
    python_requires=">=3.6",
    packages=["pdic"],
    package_dir={"": "src"},
    project_urls={
        'Source': 'https://github.com/neudinger/pdic',
    },
    cmake_install_dir="src/pdic",
    cmake_args=['-DDEBUG:BOOL=OFF'],
    install_requires=[
        "pyyaml"
    ],
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        "Programming Language :: C++",
        "Topic :: Software Development",
        "Topic :: Scientific/Engineering",
        "Typing :: Typed",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS",
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3 :: Only',
    ],
)
