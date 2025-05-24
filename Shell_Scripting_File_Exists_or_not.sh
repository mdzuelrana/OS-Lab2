#!/bin/bash
echo "Enter filename:"
read fname
if [ -f "$fname" ]; then
    echo "File exists."
else
    echo "File not found."
fi
