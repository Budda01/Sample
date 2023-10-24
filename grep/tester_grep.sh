#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

files=("test1.txt" "test2.txt")
template=("t" "k" "h")
inputs=("i" "v" "c" "l" "n" "h" "s" "o")
patterns=("patt1.txt" "patt2.txt")


for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for flag1 in "${inputs[@]}"
        do
            for tem in "${template[@]}"
            do
                echo ""
                echo "-$flag1 $tem $file1 $file2:"
                # Выполнение вашей программы
                ./s21_grep "-$flag1" "$tem" "$file1" "$file2" > s21grep_output.txt
                # Выполнение оригинального grep
                grep "-$flag1" "$tem" "$file1" "$file2" > grep_output.txt

                # Сравнение результатов
                if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1;
                then
                    let "COUNTER++"
                    let "SUCCESS++"
                    echo "$COUNTER - Success"
                else 
                    let "COUNTER++"
                    let "FAIL++"
                    echo "$FAIL - Fail"
                fi
                # Удаление временных файлов
                rm s21grep_output.txt
                rm grep_output.txt
            done
        done
    done
done

for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for flag1 in "${inputs[@]}"
        do
            for flag2 in "${inputs[@]}"
            do
                if [ $flag1 != $flag2 ]
                then
                    for tem in "${template[@]}"
                    do
                        echo ""
                        echo "-$flag1$flag2 $tem $file1 $file2:"
                        # Выполнение вашей программы
                        ./s21_grep "-$flag1" "-$flag2" "$tem" "$file1" "$file2" > s21grep_output.txt
                        # Выполнение оригинального grep
                        grep "-$flag1" "-$flag2" "$tem" "$file1" "$file2" > grep_output.txt

                        # Сравнение результатов
                        if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1;
                        then
                            let "COUNTER++"
                            let "SUCCESS++"
                            echo "$COUNTER - Success"
                        else 
                            let "COUNTER++"
                            let "FAIL++"
                            echo "$FAIL - Fail"
                        fi
                        # Удаление временных файлов
                        rm s21grep_output.txt
                        rm grep_output.txt
                    done
                fi
            done
        done
    done
done
# FLAG -e TESTING
for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for flag1 in "${inputs[@]}"
        do
            for tem in "${template[@]}"
            do
                echo ""
                echo "-e $tem -$flag1 $file1 $file2:"
                # Выполнение вашей программы
                ./s21_grep "-e" "$tem" "-$flag1" "$file1" "$file2" > s21grep_output.txt
                # Выполнение оригинального grep
                grep "-e" "$tem" "-$flag1" "$file1" "$file2" > grep_output.txt

                # Сравнение результатов
                if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1;
                then
                    let "COUNTER++"
                    let "SUCCESS++"
                    echo "$COUNTER - Success"
                else 
                    let "COUNTER++"
                    let "FAIL++"
                    echo "$FAIL - Fail"
                fi
                # Удаление временных файлов
                rm s21grep_output.txt
                rm grep_output.txt
            done
        done
    done
done

# FLAG -f TESTING
for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for flag1 in "${inputs[@]}"
        do
            for pat in "${patterns[@]}"
            do
                echo ""
                echo "-f $pat -$flag1 $file1 $file2:"
                # Выполнение вашей программы
                ./s21_grep "-f" "$pat" "-$flag1" "$file1" "$file2" > s21grep_output.txt
                # Выполнение оригинального grep
                grep "-f" "$pat" "-$flag1" "$file1" "$file2" > grep_output.txt

                # Сравнение результатов
                if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1;
                then
                    let "COUNTER++"
                    let "SUCCESS++"
                    echo "$COUNTER - Success"
                else 
                    let "COUNTER++"
                    let "FAIL++"
                    echo "$FAIL - Fail"
                fi
                # Удаление временных файлов
                rm s21grep_output.txt
                rm grep_output.txt
            done
        done
    done
done

for file1 in "${files[@]}"
do
    for file2 in "${files[@]}"
    do
        for flag1 in "${inputs[@]}"
        do
            for flag2 in "${inputs[@]}"
            do
                for flag3 in "${inputs[@]}"
                do
                    if [ $flag1 != $flag2 ] && [ $flag1 != $flag3 ] && [ $flag2 != $flag3 ]
                    then
                        for tem in "${template[@]}"
                        do
                            echo ""
                            echo "-$flag1$flag2$flag3 $tem $file1 $file2:"
                            # Выполнение вашей программы
                            ./s21_grep "-$flag1" "-$flag2" "-$flag3" "$tem" "$file1" "$file2" > s21grep_output.txt
                            # Выполнение оригинального grep
                            grep "-$flag1" "-$flag2" "-$flag3" "$tem" "$file1" "$file2" > grep_output.txt

                            # Сравнение результатов
                            if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1;
                            then
                                let "COUNTER++"
                                let "SUCCESS++"
                                echo "$COUNTER - Success"
                            else 
                                let "COUNTER++"
                                let "FAIL++"
                                echo "$FAIL - Fail"
                            fi
                            # Удаление временных файлов
                            rm s21grep_output.txt
                            rm grep_output.txt
                        done
                    fi
                done    
            done
        done
    done
done


echo ""
echo "Total: $COUNTER, Success: $SUCCESS, Fail: $FAIL"
echo ""