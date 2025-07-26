#ifndef DATA_MAKER_H
#define DATA_MAKER_H

#include <bits/stdc++.h>

class Data_Maker {
private:
    std::mt19937 rng;
public:
    Data_Maker();
    
    /// @brief 返回 [1,n] 内的一个随机数
    template <class T>
    T rdT(const T n);

    /// @brief 提供一颗树
    /// @param indexed 下标从几开始
    std::vector<std::pair<int,int>> getTree(size_t n, int indexed = 1);
    
    /// @brief 提供一个无自环的保证联通的图
    /// @param indexed 下标从几开始
    /// @param maxT 权值上限
    template <class T>
    std::vector<std::tuple<int, int, T>> getGraph(size_t n, const T maxT = std::numeric_limits<T>::max(), int indexed = 1);
    
    /// @brief 提供一个长度为 n 的随机字符串
    /// @param bas 字母大写还是小写
    std::string getStr(size_t n, const char bas = 'a');
};

#endif // DATA_MAKER_H