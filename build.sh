. .cicd-config

if [[ $# -eq 0 ]]; then
    echo "Use ./build.sh <dev/rel/test>"
    return 1
elif [[ $1 == "dev" ]]; then
    BUILD_DIR=$BUILD_DIR_DEV
    CMAKE_PARAMS="-DASAN=ON"
    TARGET=$TARGET_SRC
elif [[ $1 == "rel" ]]; then
    BUILD_DIR=$BUILD_DIR_REL
    TARGET=$TARGET_SRC
elif [[ $1 == "test" ]]; then
    BUILD_DIR=$BUILD_DIR_DEV
    TARGET=$TARGET_TEST
else
    echo "Use ./build.sh <dev/rel/test>"
    return 1
fi

cmake -H. -B$BUILD_DIR $CMAKE_PARAMS
cmake --build $BUILD_DIR/. --parallel $(nproc) --target $TARGET
