#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace cxx = __gnu_cxx;
namespace pbds = __gnu_pbds;

using PII = std::pair<int, int>;

/// @brief   优先队列
using Heap = pbds::priority_queue<PII, std::greater<PII>, pbds::pairing_heap_tag>;
using Pit = Heap::point_iterator;
void use_PriQue() {
    // 中间那个是仿函数类，类似于 std::greater
    // 小根堆
    // __gnu_pbds::priority_queue<PII, std::greater<PII>, __gnu_pbds::thin_heap_tag> q; // 斐波那契堆
    
    // Dijkstra
    int n, m; std::cin>>n>>m;
    std::vector<std::vector<PII>> adj(n+1);
    while(m--) {
        int u,v,w; std::cin>>u>>v>>w;
        adj[u].emplace_back(v, w);
    }

    Heap q; // 配对堆
    std::vector<int> dis(n+1);
    std::vector<Pit> it(n+1);
    dis[1] = 0;
    it[1] = q.push({0, 1});
    while(!q.empty()) {
        auto [uDis, u] = q.top(); q.pop();
        for(auto &[v,w]:adj[u]) {
            if(dis[v] <= uDis+w) continue;
            dis[v] = uDis+w;
            if(it[v]!=NULL) q.modify(it[v], {dis[v], v});
            else it[v] = q.push({dis[v], v}); // push 有返回那个值的指针
        }
    }

    Heap q1, q2;
    q1.join(q2); // 复杂度 O(log n), 可以代替左偏树
    // 此时 q2 为空
}

// 如果要手写仿函数类的话 
template <typename T>
struct cmp {
    constexpr bool operator()(const T &lhs, const T &rhs) {
        return lhs < rhs;
    }
};


/// @brief  平衡树
/// @param  1st key 比较类型
/// @param  2nd value 值的类型, null_type 表示无映射(参考 set 和 map)
/// @param  3rd 仿函数类
/// @param  4th 平衡树类型, rb_tree_tag 表示红黑树
/// @param  5th 元素维护策略
using Tree = pbds::tree<int, pbds::null_type, std::less<int>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;
void use_Tree() {
    Tree tr;
    for(int i=1; i<99; ++i) tr.insert(i);
    
    int k; std::cin>>k;
    auto it1 = tr.find_by_order(k); // k in [0,siz)
    int rank = tr.order_of_key(k); // 严格比 x 小(满足仿函数为true)的元素个数, 
    auto it2 = tr.lower_bound(k); // 求大于等于 x 的最小值
    // auto it2 = tr.upper_bound(k); // 求等于 x 的最小值
    
    Tree R;
    tr.split(k, R); // 所有 lower_bound 的都到 R (R原有清空)
}