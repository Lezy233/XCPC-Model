/**
 * @brief   Palindrome Automaton, PAM, EER Tree, 回文自动机
*/

#include <bits/stdc++.h>

template <size_t CHARSETSZ=26>
class PAM {
private:
    struct Node {
        std::array<int, CHARSETSZ> son;
        int len, fail, cnt;

        Node() = default;
        Node(int len): len(len), fail(0), cnt(0), son{} {}
    };

    char bas;
    int Len; // length of S
    std::string S;
    std::vector<Node> tr; // 0->偶串, 1->奇串
    int now;

    int getFail(int id) {
        while(S[Len-tr[id].len-1]!=S[Len]) id = tr[id].fail;
        return id;
    }
public:
    PAM(char bas='a'): tr(0), bas(bas), S("#"), Len(0), now(0) {
        tr.emplace_back(0); tr.emplace_back(-1);
        tr[0].fail=1;
    }

    void insert(const char ch) {
        S += ch; ++Len;
        int nowFail = getFail(now);
        if(!tr[nowFail].son[ch-bas]){
            int id = tr.size();
            tr.emplace_back(tr[nowFail].len+2);
            tr[id].fail = tr[getFail(tr[nowFail].fail)].son[ch-bas];
            tr[nowFail].son[ch-bas] = id;
        }
        now = tr[nowFail].son[ch-bas];
        ++tr[now].cnt;
    }

    void insert(const std::string &word) {
        for(auto &ch:word) insert(ch);
    }

    long long solve() {
        long long ans = 0;
        for(int i=tr.size()-1; i>=0; --i)
            tr[tr[i].fail].cnt += tr[i].cnt;
        for(int i=1; i<tr.size(); ++i)
            ans = std::max(ans, 1LL*tr[i].len*tr[i].cnt);
        return ans;
    }
};