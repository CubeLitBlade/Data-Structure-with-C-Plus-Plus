#include "../DataSturcture/SeqList.h"
#include <iostream>

int main(void)
{
	size_t m = 0, n = 0, index = 0;
	std::cin >> n >> m;

	DataStructure::SeqList<size_t> kids = DataStructure::SeqList<size_t>(n);
	for (size_t i = 0; i < n; i++)
	{
		kids.insert(i, i + 1);
	}

	for (size_t i = 1; i <= m && !kids.empty(); i++, index++)
	{
		try
		{
			if (i == m)
			{
				i = 1;
				for (; index >= kids.length(); index -= kids.length());
				std::cout << kids.get(index) << " ";
				kids.remove(index);
			}
		}
		catch (std::out_of_range& e)
		{
			std::cerr << e.what();
			kids.reset();
			}
		}
	return 0;
}