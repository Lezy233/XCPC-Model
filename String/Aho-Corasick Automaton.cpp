/**
 * @brief Aho-Corasick Automaton  AC自动机
 * @note 对于 n 个互不相同的模式串 T_i ，它们在文本串 S 中出现次数之和均摊复杂度为
 *       O(|S| sqrt{\sum |T_i|})
*/

// P5357
#include <bits/stdc++.h>

// @warning 这里使用并查集是因为题目不保证组成字典树的字符串不同
std::vector<int> Set;
int findSet(int x){ return x==Set[x]? x:Set[x]=findSet(Set[x]); }

class Trie {
private: 
    struct Node {
        std::array<int,26> son;
        int isEnd;
        int fail, ans;
        Node(): isEnd(-1), son{0}, fail(0), ans(0) {}
    };

    char bas;
    std::vector<Node> tr;
    std::vector<int> inDe;
public:
    Trie(char bas = 'a'): tr(1), bas(bas) {}

    void insert(const int id, const std::string &word) {
        int cur = 0;
        for(auto &ch:word) {
            if(!tr[cur].son[ch-bas])
                tr[cur].son[ch-bas] = tr.size(), tr.emplace_back();
            cur = tr[cur].son[ch-bas];
        }
        if(~tr[cur].isEnd) Set[id] = findSet(tr[cur].isEnd);
        else tr[cur].isEnd = id;
    }

    void build() {
        std::queue<int> que;
        inDe.assign(tr.size(), 0);
        for(auto &i:tr[0].son) if(i) que.emplace(i);
        while(que.size()) {
            int u = que.front(); que.pop();
            int nowFail = tr[u].fail;
            for(int id=0; id<26; ++id) {
                int &v = tr[u].son[id];
                if(v) {
                    tr[v].fail = tr[nowFail].son[id];
                    ++inDe[tr[nowFail].son[id]];
                    que.emplace(v);
                }
                else v = tr[nowFail].son[id];
            }
        }
    }

    void query(const std::string &S, std::vector<int> &cnt) {
        int ans = 0;
        for(int cur=0; auto &ch:S) {
            cur = tr[cur].son[ch-bas];
            ++tr[cur].ans;
        }

        std::queue<int> q;
        for(int i=1; i<tr.size(); ++i) if(!inDe[i]) q.emplace(i);
        while(q.size()) {
            int u = q.front(); q.pop();
            if(~tr[u].isEnd) cnt[tr[u].isEnd] = tr[u].ans;
            int v = tr[u].fail;
            tr[v].ans += tr[u].ans;
            if(--inDe[v]==0) q.emplace(v);
        }
    }
};

#define ALL(x) x.begin(),x.end()

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; std::cin>>n;
    Set.resize(n);
    std::iota(ALL(Set),0);

    Trie tr;
    std::vector<std::string> S(n);
    for(int i=0;i<n;++i){
        std::cin>>S[i];
        tr.insert(i, S[i]);
    }
    tr.build();
    std::string T; std::cin>>T;
    std::vector<int> cnt(n);
    tr.query(T,cnt);
    
    for(int i=0; i<n; ++i) std::cout<<cnt[findSet(i)]<<"\n";
    return 0;
}