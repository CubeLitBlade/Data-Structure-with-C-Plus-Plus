#pragma once
#include "DataStructureExpection.h"

namespace DataStructure
{
	// 顺序表类
	template <typename T>
	class SeqList
	{
	public:
		SeqList(size_t length);
		SeqList(T* target, size_t length);
		~SeqList();

		bool empty();
		size_t length();
		size_t size();
		T get(size_t index);
		size_t find(T target);
		bool insert(size_t index, T target);
		bool remove(size_t index);

	private:
		T* m_p = nullptr;
		size_t m_length = 0;
		size_t m_max = 0;
	};

	// 根据给定的容量创建空顺序表。若指定容量为 0 ，抛出 std::invalid_argument 异常。
	template <typename T>
	SeqList<T>::SeqList(size_t max)
	{
		if (length == 0)
		{
			throw std::invalid_argument(DataStructureException::ZERO_UNACCEPTABLE);
		}
		else
		{
			this->m_p = new T[max];
			this->m_length = 0;
			this->m_max = max;

		}
	}

	// 由数组创建顺序表。若传递的指针为 nullptr 或指定容量为 0 ，抛出 std::invalid_arument 异常。
	template<typename T>
	SeqList<T>::SeqList(T* target, size_t length)
	{
		if (target == nullptr)
		{
			throw std::invalid_argument(DataStructureException::NULLPTR_PARAMETER);
		}
		else if (length == 0)
		{
			throw std::invalid_argument(DataStructureException::ZERO_UNACCEPTABLE);
		}
		else
		{
			this->m_max = length;
			this->m_length = length;
			this->m_p = new T[length];

			// 将数组中的元素深拷贝到顺序表
			for (size_t i = 0; i < length; i++)
			{
				m_p[i] = target[i];
			}
		}

	}

	// 删除顺序表，并释放所占用的内存空间。
	template <typename T>
	SeqList<T>::~SeqList()
	{
		delete[] m_p;
		this->m_p = nullptr;	// 将指针置空
	}

	// 判断顺序表是否为空表。若为空表，返回 true；否则返回 false。
	template <typename T>
	bool SeqList<T>::empty()
	{
		if (m_length == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 获取顺序表的长度（即表内的元素个数）。
	template <typename T>
	size_t SeqList<T>::length()
	{
		return this->m_length;
	}

	// 获取顺序表的容量（即顺序表的最大长度）。
	template<typename T>
	size_t SeqList<T>::size()
	{
		return m_max;
	}

	// 获取顺序表特定下标的元素。若下标超出范围，抛出 std::out_of_range 异常。
	template <typename T>
	T SeqList<T>::get(size_t index)
	{
		if (index >= m_length)
		{
			// 下标超出范围时，抛出 std::out_of_range 异常。
			throw std::out_of_range(DataStructureException::BAD_INDEX);
		}
		else
		{
			return m_p[index];
		}
	}

	// 查找第一个特定元素所在的下标。若存在，返回对应下标；若不存在，返回 -1 。
	template<typename T>
	size_t SeqList<T>::find(T target)
	{
		for (size_t i = 0; i < this->m_length; i++)
		{
			if (m_p[i] == target)
			{
				return i;
			}
		}
		return -1;
	}

	// 从相应下标处插入元素。成功返回 true ，失败返回 false 。
	template<typename T>
	bool SeqList<T>::insert(size_t index, T target)
	{
		if (m_length == m_max)
		{
			return false;
		}
		else if (index > m_length)
		{
			return false;
		}
		else
		{
			// 从顺序表末尾依次将元素后移，达到下标处或 size_t 类型向下溢出时停止。
			for (size_t i = m_length - 1; i >= index && i != static_cast<size_t>(-1); i--)
			{
				m_p[i + 1] = m_p[i];
			}
			m_p[index] = target;
			m_length++;
			return true;
		}
	}

	// 移除特定下标处的元素。成功返回 true ，失败返回 false 。
	template<typename T>
	bool SeqList<T>::remove(size_t index)
	{
		if (index >= m_length)
		{
			return false;
		}
		else
		{
			for (size_t i = index; i < m_length - 1; i++)
			{
				m_p[i] = m_p[i + 1];
			}
			m_length--;
			return true;
		}
	}
}