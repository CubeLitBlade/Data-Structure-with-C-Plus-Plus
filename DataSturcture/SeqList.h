#pragma once
#include "DataStructure.h"

namespace DataStructure
{
	// 顺序表类，派生自数据结构类。

	template <typename T>
	class SeqList : public DataStructure<T>
	{
	public:
		// 构造空顺序表。
		SeqList(size_t size);
		// 通过数组构建顺序表。
		SeqList(T* target, size_t size);
		// 析构顺序表。
		~SeqList();

		// 判断顺序表是否为空，覆写基类方法。
		bool empty() override;
		// 获取顺序表长度，覆写基类方法。
		size_t length() override;
		// 获取顺序表容量，覆写基类方法。
		size_t size() override;
		// 获取顺序表内某下标的元素，覆写基类方法。
		const T& get(size_t index) override;
		// 将元素写入某下标，覆写基类方法。
		bool set(size_t index, const T& target) override;
		// 查找顺序表内第一个某元素的下标，覆写基类方法。
		size_t find(const T& target) override;
		// 从下标处插入元素。
		bool insert(size_t index, const T& target);
		// 删除某下标处的元素。
		bool remove(size_t index);
		// 重置顺序表。
		void reset();
	};

	// 根据给定的容量创建空顺序表。若指定容量为 0 ，抛出 std::invalid_argument 异常。
	template <typename T>
	inline SeqList<T>::SeqList(size_t size)
	{
		if (size == 0)
		{
			throw std::invalid_argument(DataStructureException::ZERO_UNACCEPTABLE);
		}
		else
		{
			// 为顺序表分配空间，并且初始化其成员。
			this->m_p = new T[size];
			this->m_length = 0;
			this->m_size = size;

		}
	}

	// 由数组创建顺序表。若传递的指针为 nullptr 或指定容量为 0 ，抛出 std::invalid_arument 异常。
	template<typename T>
	inline SeqList<T>::SeqList(T* target, size_t size)
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
			this->m_p = new T[size];

			// 将数组中的元素深拷贝到顺序表
			for (size_t i = 0; i < size; i++)
			{
				this->m_p[i] = target[i];
			}
		}

	}

	// 删除顺序表，并释放所占用的内存空间。
	template <typename T>
	SeqList<T>::~SeqList()
	{
		delete[] this->m_p;		// 释放空间。
		this->m_p = nullptr;	// 将指针置空。
	}

	// 判断顺序表是否为空表。若为空表，返回 true；否则返回 false。
	template <typename T>
	inline bool SeqList<T>::empty()
	{
		return this->m_length == 0;
	}

	// 获取顺序表的长度（即表内的元素个数）。
	template <typename T>
	inline size_t SeqList<T>::length()
	{
		return this->m_length;
	}

	// 获取顺序表的容量（即顺序表的最大长度）。
	template<typename T>
	inline size_t SeqList<T>::size()
	{
		return this->m_size;
	}

	// 获取顺序表特定下标的元素。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	inline const T& SeqList<T>::get(size_t index)
	{
		if (index >= this->m_length)
		{
			// 下标超出范围时，抛出 std::out_of_range 异常。
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			return this->m_p[index];
		}
	}

	// 设置特定下标的元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template<typename T>
	bool SeqList<T>::set(size_t index, const T& target)
	{
		if (index >= this->m_length)
		{
			// 下标超出范围时，抛出 std::out_of_range 异常。
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			this->m_p[index] = target;
			return true;
		}
	}

	// 查找第一个特定元素所在的下标。若存在，返回对应下标；若不存在，返回 SeqList<T>.length() 。
	template<typename T>
	size_t SeqList<T>::find(const T& target)
	{
		for (size_t i = 0; i < this->m_length; i++)
		{
			if (this->m_p[i] == target)
			{
				return i;
			}
		}
		return this->m_length;
	}

	// 从相应下标处插入元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template<typename T>
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
			for (size_t i = this->m_length - 1; i >= index && i != static_cast<size_t>(-1); i--)
			{
				this->m_p[i + 1] = this->m_p[i];
			}
			// 插入指定的元素。
			this->m_p[index] = target;
			this->m_length++;
			return true;
		}
	}

	// 移除特定下标处的元素。成功返回 true ，失败返回 false 。若下标超出范围，抛出 std::out_of_range 异常。
	template<typename T>
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
				this->m_p[i] = this->m_p[i + 1];
			}
			this->m_length--;
			return true;
		}
	}

	// 重置顺序表，将释放顺序表的内存。当你在使用此顺序表类时捕获任何异常，请调用此方法以避免内存泄漏。
	template<typename T>
	inline void SeqList<T>::reset()
	{
		delete[] this->m_p;
		this->m_p = nullptr;
		this->m_length = 0;
		this->m_size = 0;
	}
}