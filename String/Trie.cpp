// Trie -> Retrieval Tree 字典树
#include <bits/stdc++.h>

class Trie {
private:
    bool isEnd;
    std::array<Trie*,26> son;
public:
    Trie(): isEnd(false) {
        son.fill(nullptr);
    }

    void insert(const std::string &word, char stand) {
        Trie* cur = this;
        for(auto &ch:word){
            if(cur->son[ch-stand]==nullptr) cur->son[ch-stand] = new Trie();
            cur = cur->son[ch-stand];
        }
        cur->isEnd=true;
    }

    bool search(const std::string &word, char stand) {
        Trie* cur = this;
        for(auto &ch:word){
            if(cur->son[ch-stand]==nullptr) return false;
            cur = cur->son[ch-stand];
        }
        return cur->isEnd;
    }

    bool startsWith(const std::string &prefix, char stand) {
        Trie* cur = this;
        for(auto &ch:prefix){
            if(cur->son[ch-stand]==nullptr) return false;
            cur = cur->son[ch-stand];
        }
        return true;
    }
};