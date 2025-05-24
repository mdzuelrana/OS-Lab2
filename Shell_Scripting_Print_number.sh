#!/bin/bash
echo "Even numbers from 1 to 10:"
for ((i=1; i<=10; i++)); do
    if (( i % 2 == 0 )); then
        echo "$i"
    fi
done
