// Luogu P3375
#include <bits/stdc++.h>
#define endl "\n"

void getNext(const std::string &S, std::vector<int> &nxt) {
    nxt.assign(S.size()+1, 0);
    nxt[0] = nxt[1] = 0;
    for (int i = 1; i < S.size(); ++i) {
        int j = nxt[i];
        while(j && S[i] != S[j]) j = nxt[j];
        nxt[i+1] = S[i] == S[j] ? j + 1 : 0;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string S1, S2; std::cin >> S1 >> S2;
    std::vector<int> next;
    getNext(S2, next);

    for (int i = 0, j = 0; i < S1.size(); ++i) {
        while (j && S1[i] != S2[j]) j = next[j];
        if (S1[i] == S2[j]) ++j;
        if (j == S2.size()) {
            std::cout << i-S2.size()+2 << endl;
            j = next[j];
        }
    }
    for (int i = 1; i <= S2.size(); ++i)
        std::cout << next[i] << " ";
    return 0;
}