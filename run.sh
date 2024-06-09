. .cicd-config

USAGE_TEXT="Usage ./run.sh <dev/rel/test>"
if [[ $# -eq 0 ]]; then
    PrintUsageAndExit
elif [[ $1 == "dev" ]]; then
    $BUILD_DIR_DEV/src/$TARGET_SRC
elif [[ $1 == "rel" ]]; then
    $BUILD_DIR_REL/src/$TARGET_SRC
elif [[ $1 == "test" ]]; then
    echo "_________________________________________    Unit Tests   _________________________________________"
    $BUILD_DIR_DEV/test/unit/unit-tests
    echo "_________________________________________ Component Tests _________________________________________"
    $BUILD_DIR_DEV/test/component/component-tests
else
    PrintUsageAndExit
fi
