#include <bits/stdc++.h>
using namespace std;

struct Node {
    int r;
    string n;
    long long h;
    Node *l, *ri;
    Node(int rr, string nn, long long hh) : r(rr), n(nn), h(hh), l(NULL), ri(NULL) {}
};

Node* root = NULL;
int cnt = 0;

Node* findP(Node* c, int r) {
    if (!c) return NULL;
    if (c->r == r) return c;
    if (r < c->r) return findP(c->l, r);
    return findP(c->ri, r);
}

bool addP(int r, string n, long long h) {
    if (!root) {
        root = new Node(r, n, h);
        cnt++;
        return true;
    }
    Node* c = root;
    while (true) {
        if (r == c->r) return false;
        if (r < c->r) {
            if (!c->l) {
                c->l = new Node(r, n, h);
                cnt++;
                return true;
            }
            c = c->l;
        } else {
            if (!c->ri) {
                c->ri = new Node(r, n, h);
                cnt++;
                return true;
            }
            c = c->ri;
        }
    }
}

Node* minP(Node* c) {
    while (c && c->l) c = c->l;
    return c;
}

Node* delP(Node* c, int r, bool &ok) {
    if (!c) return NULL;
    if (r < c->r) c->l = delP(c->l, r, ok);
    else if (r > c->r) c->ri = delP(c->ri, r, ok);
    else {
        ok = true;
        if (!c->l && !c->ri) {
            delete c;
            return NULL;
        }
        if (!c->l || !c->ri) {
            Node* ch = c->l ? c->l : c->ri;
            delete c;
            return ch;
        }
        Node* s = minP(c->ri);
        c->r = s->r;
        c->n = s->n;
        c->h = s->h;
        c->ri = delP(c->ri, s->r, ok);
    }
    return c;
}

void printR(Node* c, int L, int R, bool &f) {
    if (!c) return;
    if (c->r > L) printR(c->l, L, R, f);
    if (c->r >= L && c->r <= R) {
        cout << c->r << " " << c->n << " " << c->h << "\n";
        f = true;
    }
    if (c->r < R) printR(c->ri, L, R, f);
}

int rankC(Node* c, int X) {
    if (!c) return 0;
    if (c->r >= X) return rankC(c->l, X);
    return 1 + rankC(c->l, X) + rankC(c->ri, X);
}

Node* kthP(Node* c, int &k) {
    if (!c) return NULL;
    Node* x = kthP(c->l, k);
    if (x) return x;
    k--;
    if (k == 0) return c;
    return kthP(c->ri, k);
}

Node* prevP(Node* c, int X) {
    Node* a = NULL;
    while (c) {
        if (c->r < X) {
            a = c;
            c = c->ri;
        } else c = c->l;
    }
    return a;
}

Node* nextP(Node* c, int X) {
    Node* a = NULL;
    while (c) {
        if (c->r > X) {
            a = c;
            c = c->l;
        } else c = c->ri;
    }
    return a;
}

int hgt(Node* c) {
    if (!c) return -1;
    return 1 + max(hgt(c->l), hgt(c->ri));
}

int leaf(Node* c) {
    if (!c) return 0;
    if (!c->l && !c->ri) return 1;
    return leaf(c->l) + leaf(c->ri);
}

int dist(Node* c, int t) {
    int d = 0;
    while (c && c->r != t) {
        if (t < c->r) c = c->l;
        else c = c->ri;
        d++;
    }
    return c ? d : -1;
}

Node* lcaP(Node* c, int a, int b) {
    while (c) {
        if (a < c->r && b < c->r) c = c->l;
        else if (a > c->r && b > c->r) c = c->ri;
        else return c;
    }
    return NULL;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    while (Q--) {
        string cmd;
        cin >> cmd;

        if (cmd == "JOIN") {
            int r; string n; long long h;
            cin >> r >> n >> h;
            if (addP(r, n, h)) cout << "JOINED\n";
            else cout << "DUPLICATE\n";
        }

        else if (cmd == "LEAVE") {
            int r;
            cin >> r;
            bool ok = false;
            root = delP(root, r, ok);
            if (!ok) cout << "NOT FOUND\n";
            else {
                cnt--;
                cout << "LEFT\n";
            }
        }

        else if (cmd == "STATUS") {
            int r;
            cin >> r;
            Node* p = findP(root, r);
            if (!p) cout << "NOT FOUND\n";
            else cout << p->r << " " << p->n << " " << p->h << "\n";
        }

        else if (cmd == "DAMAGE") {
            int r; long long a;
            cin >> r >> a;
            Node* p = findP(root, r);
            if (!p) cout << "NOT FOUND\n";
            else {
                p->h = max(0LL, p->h - a);
                cout << "DAMAGED " << p->h << "\n";
            }
        }

        else if (cmd == "HEAL") {
            int r; long long a;
            cin >> r >> a;
            Node* p = findP(root, r);
            if (!p) cout << "NOT FOUND\n";
            else {
                p->h += a;
                cout << "HEALED " << p->h << "\n";
            }
        }

        else if (cmd == "MATCH") {
            int X;
            cin >> X;
            if (!root) {
                cout << "EMPTY\n";
                continue;
            }

            Node* p = prevP(root, X);
            Node* s = nextP(root, X);

            Node* ans = NULL;
            if (p && s) {
                int d1 = abs(X - p->r);
                int d2 = abs(s->r - X);
                if (d1 <= d2) ans = p;
                else ans = s;
            } else if (p) ans = p;
            else ans = s;

            if (ans) cout << ans->r << " " << ans->n << " " << ans->h << "\n";
        }

        else if (cmd == "NEXT") {
            int X;
            cin >> X;
            Node* p = nextP(root, X);
            if (!p) cout << "NONE\n";
            else cout << p->r << " " << p->n << " " << p->h << "\n";
        }

        else if (cmd == "PREV") {
            int X;
            cin >> X;
            Node* p = prevP(root, X);
            if (!p) cout << "NONE\n";
            else cout << p->r << " " << p->n << " " << p->h << "\n";
        }

        else if (cmd == "RANGE") {
            int L, R;
            cin >> L >> R;
            bool f = false;
            printR(root, L, R, f);
            if (!f) cout << "EMPTY\n";
        }

        else if (cmd == "RANK") {
            int X;
            cin >> X;
            cout << rankC(root, X) << "\n";
        }

        else if (cmd == "KTH") {
            int k;
            cin >> k;
            if (k < 1 || k > cnt) cout << "OUT OF RANGE\n";
            else {
                int t = k;
                Node* p = kthP(root, t);
                cout << p->r << " " << p->n << " " << p->h << "\n";
            }
        }

        else if (cmd == "DUEL") {
            int A, B;
            cin >> A >> B;
            Node* a = findP(root, A);
            Node* b = findP(root, B);
            if (!a || !b) cout << "NOT FOUND\n";
            else {
                Node* c = lcaP(root, A, B);
                int d = dist(c, A) + dist(c, B);
                cout << "DIST " << d << "\n";
            }
        }

        else if (cmd == "STATS") {
            cout << "PLAYERS " << cnt << "\n";
            if (!root) {
                cout << "MIN NONE\n";
                cout << "MAX NONE\n";
                cout << "HEIGHT -1\n";
                cout << "LEAVES 0\n";
            } else {
                Node* mn = minP(root);
                Node* mx = root;
                while (mx->ri) mx = mx->ri;
                cout << "MIN " << mn->r << "\n";
                cout << "MAX " << mx->r << "\n";
                cout << "HEIGHT " << hgt(root) << "\n";
                cout << "LEAVES " << leaf(root) << "\n";
            }
        }
    }

    return 0;
}
