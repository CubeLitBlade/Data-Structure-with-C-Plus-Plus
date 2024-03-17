#include "../Data Structure/List.hpp"
#include <iostream>
#include <random>


/**
 * \brief 将目标链表给定索引的元素与其后一个元素交换位置。
 * \tparam T 元素类型。
 * \param index 给定的索引。
 * \param target 目标链表。
 */
template <typename T>
void SwapWithNext(size_t index, DataStructure::List<T>& target)
{
	for(auto it = target.begin(); it != target.end(); ++it, --index)
	{
		if(index == 0)
		{
			auto it_next = it.next();
			if(it.m_ptr->m_prev != nullptr)
			{
				it.m_ptr->m_prev->m_next = it_next.m_ptr;    ///< 如果索引的 prev 指针不是 nullptr，就将 prev 的 next 设为 it 的 next。
			}
			else
			{
				target.m_head = it_next.m_ptr;    ///< 否则，表示 it 是头结点，直接更改链表的头结点即可。
			}
			if(it_next.m_ptr->m_next != nullptr)    ///< 同理。
			{
				it_next.m_ptr->m_next->m_prev = it.m_ptr;
			}
			else
			{
				target.m_tail = it.m_ptr;
			}

			/** 分别更改这两个节点的 prev 和 next 使其指向正确即可。*/
			it.m_ptr->m_next = it_next.m_ptr->m_next;
			it_next.m_ptr->m_prev = it.m_ptr->m_prev;
			it.m_ptr->m_prev = it_next.m_ptr;
			it_next.m_ptr->m_next = it.m_ptr;
		}
	}
}

/**
 * \brief 对以上算法进行测试。
 * \return 如果程序没有异常，应当返回 0 .
 */
int main(void)
{

	size_t index = 0;
	DataStructure::List<int> L;
	size_t n = 0;

	/** 创建随机数生成器。*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int>  dist(-100, 100);

	/** 生成对应数目的随机数。*/
	std::cout << "Enter the number of random numbers: " << std::endl;
	std::cin >> n;

	std::cout << "Generated random numbers: " << std::endl;
	for (int i = 0; i < n; i++)
	{
		int value = dist(gen);
		std::cout << value << " ";
		L.add(value);
	}
	std::cout << std::endl;

	/** 调用函数交换顺序。*/
	std::cout << "Now enter an index: " << std::endl;
	std::cin >> index;
	if(index < n - 1)
	{
		SwapWithNext(index, L);

		std::cout << "Swapped numbers: " << std::endl;
		for (const auto value : L)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cerr << "Invalid index. ";    ///< 如果索引不在范围内，则输出此提示。
	}

	return 0;
}