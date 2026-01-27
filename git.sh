#!/bin/dash

QNAME="$1"

git add .
git commit -m "Solution for $QNAME"
git push
