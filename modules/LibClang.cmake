include(ExternalProject)
# Clang 12
set(LIBCLANG_INSTALL libclang-copied)
ExternalProject_Add(libclang-static-build
	DOWNLOAD_DIR "libclang-static-build"
	INSTALL_DIR "${LIBCLANG_INSTALL}"
	GIT_REPOSITORY "https://github.com/deech/libclang-static-build"
  	GIT_TAG "3daf7793644764bff2dad11021051a6b8f450a52" # latest
	# GIT_TAG "0cae8e85ef1ad951e1bb560e1eadcd64b2f0828e"
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${LIBCLANG_INSTALL}"
)
ExternalProject_Get_Property(libclang-static-build binary_dir)
