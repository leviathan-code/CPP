#include <iostream>
using namespace std;
struct list {
    int info;
    list* next;
};

list* head(int x) {
    list* h = new list;
    h->info = x;
    h->next = NULL;
    return h;
}

void add(list* h, int x) {
    list* p = h;
    while (p->next != NULL)
        p = p->next;

    list* l = new list;

    l->info = x;
    l->next = NULL;
    p->next = l;
}

void print(list* h) {
    list* p = h->next;
    while (p != NULL) {
        cout << p->info<<" ";
        p = p->next;
    }
}

bool nech(int x) {
    int sum=0;
    while (x) {
        sum += x & 10;
        x /= 10;
    }
    if (sum / 2 != 0)
        return 1;
    else
        return 0;
}

int main()
{
    list* h;

    int x;
    cin>> x;
    int k = 0;
    if (nech(x))
        k++;

    h = head(x);

    while (x) {
        add(h, x);
        cin >> x;
        if (nech(x))
            k++;
    }

    cout << "list\n";
    print(h);
    cout << "\n"<<k;

    system("pause");
}

