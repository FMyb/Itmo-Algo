#include <stdio.h>
#include <assert.h>

using namespace std;

struct Node {
    Node *next;
    int val;

    Node(int val_, Node *next_) {
        next = next_;
        val = val_;
    }
};

struct List {
    Node *last = nullptr;
    Node *head = nullptr;
    int size = 0;

    void push(int val) {
        if (size == 0) {
            last = new Node(val, nullptr);
            head = last;
            size++;
            return;
        }
        Node *x = new Node(val, nullptr);
        last->next = x;
        size++;
        last = x;
    }

    int pop() {
        assert(size > 0);
        int ans = head->val;
        head = head->next;
        size--;
        return ans;
    }
};

int main() {
    List queue;
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        char c;
        scanf("%c", &c);
        if (c == '+') {
            int x;
            scanf("%d\n", &x);
            queue.push(x);
        } else {
            scanf("%c", &c);
            printf("%d\n", queue.pop());
        }
    }
}
