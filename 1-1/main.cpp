#include "../DataSturcture/SeqList.h"
#include <iostream>

int main(void)
{
	char a[] = { '4','9','2','8','0','5','4','6','7','9' };		// 初始化字符数组，用于测试类。
	
	DataStructure::SeqList<char> L = DataStructure::SeqList<char>(a, 10);	// 通过数组构造SeqList。

	// 依次输出 SeqList 的各元素。
	std::cout << std::endl << "Original SeqList: " << std::endl;
	for (size_t i = 0; i < L.length(); i++)
	{
		std::cout << L.get(i) << " ";
	}

	// 遍历 SeqList ，删除'1'到'5'之间的元素。
	for (size_t i = 0; i < L.length(); i++)
	{
		if (L.get(i) >= '1' && L.get(i) <= '5')
		{
			L.remove(i);
			i--;			// 删除元素后，为了保证每个元素被遍历到，下标自减1.
		}
	}

	// 依次输出改变后的 SeqList 的各元素。
	std::cout << std::endl << "Changed SeqList: " << std::endl;
	for (size_t i = 0; i < L.length(); i++)
	{
		std::cout << L.get(i) << " ";
	}

	return 0;
}

