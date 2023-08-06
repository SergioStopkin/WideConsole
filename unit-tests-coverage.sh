. .cicd-config

rm -rf $COV_RESULT_DIR
mkdir $COV_RESULT_DIR

find $BUILD_DIR_DEV/$COV_SOURCE_DIR -name "*.gcno" -exec cp "{}" $COV_RESULT_DIR/ \;
find $BUILD_DIR_DEV/$COV_SOURCE_DIR -name "*.gcda" -exec cp "{}" $COV_RESULT_DIR/ \;

lcov -q -c --external -d $COV_RESULT_DIR -o $COV_RESULT_DIR/coverage.info
lcov -q -r $COV_RESULT_DIR/coverage.info "/usr/*" -o $COV_RESULT_DIR/coverage.info
lcov -q -r $COV_RESULT_DIR/coverage.info "/*/$COV_SOURCE_DIR/*" -o $COV_RESULT_DIR/coverage.info

RESULT=$(genhtml -t "Unit Tests Coverage" --num-spaces 4 $COV_RESULT_DIR/coverage.info -o $COV_RESULT_DIR)
IS_FOUND=0

for item in $RESULT
do
    if [[ $IS_FOUND == 1 ]]; then
        COVERAGE=$item
        break
    fi
    if [[ $item == "lines......:" ]]; then
        IS_FOUND=1
    fi
done

if (( `echo "$COVERAGE < $COV_MIN_LIMIT" | sed 's/%//g' | bc -l` )); then
    echo "Unit tests coverage $COVERAGE less then $COV_MIN_LIMIT"
    exit 1
else
    echo "Unit tests coverage $COVERAGE"
    exit 0
fi
