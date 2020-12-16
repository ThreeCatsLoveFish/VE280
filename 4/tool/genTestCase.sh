#!/bin/bash

function generate () {
    MAX_VARS=$((RANDOM % 49 + 1))
    MAX_CLAUSES=$((RANDOM % 99 + 1))
    TIMES=$((RANDOM % 99 + 1))

    echo $MAX_VARS $MAX_CLAUSES >> $1
    for ((i=0; i<$MAX_CLAUSES; i++)); do
        for ((j=0; j<(RANDOM % 49 + 1); j++)); do
            if [ $j -gt 0 ]; then
                echo -n " | "  >> $1
            fi
            if [ $((RANDOM % 2)) -eq 1 ]; then
                echo -n "-" >> $1
            fi
            echo -n "x" >> $1
            echo -n "$((RANDOM%$MAX_VARS))" >> $1
        done
        echo "" >> $1
    done

    for ((i=0; i<$TIMES; i++)); do
        case $((RANDOM % 3)) in
            0)
                echo "EVAL" >> $1
                for ((j=0; j<$MAX_VARS; j++)); do
                    if [ $j -gt 0 ]; then
                        echo -n " " >> $1
                    fi
                    echo -n "$((RANDOM % 2)) " >> $1
                done
                echo "" >> $1
            ;;
            1)
                echo "SAT" >> $1
            ;;
            2)
                echo "PRINT" >> $1
            ;;
        esac

    done

    echo "EXIT" >> $1
}

for ((times=0; times<10; times++)); do
    file="./test/db/case$times"
    rm $file
    generate $file
done
