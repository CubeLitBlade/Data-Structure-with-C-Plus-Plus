#include "../Data Structure/SeqList.hpp"
#include <iostream>

int main(void)
{
    char a[] = {'4', '9', '2', '8', '0', '5', '4', '6', '7', '9'}; ///< 初始化字符数组，用于测试类。
    DataStructure::SeqList<char> L = DataStructure::SeqList(a, 10); ///< 通过数组构造SeqList。

    /** 依次输出 SeqList 的各元素。*/
    std::cout << "Original SeqList: " << std::endl;
    for (size_t i = 0; i < L.Length(); i++)
    {
        std::cout << L.Get(i) << " ";
    }

    /** 遍历 SeqList ，删除'1'到'5'之间的元素。*/
    for (int i = 0; i < L.Length(); i++)
    {
        if (L.Get(i) >= '1' && L.Get(i) <= '5')
        {
            L.Remove(i);
            i--; ///< 删除元素后，为了保证每个元素被遍历到，下标自减1.
        }
    }

    /** 依次输出改变后的 SeqList 的各元素。*/
    std::cout << std::endl << "Changed SeqList: " << std::endl;
    for (size_t i = 0; i < L.Length(); i++)
    {
        std::cout << L.Get(i) << " ";
    }

    return 0;
}
