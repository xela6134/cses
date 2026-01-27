#!/bin/dash

FILENAME="$1"

git add .
git commit -m "Solution for $FILENAME"
git push
