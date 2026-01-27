#!/bin/dash

FILENAME="$1.cpp"

if [ -f "$FILENAME" ]; then
    echo "Error: $FILENAME already exists!"
    exit 1
fi

cat <<EOF > "$FILENAME"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    
    return 0;
}
EOF
