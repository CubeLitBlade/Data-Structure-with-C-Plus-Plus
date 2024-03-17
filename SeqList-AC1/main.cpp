#include "../Data Structure/SeqList.hpp"
#include <iostream>
#include <random>

namespace SeqList_AC1
{
	/**
	 * \brief 一种稳定的将所给定的 int 类型的 SeqList 中的负数前置的算法，保证元素间的相对顺序。
	 * \param target 待操作的 int 类型顺序表的引用。
	 */
	void PrefixNegative(DataStructure::SeqList<int>& target)
	{
		int temp = 0;
		size_t index = 0;    ///< 用于记录下一个负数插入位置的索引。
		for (size_t i = 0; i < target.length(); i++)
		{
			if (target.get(i) < 0)
			{
				temp = target.get(i);
				target.remove(i);
				target.insert(index, temp);    ///< 使用 index 作为索引而不是 0 ，可以维护负数的相对位置。
				index++;    ///< 将后续插入的负数下标后移。
			}
		}
	}

	/**
	 * \brief 快速但不稳定的将所给定的 int 类型的 SeqList 中的负数快速前置的算法，即无法保证元素间的相对顺序。
	 * \param target 待操作的 int 类型顺序表的引用。
	 * \note 此方法由 @KepWalk 提供。
	 */
	void QuickPrefixNegative(DataStructure::SeqList<int>& target)
	{
		DataStructure::SeqListIterator<int> left_it = target.begin(), right_it = ++target.begin();
		for (auto temp = target.begin(); temp != target.end(); ++temp)
		{
			if (right_it == target.end()) break;
			if (*temp >= 0)
			{
				left_it = temp;

				while (right_it != target.end())
				{
					if (*right_it < 0)
					{
						// 交换元素，并且退出遍历操作。
						std::swap(*left_it, *right_it);
						++right_it;
						break;
					}
					++right_it;
				}
			}
		}
	}
}

/**
 * \brief 对以上两种算法进行测试。
 * \return 如果程序没有异常，应当返回 0 .
 */
int main(void)
{
	int a[10];    ///< 创建数组用于生成 SeqList 。

	/** 创建随机数生成器。*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int>  dist(-10, 10);

	/** 生成 10 个 [-10, 10] 随机整数并将其公示。*/
	std::cout << "Original random integer sequence: " << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		a[i] = dist(gen);
		std::cout << a[i] << " ";
	}
	std::cout << std::endl << std::endl;

	/** 利用两种不同的算法排序。*/
	DataStructure::SeqList<int> L1 = DataStructure::SeqList<int>(a, 10);
	DataStructure::SeqList<int> L2 = DataStructure::SeqList<int>(a, 10);
	SeqList_AC1::PrefixNegative(L1);
	SeqList_AC1::QuickPrefixNegative(L2);

	/** 输出由 SeqList::PrefixNegative 排序的结果。*/
	std::cout << "Sorted by SeqList::PrefixNegative: " << std::endl;
	for (size_t i = 0; i < L1.length(); i++)
	{
		std::cout << L1.get(i) << " ";
	}
	std::cout << std::endl << std::endl;

	/** 输出由 SeqList::QuickPrefixNegative 排序的结果。*/
	std::cout << "Sorted by SeqList::QuickPrefixNegative(by @KepWalk): " << std::endl;
	for (size_t i = 0; i < L2.length(); i++)
	{
		std::cout << L2.get(i) << " ";
	}
	std::cout << std::endl << std::endl;

	return 0;
}
