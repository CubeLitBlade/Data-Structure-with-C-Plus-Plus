#pragma once
#include "DataStructure.h"
#include <algorithm>

namespace DataStructure
{
	template <typename T>
	class SeqListIterator : public DataStructureIterator<T>
	{
	public:
		SeqListIterator(T* ptr) : m_ptr(ptr) {};    // 创建指向特定元素的迭代器。
		T& operator*() override { return *m_ptr; }    // 重载 * 运算符返回对元素的引用。
		const T& operator*() const override { return *m_ptr; }    // 重载 * 运算符对元素的 const 引用。

		// 重载前置 ++ 运算符。迭代器向后移动后返回。
		SeqListIterator& operator++() override
		{
			++m_ptr;
			return *this;
		}

		// 重载后置 ++ 运算符。返回当前迭代器的副本并向后移动。
		SeqListIterator& operator++(int) override
		{
			SeqListIterator<T> it = *this;
			++*this;
			return it;
		}

		// 重载 != 运算符。判断两个迭代器是否指向同一元素。
		bool operator!=(const DataStructureIterator<T>& target) const override
		{
			const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target);
			return m_ptr != temp.m_ptr;
		}

		// 重载 == 运算符。判断两个迭代器是否指向同一元素。
		bool operator==(const DataStructureIterator<T>& target) const override
		{
			const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target);
			return m_ptr == temp.m_ptr;
		}

	private:
		T* m_ptr = nullptr;    // 当前迭代器指向的元素的地址。
	};

	// 顺序表类，派生自数据结构类。
	template <typename T>
	class SeqList : public DataStructure<T>
	{
	public:
		SeqList(size_t size);
		SeqList(T* target, size_t size);
		SeqList(const SeqList& target);
		~SeqList() override;
		SeqList& operator=(SeqList target);

		SeqListIterator<T> begin() { return SeqListIterator<T>(&this->m_data[0]); }
		SeqListIterator<T> end() { return SeqListIterator<T>(&this->m_data[this->m_size]); }

		bool empty() const override;
		size_t length() const override;
		size_t size() const override;
		SeqListIterator<T> find(const T& target) const;
		const T& get(size_t index) const override;
		bool set(size_t index, const T& target) override;
		bool add(const T& target) override;

		bool insert(size_t index, const T& target);
		bool remove(size_t index);
		void reset();
	};

	// 根据给定的容量创建空顺序表。若指定容量为 0 ，抛出 std::invalid_argument 异常。
	template <typename T>
	SeqList<T>::SeqList(size_t size)
	{
		if (size == 0)
		{
			throw std::invalid_argument(DataStructureException::ZERO_UNACCEPTABLE);
		}
		else
		{
			// 为顺序表分配空间，并且初始化其成员。
			this->m_data = new T[size];
			this->m_length = 0;
			this->m_size = size;

		}
	}

	// 由数组创建顺序表。若传递的指针为 nullptr 或指定容量为 0 ，抛出 std::invalid_argument 异常。
	template <typename T>
	SeqList<T>::SeqList(T* target, size_t size)
	{
		if (target == nullptr)
		{
			throw std::invalid_argument(DataStructureException::NULLPTR_PARAMETER);
		}
		else if (size == 0)
		{
			throw std::invalid_argument(DataStructureException::ZERO_UNACCEPTABLE);
		}
		else
		{
			// 为顺序表分配空间，并且初始化其成员。
			this->m_size = size;
			this->m_length = size;
			this->m_data = new T[size];

			// 将数组中的元素深拷贝到顺序表
			for (size_t i = 0; i < size; i++)
			{
				this->m_data[i] = target[i];
			}
		}

	}

	// 顺序表的复制构造函数。
	template <typename T>
	SeqList<T>::SeqList(const SeqList& target)
	{
		// 为顺序表分配空间，并且初始化其成员。
		this->m_size = target.size();
		this->m_length = target.length();
		this->m_data = new T[this->m_size];

		// 迭代器遍历并依次赋值。
		for (SeqListIterator<T> it1 = begin(), it2 = target.begin(); it1 != end() && it2 != target.end(); ++it1, ++it2)
		{
			*it1.m_ptr = *it2.m_ptr;
		}
	}

	// 删除顺序表，并释放所占用的内存空间。
	template <typename T>
	SeqList<T>::~SeqList()
	{
		delete[] this->m_data;		// 释放空间。
		this->m_data = nullptr;	// 将指针置空。
	}

	// 完成 SeqList 之间的赋值。
	template <typename T>
	SeqList<T>& SeqList<T>::operator=(SeqList target)
	{
		std::swap(*this, target);
		return *this;
	}

	// 判断顺序表是否为空表。若为空表，返回 true；否则返回 false。
	template <typename T>
	bool SeqList<T>::empty() const
	{
		return this->m_length == 0;
	}

	// 获取顺序表的长度（即表内的元素个数）。
	template <typename T>
	size_t SeqList<T>::length() const
	{
		return this->m_length;
	}

	// 获取顺序表的容量（即顺序表的最大长度）。
	template <typename T>
	size_t SeqList<T>::size() const
	{
		return this->m_size;
	}

	// 返回指向第一个指定元素的迭代器。若不存在，返回 SeqList<T>.end() 。
	template <typename T>
	SeqListIterator<T> SeqList<T>::find(const T& target) const
	{
		for (SeqListIterator<T> it = begin(); it != end(); ++it)
		{
			if (*it == target)
				return it;
		}
		return end();
	}

	// 获取顺序表特定下标的元素。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	const T& SeqList<T>::get(size_t index) const
	{
		if (index >= this->m_length)
		{
			// 下标超出范围时，抛出 std::out_of_range 异常。
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			return this->m_data[index];
		}
	}

	// 设置特定下标的元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	bool SeqList<T>::set(size_t index, const T& target)
	{
		if (index >= this->m_length)
		{
			// 下标超出范围时，抛出 std::out_of_range 异常。
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			this->m_data[index] = target;
			return true;
		}
	}

	// 从顺序表尾部插入元素。成功返回 true ，失败返回 false 。
	template<typename T>
	bool SeqList<T>::add(const T& target)
	{
		if (this->m_length == this->m_size)
		{
			return false;
		}
		else
		{
			this->m_data[this->m_length] = target;
			++this->m_length;
			return true;
		}
	}

	// 从相应下标处插入元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	bool SeqList<T>::insert(size_t index, const T& target)
	{
		if (this->m_length == this->m_size)
		{
			return false;
		}
		else if (index > this->m_length)
		{
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			// 从顺序表末尾依次将元素后移，达到下标处或 size_t 类型向下溢出时停止。
			for (size_t i = this->m_length - 1; i >= index && i != static_cast<size_t>(-1); --i)
			{
				this->m_data[i + 1] = this->m_data[i];
			}
			// 插入指定的元素。
			this->m_data[index] = target;
			++this->m_length;
			return true;
		}
	}

	// 移除特定下标处的元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	bool SeqList<T>::remove(size_t index)
	{
		if (index >= this->m_length)
		{
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			for (size_t i = index; i < this->m_length - 1; i++)
			{
				this->m_data[i] = this->m_data[i + 1];
			}
			--this->m_length;
			return true;
		}
	}

	// 重置顺序表，将释放顺序表的内存。当你在使用此顺序表类时捕获任何异常，请调用此方法以避免内存泄漏。
	template <typename T>
	void SeqList<T>::reset()
	{
		delete[] this->m_data;
		this->m_data = nullptr;
		this->m_length = 0;
		this->m_size = 0;
	}
}