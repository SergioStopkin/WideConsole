. .cicd-config

echo $SOURCE_FILES $TEST_FILES | xargs -n 1 clang-format -i

echo $CMAKE_FILES | xargs -n 1 cmake-format -i

[ -e "./.git" ] && git -C "./" status
