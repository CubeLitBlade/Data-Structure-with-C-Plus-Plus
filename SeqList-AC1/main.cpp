#include "../Data Structure/SeqList.h"
#include <iostream>
#include <random>

namespace SeqList_AC1
{
	// 一种稳定的将所给定的 int 类型的 SeqList 中的负数前置的算法，保证元素间的相对顺序。
	void PrefixNegative(DataStructure::SeqList<int>& target)
	{
		int temp = 0;
		size_t index = 0;    // 用于记录下一个负数插入位置的下标。
		for (size_t i = 0; i < target.length(); i++)
		{
			if (target.get(i) < 0)
			{
				temp = target.get(i);
				target.remove(i);
				target.insert(index, temp);    // 使用 index 作为下标而不是 0 ，可以维护负数的相对位置。
				index++;    // 将后续插入的负数下标后移。
			}
		}
	}

	// 快速但不稳定的将所给定的 int 类型的 SeqList 中的负数快速前置的算法，即无法保证元素间的相对顺序。
	void QuickPrefixNegative(DataStructure::SeqList<int>& target)    // 此方法由 @KepWalk 提供。
	{
		int temp = 0;
		size_t left = 0, right = 1;    // left 指定一个非负数，right 指定一个负数。如果均为有效下标，则两个下标指定的数需要被交换位置。
		for (int i = 0; i < target.length(); i++)
		{
			// 如果 right 已经遍历到 target.length()，则表示遍历结束。
			if (right >= target.length()) break;

			// 判断下标对应的数是否为非负数。
			if (target.get(i) >= 0) 
			{
				left = i;    // 如果是，则将 left 置为此下标，至此，下标区间 [left, right - 1] （闭区间）中均指定非负数。

				// 以 right 为下标遍历后续元素。
				for (; right < target.length(); right++)
				{
					// 如果存在负数，此时 left 指定一个非负数，right 指定一个负数，二者交换元素即可。
					if (target.get(right) < 0)
					{
						// 交换元素，并且退出遍历操作。
						temp = target.get(left);
						target.set(left, target.get(right));
						target.set(right, temp);
						right++;
						break;
					}
				}
			}
		}
	}
}

// 在 main 函数中对以上两种算法进行测试。
int main(void)
{
	// 创建数组用于生成 SeqList 。
	int a[10];

	// 创建随机数生成器。
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int>  dist(-10, 10);

	// 生成 10 个 [-10, 10] 随机整数并将其公示。
	std::cout << "Original random integer sequence: " << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		a[i] = dist(gen);
		std::cout << a[i] << " ";
	}
	std::cout << std::endl << std::endl;

	// 利用两种不同的算法排序。
	DataStructure::SeqList<int> L1 = DataStructure::SeqList<int>(a, 10);
	DataStructure::SeqList<int> L2 = DataStructure::SeqList<int>(a, 10);
	SeqList_AC1::PrefixNegative(L1);
	SeqList_AC1::QuickPrefixNegative(L2);

	// 输出由 SeqList::PrefixNegative 排序的结果。
	std::cout << "Sorted by SeqList::PrefixNegative: " << std::endl;
	for (size_t i = 0; i < L1.length(); i++)
	{
		std::cout << L1.get(i) << " ";
	}
	std::cout << std::endl << std::endl;

	// 输出由 SeqList::QuickPrefixNegative 排序的结果。
	std::cout << "Sorted by SeqList::QuickPrefixNegative(by @KepWalk): " << std::endl;
	for (size_t i = 0; i < L2.length(); i++)
	{
		std::cout << L2.get(i) << " ";
	}
	std::cout << std::endl << std::endl;
	return 0;
}
