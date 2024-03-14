#pragma once
#include <stdexcept>

namespace DataStructure
{
	// 数据结构迭代器的基类。
	template <typename T>
	class DataStructureIterator
	{
	public:
		virtual ~DataStructureIterator() {};
		virtual T& operator*() = 0;
		virtual const T& operator*() const = 0;
		virtual DataStructureIterator& operator++() = 0;
		virtual DataStructureIterator& operator++(int) = 0;
		virtual bool operator!=(const DataStructureIterator<T>& target) const = 0;
		virtual bool operator==(const DataStructureIterator<T>& target) const = 0;
	};

	// 数据结构类的基类。
	template <typename T>
	class DataStructure
	{
	public:
		// 虚析构函数。
		virtual ~DataStructure(){}

		// 判定数据结构是否为空。
		virtual bool empty() const = 0;
		// 获取数据结构的长度。
		virtual size_t length() const = 0;
		// 获取数据结构的容量。
		virtual size_t size() const = 0;
		// 查找数据结构内第一个相应元素的下标。暂时无法解决派生的虚基类继承问题，目前不作为基类方法。
		//virtual DataStructureIterator<T> find(const T& target) const = 0;
		// 获取数据结构某下标的元素。
		virtual const T& get(size_t index) const = 0;
		// 从某下标写入数据。
		virtual bool set(size_t index, const T& target) = 0;
		// 在数据结构尾部插入数据。 
		virtual bool add(const T& target) = 0;


	protected:
		T* m_data = nullptr;	// 数据指针，默认为空指针。
		size_t m_length = 0;	// 数据结构的长度（所装载的元素个数）。
		size_t m_size = 0;	// 数据结构的容量（最大元素个数）。
	};
};

namespace DataStructureException
{
	const std::string NULLPTR_PARAMETER = "nullptr passed as parameter(s)";
	const std::string BAD_INDEX = "index out of range";
	const std::string ZERO_UNACCEPTABLE = "zero is unacceptable";
}