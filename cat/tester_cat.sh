#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

files=("test1.txt" "test2.txt")
inputs=("b" "e" "s" "n" "t" "v" "be" "bs" "bn" "bt" "bv" "es" "en" "et" "ev" "sn" "st" "sv" "nt" "nv" "tv" "bes"
"ben" "bet" "bev" "bsn" "bst" "bsv" "bnt" "bnv" "btv" "esn" "est" "esv" "ent" "env" "etv" "snt" "snv" "stv" "ntv"
"besn" "best" "besv" "bent" "benv" "betv" "bsnt" "bsnv" "bstv" "bntv" "esnt" "esnv" "entv" "sntv" "besnt" "besnv"
"bestv" "bentv" "bsntv" "esntv" "benstv")


for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for input in "${inputs[@]}"
        do
            echo ""
            echo "-$input $file1 $file2:"
            ./s21_cat "-$input" "$file1" "$file2" > s21cat_output.txt
            cat "-$input" "$file1" "$file2" > cat_output.txt

            if diff -q s21cat_output.txt cat_output.txt >/dev/null 2>&1;
            then
                let "COUNTER++"
                let "SUCCESS++"
                echo "$COUNTER - Success"
            else 
                let "COUNTER++"
                let "FAIL++"
                echo "$FAIL - Fail"
            fi

            rm s21cat_output.txt
            rm cat_output.txt
        done
    done
done

echo ""
echo "Total: $COUNTER, Success: $SUCCESS, Fail: $FAIL"
echo ""