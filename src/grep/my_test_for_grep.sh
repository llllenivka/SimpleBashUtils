#!/bin/bash

SUCCESS=0
FAIL=0
COUNT=0
DIFF=""

declare -a flags=(
"-i"
"-v"
"-c"
"-l"
"-n"
"-h"
"-s"
"-o"
)

txt1="text_for_my_testgrep1.txt"
txt2="text_for_my_testgrep2.txt"

declare -a commline=(
"OPT"
)

function test1()
{
    str=$(echo $@ | sed "s/OPT/$options/")

        ./s21_grep $str $txt1 > proverka_mygrep.txt
        grep $str $txt1> proverka_grep.txt
        DIFF="$(diff -s proverka_mygrep.txt proverka_grep.txt)"
            if [ "$DIFF" == "Files proverka_mygrep.txt and proverka_grep.txt are identical" ]
            then
                (( COUNT++ ))
                echo "$COUNT $options $txt1  - Success"                        
                (( SUCCESS++ ))
                echo "\n"
            else
                (( FAIL++ ))
                (( COUNT++ ))
                echo "$COUNT $options $txt1 - Fail"
                echo "\n"
            fi
            rm proverka_mygrep.txt proverka_grep.txt

}

function test2()
{
    str=$(echo $@ | sed "s/OPT/$options/")

        ./s21_grep $str $txt1 $txt2> proverka_mygrep.txt
        grep $str $txt1 $txt2> proverka_grep.txt
        DIFF="$(diff -s proverka_mygrep.txt proverka_grep.txt)"
            if [ "$DIFF" == "Files proverka_mygrep.txt and proverka_grep.txt are identical" ]
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
            rm proverka_mygrep.txt proverka_grep.txt

}

echo --------------------------------------------------------------------------------
echo ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆ 1 flag ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
echo --------------------------------------------------------------------------------

for fl in "${flags[@]}"
do
    options="album $fl"
    test1 $commline
    test2 $commline
done

for fl in "${flags[@]}"
do
    options="-e album -e wake -f pattern_for_test_1.txt $fl"
    test1 $commline
    test2 $commline
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
            options="album $fl1 $fl2"
            test1 $commline
            test2 $commline
        fi
    done
done


for fl1 in "${flags[@]}"
do
    for fl2 in "${flags[@]}"
    do
        if [ $fl1 != $fl2 ]
        then
            options="-e album -e wake -f pattern_for_test_1.txt $fl1 $fl2"
            test1 $commline
            test2 $commline
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
                    options="-e album -e wake -f pattern_for_test_1.txt $fl1 $fl2 $fl3 $fl4"
                    test1 $commline
                    test2 $commline
                fi
            done
        done
    done
done

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
                    options="album $fl1 $fl2 $fl3 $fl4"
                    test1 $commline
                    test2 $commline
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



