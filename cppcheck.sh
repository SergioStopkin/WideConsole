. .cicd-config

cppcheck \
    --quiet \
    --enable=all \
    --inline-suppr \
    --suppress=missingInclude \
    --error-exitcode=1 \
    $CPPCHECK_SOURCE_DIR
