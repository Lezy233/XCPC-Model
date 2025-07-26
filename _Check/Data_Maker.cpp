#include "Data_Maker.hpp"
#include <bits/stdc++.h>

Data_Maker::Data_Maker()
    : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

/// @brief 返回 [1,n] 内的一个随机数
template <class T>
T Data_Maker::rdT(const T n) {
	return rng()%n+1;
}

/**
 * @brief 提供一颗树
 * @param indexed 下标从几开始
 */
std::vector<std::pair<int,int>> Data_Maker::getTree(size_t _n, int indexed) {
	std::vector<std::pair<int,int>> ans;
	
	std::vector<int> Set(_n);
	std::iota(Set.begin(), Set.end(), 0);
	auto findSet = [&Set](auto self, int x)->int {
		return x==Set[x]? x : Set[x] = self(self, Set[x]);
	};

	int n = _n;
	while(ans.size() < n-1) {
		int u = rdT(n), v = rdT(n);
		int su = findSet(findSet, u), sv = findSet(findSet, v);
		if(su==sv) continue;
		ans.emplace_back(u+indexed, v+indexed);
		Set[su] = sv;
	}
	return ans;
}

/**
 * @brief 提供一个无自环的保证联通的图
 * @param indexed 下标从几开始
 */
template <class T>
std::vector<std::tuple<int, int, T>> Data_Maker::getGraph(size_t _n, const T maxT, int indexed) {
	std::vector<std::tuple<int, int, T>> ans;

	std::vector<int> Set(_n);
	std::iota(Set.begin(), Set.end(), 0);
	auto findSet = [&Set](auto self, int x)->int {
		return x==Set[x]? x : Set[x] = self(self, Set[x]);
	};
	
	int n = _n;
	int cnt = 0;
	while(cnt < n-1) {
		int u = rdT(n)-1, v = rdT(n)-1;
		int su = findSet(findSet, u), sv = findSet(findSet, v);
		if(su != sv) ++cnt;
		
		T w = rdT(maxT);
		ans.emplace_back(u+indexed, v+indexed, w);
	}
	return ans;
}

template std::vector<std::tuple<int, int, int>> Data_Maker::getGraph<int>(size_t, int, int);

/**
 * @brief	提供一个长度为 n 的随机字符串
 */
std::string Data_Maker::getStr(size_t n, const char bas) {
	std::string res = "";
	for(size_t i=0; i<n; ++i) res += rng()%26+bas;
	return res;
}