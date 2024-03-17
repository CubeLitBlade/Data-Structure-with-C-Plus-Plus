# SeqList-AC1

## 问题

- 假设一个顺序表 `L` 中的所有元素为整数，设计一个算法调整该顺序表，使其中所有小于零的元素放在所有大于或等于零的元素的前面。

## main.cpp

在 `main.cpp` 中存在以下函数。

|函数原型|简介|
|:-----:|:-:|
|`SeqList_AC1::void PrefixNegative(DataStructure::SeqList<int>& target);`             |一种稳定的将所给定的 `int` 类型的 `SeqList` 中的负数前置的算法，保证元素间的相对顺序。|
|`SeqList_AC1::void QuickPrefixNegativeIterator(DataStructure::SeqList<int>& target);`|快速但不稳定的将所给定的 `int` 类型的 `SeqList` 中的负数快速前置的算法，即无法保证元素间的相对顺序。|
|`int main(void);`                                                                    |生成随机数对以上两种算法进行测试。|
