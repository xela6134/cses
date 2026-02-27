#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 1. Custom Comparator for the Min-Heap
    // The priority_queue is a Max-Heap by default, so we invert the logic (greater >)
    // to make the smallest value appear at the top.
    struct CompareNode {
        bool operator()(ListNode* const& p1, ListNode* const& p2) {
            return p1->val > p2->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, CompareNode> minHeap;

        for (ListNode* list : lists) {
            if (list != nullptr) {
                minHeap.push(list);
            }
        }

        // Make dummy
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        while (!minHeap.empty()) {
            ListNode* smallest = minHeap.top();
            minHeap.pop();

            tail->next = smallest;
            tail = tail->next;

            if (smallest->next != nullptr) {
                minHeap.push(smallest->next);
            }
        }

        return dummy->next;
    }
};
