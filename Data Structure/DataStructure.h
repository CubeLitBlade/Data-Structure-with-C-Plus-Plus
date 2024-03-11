#pragma once
#include <stdexcept>

namespace DataStructure
{
	// 数据结构类的基类。
	template <typename T>
	class DataStructure
	{
	public:
		// 判定数据结构是否为空。
		virtual bool empty() const = 0;
		// 获取数据结构的长度。
		virtual size_t length() const = 0;
		// 获取数据结构的容量。
		virtual size_t size() const = 0;
		// 查找数据结构内第一个相应元素的下标。
		virtual size_t find(const T& target) const = 0;
		// 获取数据结构某下标的元素。
		virtual const T& get(size_t index) const = 0;
		// 从某下标写入数据。
		virtual bool set(size_t index, const T& target) = 0;
		
	protected:
		T* m_p = nullptr;	// 数据指针，默认为空指针。
		size_t m_length = 0;	// 数据结构的长度（所装载的元素个数）。
		size_t m_size = 0;	// 数据结构的容量（最大元素个数）。
	};
}

namespace DataStructureException
{
	const std::string NULLPTR_PARAMETER = "nullptr passed as parameter(s)";
	const std::string BAD_INDEX = "index out of range";
	const std::string ZERO_UNACCEPTABLE = "zero is unacceptable";
}