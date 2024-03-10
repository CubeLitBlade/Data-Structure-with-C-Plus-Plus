#include "../DataSturcture/SeqList.h"
#include <iostream>

int main(void)
{
	// 初始化变量。n 为 kids 的数量；m 为被杀死的 kids 所报的数；index 为遍历时的下标。
	size_t m = 0, n = 0, index = 0;
	std::cin >> n >> m;

	// 根据输入的数量新建对应数量的 kids ，并且为其编号。
	DataStructure::SeqList<size_t> kids = DataStructure::SeqList<size_t>(n);
	for (size_t i = 0; i < n; i++)
	{
		kids.insert(i, i + 1);
	}

	// 仅当还有 kids 存活时开始循环点名。
	for (size_t i = 1; i <= m && !kids.empty(); i++, index++)
	{
		// 由于此代码段使用了 const T& SeqList.get(size_t index) 和 bool SeqList.remove(size_t index)；
		// 这些方法可能会抛出 std::out_of_range 异常，因此我们需要尝试捕获这些异常。
		try
		{
			// 点到相应的 kids 时。
			if (i == m)
			{
				// 通过 for 循环将 index 修正到正确的位置。index 不可大于或等于 kids.length()，因此只需要不断减去 kids.length()。
				for (; index >= kids.length(); index -= kids.length());

				std::cout << kids.get(index) << " "; // 打印将被杀死的 kids 的序号。
				kids.remove(index);  // 杀死此 kids。

				i = 0;  // 重置计数器。
				index--;  // 由于删除了元素，索引值自减使循环结束后自增还原下标。
			}
		}
		catch (std::out_of_range& e)
		{
			// 当捕获到 std::out_of_range 异常时，输出错误信息，并且手动调用 void SeqList.reset() 方法释放内存，避免内存泄漏。
			std::cerr << e.what();
			kids.reset();
		}
	}
	return 0;
}