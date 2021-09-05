# https://github.com/dockcross/dockcross

FROM dockcross/base

ENV DEFAULT_DOCKCROSS_IMAGE pdic_cross_build
RUN set -eux && \
    apt update -y && apt install -y --no-install-recommends \
    curl ca-certificates tar build-essential sudo git binutils-gold \
    libtool libtool-bin zlib1g-dev libssl-dev \
    libncursesw5 libpthread-stubs0-dev \
    clang-format clang-tidy clang-tools clang clangd libc++-dev \
    libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev \
    libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python-clang
RUN pip install pdoc3 twine pyaml
