. .cicd-config

echo $SOURCE_FILES $TEST_FILES | xargs -n 1 clang-format --dry-run --Werror
RESULT=$?

echo $CMAKE_FILES | xargs -n 1 cmake-format --check
let "RESULT+=$?"

exit $RESULT
