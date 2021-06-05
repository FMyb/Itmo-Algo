#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <assert.h>

using namespace std;

struct Vector {
    int *arr = (int *) malloc(sizeof(int) * 1);
    int size = 1;
    int top = 0;
    int head = 0;

    void push(int x) {
        if (top == size) {
            int *temp = (int *) malloc(sizeof(int) * size);
            memcpy(temp, arr, sizeof(int) * size);
            free(arr);
            arr = (int *) malloc(sizeof(int) * size * 2);
            memcpy(arr, temp, sizeof(int) * size);
            free(temp);
            size *= 2;
        }
        arr[top] = x;
        top++;
    }

    int pop() {
        assert(top != head);
        int ans = arr[head];
        head++;
        if (size > 1 && head == size / 2) {
            int *temp = (int *) malloc(sizeof(int) * size / 2);
            memcpy(temp, arr + head, sizeof(int) * size / 2);
            free(arr);
            arr = (int *) malloc(sizeof(int) * size / 2);
            memcpy(arr, temp, sizeof(int) * size / 2);
            free(temp);
            size /= 2;
            head = 0;
            top -= size;
        }
        return ans;
    }
};

int main() {
    Vector queue;
    int n;

    scanf("%d", &n);
    if (n == 1) {
        return 0;
    }
    char c1;
    scanf("%c", &c1);
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
