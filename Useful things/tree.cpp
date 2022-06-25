#include <iostream>
using namespace std;

struct tree {
    int info;
    tree* l;
    tree* r;
};

void add(tree* t, int x) {
    tree* root = t;
    tree* pred = new tree;
    while (root != NULL) {
        pred = root;
        if (x < root->info)
            root = root->l;
        else
            root = root->r;
    }

    tree* p = new tree;
    p->info = x;
    p->l = NULL;
    p->r = NULL;

    if (x < pred->info)
        pred->l = p;
    else
        pred->r = p;
}

bool prost(int x) {
    int k = 0;
    for (int i = 1; i <= x; i++) {
        if (x % i == 0)
            k++;
    }
    if (k <= 2)
        return 1;
    else
        return 0;
}

int sum(tree* t) {

    if (t == NULL)
        return 0;

    if (t->l == NULL && t->r == NULL) {
        return t->info + sum(t->l) + sum(t->r);
    }
    else {
        return sum(t->l) + sum(t->r);
    }
}

int main()
{
    struct tree* t = new tree;
    int x;

    cin >> x;
    t->info = x;
    t->l = NULL;
    t->r = NULL;
    int s = 0;

    cin >> x;
    while (x) {
        add(t, x);
        cin >> x;
    }
    cout << endl;

    cout << endl;

    s = sum(t);

    cout << "sum of lists\n" << s;
    system("pause");
}

