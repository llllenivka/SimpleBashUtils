#!/bin/bash

SUCCESS=0
FAIL=0
COUNT=0
DIFF=""

declare -a flags=(
"-b"
"-e"
"-n"
"-s"
"-t"
"-v"
)
txt1="text_for_my_testcat1.txt"
txt2="text_for_my_testcat2.txt"

declare -a files=(
"text_for_my_testcat1.txt"
"text_for_my_testcat2.txt"
)

declare -a commline=(
"OPT"
)

function test()
{
    str=$(echo $@ | sed "s/OPT/$options/")

        ./s21_cat $str $txt1 $txt2 > proverka_mycat.txt
        cat $str $txt1 $txt2 > proverka_cat.txt
        DIFF="$(diff -s proverka_mycat.txt proverka_cat.txt)"
            if [ "$DIFF" == "Files proverka_mycat.txt and proverka_cat.txt are identical" ]
            then
                (( COUNT++ ))
                echo "$COUNT $options $txt1 $txt2 - Success"                        
                (( SUCCESS++ ))
                echo "\n"
            else
                (( FAIL++ ))
                (( COUNT++ ))
                echo "$COUNT $options $txt1 $txt2 - Fail"
                echo "\n"
            fi
            rm proverka_mycat.txt proverka_cat.txt

}

echo --------------------------------------------------------------------------------
echo ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆ 1 flag ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
echo --------------------------------------------------------------------------------

for fl in "${flags[@]}"
do
    options=" $fl"
    test $commline
done

echo --------------------------------------------------------------------------------
echo ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆ 2 flag ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
echo --------------------------------------------------------------------------------


for fl1 in "${flags[@]}"
do
    for fl2 in "${flags[@]}"
    do
        if [ $fl1 != $fl2 ]
        then

            options=" $fl1 $fl2"
            test $commline
        fi
    done
done


echo --------------------------------------------------------------------------------
echo ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆ 4 flag ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
echo --------------------------------------------------------------------------------

for fl1 in "${flags[@]}"
do
    for fl2 in "${flags[@]}"
    do
        for fl3 in "${flags[@]}"
        do
            for fl4 in "${flags[@]}"
            do
                if [ $fl1 != $fl2 ] && [ $fl1 != $fl3 ] \
                && [ $fl1 != $fl4 ] && [ $fl2 != $fl3 ] \
                && [ $fl2 != $fl4 ] && [ $fl3 != $fl4 ]
                then
                    options="$fl1 $fl2 $fl3 $fl4"
                    test $commline
                fi
            done
        done
    done
done

echo "\n"
echo "┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┤  ( ͡° ͜ʖ├┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬"
echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
echo "ALL: $COUNT"
echo "├┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┤"




