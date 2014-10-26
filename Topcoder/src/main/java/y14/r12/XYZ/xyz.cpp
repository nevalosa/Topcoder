#include <stdio.h>

struct oper_rec {
    char op;
    int times;
};

int num;
oper_rec op[2000];

void swap(int &a, int &b) {
    
    int t = a;
    a = b;
    b = t;
    
    if (num > 0 && op[num - 1].op == 'X') {
        op[num - 1].times++;
    } else {
        op[num].op = 'X';
        op[num++].times = 1;
    }
    op[num].op = 'Z';
    op[num++].times = 1;
    op[num].op = 'Y';
    op[num++].times = 1;
}

void positive(int &a, int &b) {
    if (a < 0 && b > 0) {
        op[num].op = 'X';
        op[num++].times = -a / b + 1;
        a = a + b * op[num++].times;
    } else if (a > 0 && b < 0) {
        op[num].op = 'Z';
        op[num++].times = 1;
        b = a - b;
    } else if (a < 0 && b < 0) {
        if (a < b) {
            swap(a, b);
        }
        op[num].op = 'Y';
        op[num++].times = 1;
        a = a - b;
        op[num].op = 'Z';
        op[num++].times = 1;
        b = a - b;
    }
}

int getGCD(int a, int b) {
    if (a < b)
        swap(a, b);
    while (b != 0) {
        if (num > 0 && op[num - 1].op == 'Y') {
            op[num - 1].times += a / b;
        } else {
            op[num].op = 'Y';
            op[num++].times = a / b;
        }
        a %= b;
        swap(a, b);
    }
    return a;
}

bool get_k(int k, int b) // b should be gcd
{
    if (k % b != 0)
        return false;
    if (k > 0) {
        if (num > 0 && op[num - 1].op == 'X') {
            op[num - 1].times += k / b;
        } else {
            op[num].op = 'X';
            op[num++].times = k / b;
        }
    } else if (k < 0) {
        if (num > 0 && op[num - 1].op == 'Y') {
            op[num - 1].times += -k / b;
        } else {
            op[num].op = 'Y';
            op[num++].times = -k / b;
        }
    }
    return true;
}

int main() {
    int i, j, tc, a, b, k;
    int gcd;
    scanf("%d", &tc);
    for (i = 1; i <= tc; i++) {
        scanf("%d%d%d", &a, &b, &k);
        printf("Case #%d\n", i);
        if (a == k) {
            printf("YES\n");
            continue;
        }
        num = 0;
        positive(a, b);
        gcd = getGCD(a, b);
        a = gcd;
        b = 0;
        swap(a, b);
        if (k != 0 && !get_k(k, b))
            printf("NO\n");
        else {
            printf("YES\n");
            for (j = 0; j < num; j++) {
                printf("%c %d\n", op[j].op, op[j].times);
            }
        }
    }
    return 0;
}
