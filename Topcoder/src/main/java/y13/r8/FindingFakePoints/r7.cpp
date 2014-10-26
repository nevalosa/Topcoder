/*
 * grafs.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: a-grigoriev
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stdio.h>

using namespace std;

class cmp {
    const vector<pair<int, int> > * data;
    int status;
public:

    cmp(const vector<pair<int, int> > & aData, int aStatus) : data(&aData), status(aStatus) {
    }

    bool operator()(const int & ai, const int & bi) const {
        const pair<int, int> & a = data->operator[](ai);
        const pair<int, int> & b = data->operator[](bi);

        switch (status) {
            case 0:
            {
                if (a.first < b.first)return true;
                else if ((a.first == b.first) && (a.second < b.second))return true;
                else return false;
                break;
            }
            case 1:
            {
                if (a.first < b.first)return true;
                else if ((a.first == b.first) && (a.second > b.second))return true;
                else return false;
                break;
            }
            case 2:
            {
                if (a.first > b.first)return true;
                else if ((a.first == b.first) && (a.second < b.second))return true;
                else return false;
                break;
            }
            case 3:
            {
                if (a.first > b.first)return true;
                else if ((a.first == b.first) && (a.second > b.second))return true;
                else return false;
                break;
            }

            case 4:
            {
                if (a.second < b.second)return true;
                else if ((a.second == b.second) && (a.first < b.first))return true;
                else return false;
                break;
            }
            case 5:
            {
                if (a.second < b.second)return true;
                else if ((a.second == b.second) && (a.first > b.first))return true;
                else return false;
                break;
            }
            case 6:
            {
                if (a.second > b.second)return true;
                else if ((a.second == b.second) && (a.first < b.first))return true;
                else return false;
                break;
            }
            case 7:
            {
                if (a.second > b.second)return true;
                else if ((a.second == b.second) && (a.first > b.first))return true;
                else return false;
                break;
            }
        }
        return false;
    }
};

class Rect {
    int left, right, top, bottom;
public:

    Rect() : left(1000000001), right(-1000000001), top(1000000001), bottom(-1000000001) {
    }

    ~Rect() {
    }

    int getSide()const {
        return max(right - left, bottom - top);
    }

    void push(const pair<int, int> & a) {
        if (left > a.first)left = a.first;
        if (right < a.first)right = a.first;
        if (top > a.second)top = a.second;
        if (bottom < a.second)bottom = a.second;
    }

    void combine(const Rect & other) {
        left = min(left, other.left);
        top = min(top, other.top);
        right = max(right, other.right);
        bottom = max(bottom, other.bottom);
    }
};

int answer(const vector<pair<int, int> > & a) {
    if (a.size() <= 4)return 0;
    vector<priority_queue<int, vector<int>, cmp > > Q;
    for (int i = 0; i < 8; ++i)
        Q.push_back(priority_queue<int, vector<int>, cmp >(cmp(a, i)));

    for (int i = 0; i < a.size(); ++i)
        for (int k = 0; k < Q.size(); ++k) {
            Q[k].push(i);
            if (Q[k].size() > 3)Q[k].pop();
        }

    set<int> s;
    for (int i = 0; i < Q.size(); ++i)
        while (!Q[i].empty()) {
            s.insert(Q[i].top());
            Q[i].pop();
        }

    Rect pure;
    for (int i = 0; i < a.size(); ++i)
        if (s.find(i) == s.end())pure.push(a[i]);

    vector<int> e(s.begin(), s.end());

    int best = 1000000000;

    for (int i1 = 0; i1 < e.size(); ++i1)
        for (int i2 = i1 + 1; i2 < e.size(); ++i2)
            for (int i3 = i2 + 1; i3 < e.size(); ++i3) {
                Rect r;
                for (int i = 0; i < e.size(); ++i) {
                    if ((i != i1) && (i != i2) && (i != i3)) {
                        r.push(a[e[i]]);
                    }
                }
                r.combine(pure);
                int newSide = r.getSide();
                if (best > newSide)best = newSide;
            }

    return best;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    //    freopen("/home/a-grigoriev/workspace/input.txt", "rt", stdin);

    int testCasesCount;
    cin >> testCasesCount;

    for (int testCase = 1; testCase <= testCasesCount; ++testCase) {
        int n;
        cin >> n;
        vector<pair<int, int> > data(n);
        for (int i = 0; i < n; ++i)
            cin >> data[i].first >> data[i].second;
        cout << "Case #" << testCase << endl << answer(data) << endl;
    }

    return 0;
}
