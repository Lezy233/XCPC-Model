#include <bits/stdc++.h>

namespace DataMaker {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

	/// @brief 返回 [1, n] 内的一个随机数
	template <class T>
	T rdT(const T n) {
		return rng()%n+1;
	}
	
	/// @brief 返回 [0, n) 内的一个随机数
	template <class T>
	T rdB(const T n) {
		return rng()%n;
	}
	
	/// @brief 提供一个长度为 _n, [1, MAXN] 的随机数组
	template <class T>
	std::vector<T> getArr(size_t _n, T MAXN) {
		std::vector<T> ans(_n);
		for(auto &i:ans) i = rdT(MAXN);
		return ans;
	}

	#pragma region getTree
	/// @brief 提供一颗树
	/// @param _n 点个数
	/// @param indexed 下标从几开始
	std::vector<std::pair<int,int>> getTree(size_t _n, int indexed = 1) {
		std::vector<std::pair<int,int>> ans;
		
		std::vector<int> Set(_n);
		std::iota(Set.begin(), Set.end(), 0);
		auto findSet = [&Set](auto self, int x)->int {
			return x==Set[x]? x : Set[x] = self(self, Set[x]);
		};

		int n = _n;
		while(ans.size() < n-1) {
			int u = rdB(n), v = rdB(n);
			int su = findSet(findSet, u), sv = findSet(findSet, v);
			if(su==sv) continue;
			ans.emplace_back(u+indexed, v+indexed);
			Set[su] = sv;
		}
		return ans;
	}
	#pragma endregion

	#pragma region getGraph
	/// @brief 提供一个无自环的保证联通的图, [u,v,w]
	/// @param _n 点个数
	/// @param indexed 下标从几开始
	/// @param mulEdges 是否含有重边
	std::vector<std::tuple<int, int>> getGraph(size_t _n, int indexed = 1, bool mulEdges = false) {
		std::vector<std::tuple<int, int>> ans;

		std::vector<int> Set(_n);
		std::iota(Set.begin(), Set.end(), 0);
		auto findSet = [&Set](auto self, int x)->int {
			return x==Set[x]? x : Set[x] = self(self, Set[x]);
		};
		
		int n = _n;
		int cnt = 0;
		std::set<std::pair<int, int>> st;
		while(cnt < n-1) {
			int u = rdB(n), v = rdB(n);
			if(u == v) continue;
			if(!mulEdges && st.contains(std::minmax(u, v))) continue;
			int su = findSet(findSet, u), sv = findSet(findSet, v);
			if(su != sv) {
				++cnt;
				Set[su] = sv;
			}
			
			ans.emplace_back(u+indexed, v+indexed);
			if(!mulEdges) st.emplace(std::minmax(u, v));
		}
		return ans;
	}

	/// @brief 提供一个无自环的保证联通的图, [u,v,w]
	/// @param _n 点个数
	/// @param maxT 边权范围 [1, maxT]
	/// @param indexed 下标从几开始
	template <class T>
	std::vector<std::tuple<int, int, T>> getGraph(size_t _n, const T maxT, int indexed = 1) {
		std::vector<std::tuple<int, int, T>> ans;

		std::vector<int> Set(_n);
		std::iota(Set.begin(), Set.end(), 0);
		auto findSet = [&Set](auto self, int x)->int {
			return x==Set[x]? x : Set[x] = self(self, Set[x]);
		};
		
		int n = _n;
		int cnt = 0;
		while(cnt < n-1) {
			int u = rdB(n), v = rdB(n);
			if(u == v) continue;
			int su = findSet(findSet, u), sv = findSet(findSet, v);
			if(su != sv) ++cnt;
			
			T w = rdT(maxT);
			ans.emplace_back(u+indexed, v+indexed, w);
		}
		return ans;
	}
	#pragma endregion

	/// @brief 提供一个稠密图
	/// @param _n 点个数
	/// @param maxT 边权范围 [1, maxT]
	/// @param indexed 下标从几开始
	template <class T>
	std::vector<std::vector<T>> getDenseGraph(size_t _n, const T maxT = std::numeric_limits<T>::max(), int indexed = 1) {
		std::vector<std::vector<T>> ans(_n+indexed, std::vector<T>(_n+indexed));
		for(int i=indexed; i<_n+indexed; ++i)
			for(int j=indexed; j<_n+indexed; ++j)
				if(i != j) ans[i][j] = rdT(maxT);
		return ans;
	}


	/// @brief	提供一个长度为 n 的随机字符串
	std::string getStr(size_t n, const char bas = 'a') {
		std::string res = "";
		for(size_t i=0; i<n; ++i) res += rng()%26+bas;
		return res;
	}
} // namespace DataMaker
using namespace DataMaker;

using std::endl;
#define ALL(x) x.begin(), x.end()

constexpr int T=1;
constexpr int N = 10, M = 3, Q = 5;
using ll = long long;
constexpr int MAXN = 1e1;
constexpr ll MAXN2 = 2e14;
constexpr int MOD = 998'244'353;

int main()
{
	// std::cout << T << endl;

}