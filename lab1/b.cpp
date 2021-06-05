#include <stdio.h>
#include <assert.h>

using namespace std;

struct Node {
    Node *prev;
    int val;

    Node(int val_, Node *prev_) {
        prev = prev_;
        val = val_;
    }
};

struct List {
    Node *last = nullptr;
    int size = 0;

    void push(int val) {
        if (size == 0) {
            last = new Node(val, nullptr);
            size++;
            return;
        }
        Node *x = new Node(val, last);
        size++;
        last = x;
    }

    int pop() {
        assert(size > 0);
        int ans = last->val;
        last = last->prev;
        return ans;
    }
};

int main() {
    List stack;
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        char c;
        scanf("%c", &c);
        if (c == '+') {
            int x;
            scanf("%d\n", &x);
            stack.push(x);
        } else {
            scanf("%c", &c);
            printf("%d\n", stack.pop());
        }
    }
}
