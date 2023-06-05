. .cicd-config

sed -i 's/-static-libasan/ /g' $BUILD_DIR_DEV/compile_commands.json

echo $SOURCE_FILES | xargs clang-tidy --quiet -p $BUILD_DIR_DEV
RESULT=$?

echo $TEST_FILES | xargs clang-tidy --quiet -p $BUILD_DIR_DEV \
    --checks '
        -cert-err58-cpp,
        -cppcoreguidelines-avoid-non-const-global-variables,
        -cppcoreguidelines-owning-memory,
        -fuchsia-default-arguments-calls,
        -fuchsia-statically-constructed-objects'
let "RESULT+=$?"

return $RESULT
