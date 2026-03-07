#include <bits/stdc++.h>
using namespace std;

// "user1 rwx file1\n
// user2 r file2\n
// user3 rw- file3\n"
// -> {file2}

// "owner1 r fileA\n
// owner2 rx fileB\n
// owner3 r fileC\n" 
// -> {fileA, fileC}

// "userA rw fileX\n
// userB x fileY\n
// userC r fileZ\n" 
// -> {fileZ}

// "ownerX r file1\n
// ownerY r file2\n
// ownerZ r file3\n" 
// -> {file1, file2, file3}

// "user1 rwx fileX\n
// user2 rwx fileY\n
// user3 rwx fileZ\n"
// -> {}

vector<string> determine_read_only_files(const vector<string>& file_queries) {
    vector<string> result;

    // query is "user2 rwx fileY"
    for (auto& query : file_queries) {
        stringstream ss(query);
        string segment;
        vector<string> parts;

        while (getline(ss, segment, ' ')) {
            parts.push_back(segment);
        }

        bool has_r = (parts[1].find('r') != string::npos);
        bool has_w = (parts[1].find('w') != string::npos);
        bool has_x = (parts[1].find('x') != string::npos);

        if (has_r && !has_w && !has_x) {
            result.push_back(parts[2]);
        }
    }

    return result;
}
