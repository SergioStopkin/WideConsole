. .cicd-config

echo "_________________________________________    Unit Tests   _________________________________________"
$BUILD_DIR_DEV/test/unit/unit-tests

echo "_________________________________________ Component Tests _________________________________________"
$BUILD_DIR_DEV/test/component/component-tests
