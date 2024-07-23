// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) return nullptr;
        Node* curr = head;
        while (curr) {
            if (curr->child) {
                Node* next = curr->next;
                Node* childHead = flatten(curr->child);
                
                curr->next = childHead;
                childHead->prev = curr;
                curr->child = nullptr;

                Node* childEnd = childHead; //child의 마지막 찾기
                while (childEnd->next) {
                    childEnd = childEnd->next;
                }

                if (next) {
                    childEnd->next = next;
                    next->prev = childEnd;
                }
            }
            curr = curr->next;
        }
        return head;
    }
};