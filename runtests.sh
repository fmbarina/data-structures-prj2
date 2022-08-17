#!/bin/bash

test()
{
    local test
    test="$1"
    
    echo "RUNNING TEST: $(basename "$test")"
    
    rm -f ./*.comp

    for file in "$test"/*; do
        cp  "$file" ./

        printf ' - Compressing...'
        ./compacta.out "$(basename "$file")"
        printf ' Done\n'

        rm "$(basename "$file")"


        printf ' - Decompressing...'
        ./descompacta.out *.comp
        printf ' Done\n'

        # Move file to tests_out
        mkdir -p ./tests_out/"$(basename "$test")"
        mv "$(basename "$file")" ./tests_out/"$(basename "$test")"
    done
    
    rm -f ./*.comp
}

rm -rf ./tests_out
rm -f ./*.comp
make clean

make 

differences=

echo '### TESTING ###'

if [ "$(ls "./tests")" ]; then
	for testdir in "./tests"/*; do
        test "$testdir"
    done
fi


echo '### CHECKING ###'

if [ "$(ls "./tests")" ]; then
	for testdir in "./tests"/* ; do
        printf 'CHECKING: %s' "$(basename "$testdir")"

        for file in "$testdir"/* ; do
            cmp -s "$file" ./tests_out/"$(basename "$testdir")"/"$(basename "$file")"
            ret=$?
            if [ $ret -ne 0 ]; then
                printf " - ERR\n"
                differences=':c'
            else
                printf " - OK\n"
            fi
        done
    done
fi

if [ -n "$differences" ]; then
    echo '***There were differences***'
else
    echo 'No differences found.'
fi

