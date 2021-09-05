# Extra

## Install Clang llvm lld from source

Follow: [LibTooling and LibASTMatchers](https://clang.llvm.org/docs/LibASTMatchersTutorial.html) installation tutorial if you want to contribute.

Use `gold` or `lld` because `bfd` use too much ram

`wget` or `curl --progress-bar -LO`

```sh
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-12.0.1.tar.gz
tar xvf llvmorg-12.0.1.tar.gz
cd llvm-project-llvmorg-12.0.1

cmake -G Ninja -S ./llvm -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;lld" -DCMAKE_BUILD_TYPE=Release -DLLVM_USE_LINKER=gold -B build

# export CC=`which clang`
# export CXX=`which clang++`
# export CFLAGS='-fuse-ld=ld.lld -rtlib=compiler-rt'
# export CXXFLAGS='-fuse-ld=lld' # gcc
# export CXXFLAGS='-B lld' # clang
# sudo update-alternatives --install "/usr/bin/ld" "ld" `which ld.lld` 10

cmake --build build -- -j`nproc`
sudo cmake --install build
cd build
ninja install
```

```sh
# uninstall from build
xargs rm < install_manifest.txt
```
