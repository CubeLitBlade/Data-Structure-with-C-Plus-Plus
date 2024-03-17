#pragma once
#include  "DataStructure.hpp"
#include <algorithm>

namespace DataStructure
{
	/**
	 * \brief 顺序表迭代器类，派生自数据结构迭代器类。
	 * \tparam T 迭代器所指向的顺序表数据类型。
	 */
	template <typename T>
	class SeqListIterator final : public DataStructureIterator<T>
	{
	public:
		SeqListIterator(T* ptr);
		T& operator*() override;
		const T& operator*() const override;

		SeqListIterator& operator++() override;
		SeqListIterator& operator++(int) override;
		bool operator!=(const DataStructureIterator<T>& target) const override;
		bool operator==(const DataStructureIterator<T>& target) const override;

	private:
		T* m_ptr = nullptr;    ///< 迭代器所指向的元素。
	};

	/**
	 * \brief 顺序表类，派生自数据结构类。
	 * \tparam T 顺序表所存储数据的类型。
	 */
	template <typename T>
	class SeqList final : public DataStructure<T>
	{
	public:
		explicit SeqList(size_t size);
		SeqList(T* target, size_t size);
		SeqList(const SeqList& target);
		~SeqList() override;
		SeqList& operator=(SeqList target);

		SeqListIterator<T> begin();
		SeqListIterator<T> end();

		bool empty() const override;
		size_t length() const override;
		size_t size() const override;
		SeqListIterator<T> find(const T& target) const;
		const T& get(size_t index) const override;
		bool set(size_t index, const T& target) override;
		bool add(const T& target) override;

		bool insert(size_t index, const T& target);
		bool remove(size_t index);
		size_t iterator_to_index(SeqListIterator<T> iterator) const;
		SeqListIterator<T> index_to_iterator(size_t index) const;
		void reset();
	};

	/************************************************************************/

	/**
	 * \brief 创建指向特定元素的迭代器。
	 * \param ptr 指向对应元素的指针。
	 */
	template <typename T>
	SeqListIterator<T>::SeqListIterator(T* ptr) : m_ptr(ptr) {}

	/**
	 * \brief 返回迭代器所指向的元素的引用。
	 * \return 迭代器所指向的元素的引用。
	 */
	template <typename T>
	T& SeqListIterator<T>::operator*()
	{
		return *m_ptr;
	}

	/**
	 * \brief 返回迭代器所指向的元素的 const 引用。
	 * \return 迭代器所指向的元素的 const 引用。
	 */
	template <typename T>
	const T& SeqListIterator<T>::operator*() const
	{
		return *m_ptr;
	}

	/**
	 * \brief 使此迭代器指向下一个元素后返回此迭代器。
	 * \return 当前迭代器的引用。
	 */
	template <typename T>
	SeqListIterator<T>& SeqListIterator<T>::operator++()
	{
		++m_ptr;    ///< 顺序表的内存是连续的，将指针自增后即可指向下一元素。
		return *this;
	}

	/**
	 * \brief 返回此迭代器的副本，然后使迭代器指向下一个元素。
	 * \return 当前迭代器的副本的引用。
	 */
	template <typename T>
	SeqListIterator<T>& SeqListIterator<T>::operator++(int)
	{
		SeqListIterator<T> it = *this;   ///< 创建此迭代器的副本，返回此副本即可。
		++*this;
		return it;
	}

	/**
	 * \brief 比较当前迭代器与目标迭代器是否指向不同元素。
	 * \param target 目标迭代器。
	 * \return 如果当前迭代器与目标迭代器指向不同元素则返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool SeqListIterator<T>::operator!=(const DataStructureIterator<T>& target) const
	{
		const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target);    ///< 使用类型转换将 target 转换为 DataStructureIterator 类型。
		return m_ptr != temp.m_ptr;
	}

	/**
	 * \brief 比较当前迭代器与目标迭代器是否指向同一元素。
	 * \param target 目标迭代器。
	 * \return 如果当前迭代器与目标迭代器指向同一元素则返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool SeqListIterator<T>::operator==(const DataStructureIterator<T>& target) const
	{
		const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target);    ///< 同上，不多赘述。
		return m_ptr == temp.m_ptr;
	}

	/**
	 * \brief 根据给定的容量创建空顺序表。
	 * \param size 顺序表的容量。
	 * \exception param_unacceptable_value 指定的顺序表的容量为 0 时，抛出此异常。
	 */
	template <typename T>
	SeqList<T>::SeqList(size_t size)
	{
		if (size == 0)
		{
			this->reset();    ///< 在抛出异常前主动重置顺序表，以免造成内存泄漏。
			throw DataStructureException::param_unacceptable_value();
		}
		else
		{
			this->m_data = new T[size];
			this->m_length_ = 0;
			this->m_size_ = size;

		}
	}

	/**
	 * \brief 由已有的数组创建顺序表。
	 * \param target 包含要存入顺序表的元素的数组。
	 * \param size 顺序表的容量。
	 * \exception param_nullptr_passed 传入的指针为 nullptr 时，抛出此异常。
	 * \exception param_unacceptable_value 指定的顺序表的容量为 0 时，抛出此异常。
	 */
	template <typename T>
	SeqList<T>::SeqList(T* target, size_t size)
	{
		if (target == nullptr)
		{
			this->reset();
			throw DataStructureException::param_nullptr_passed();
		}
		else if (size == 0)
		{
			this->reset();
			throw DataStructureException::param_unacceptable_value();
		}
		else
		{
			// 为顺序表分配空间，并且初始化其成员。
			this->m_size_ = size;
			this->m_length_ = size;
			this->m_data = new T[size];

			// 通过循环将目标数组中的元素复制到顺序表内。
			for (size_t i = 0; i < size; i++)
			{
				this->m_data[i] = target[i];
			}
		}

	}

	/**
	 * \brief 由已有顺序表复制构造新顺序表。
	 * \param target 待复制的顺序表。
	 */
	template <typename T>
	SeqList<T>::SeqList(const SeqList& target)
	{
		// 为顺序表分配空间，并且初始化其成员。
		this->m_size_ = target.size();
		this->m_length_ = target.length();
		this->m_data = new T[this->m_size_];

		// 使用迭代器遍历两个顺序表并依次将其赋值。
		for (SeqListIterator<T> it1 = begin(), it2 = target.begin(); it1 != end() && it2 != target.end(); ++it1, ++it2)
		{
			*it1.m_ptr = *it2.m_ptr;
		}
	}

	/**
	 * \brief 删除顺序表并释放其占用的内存。
	 */
	template <typename T>
	SeqList<T>::~SeqList()
	{
		if (this->m_data != nullptr)
		{
			delete[] this->m_data;    ///< 释放所占用的内存。
			this->m_data = nullptr;    ///< 将指针置空，以免造成访问异常。
		}
	}

	/**
	 * \brief 将目标顺序表的所有属性和元素复制到当前数据表。
	 * \param target 目标顺序表。
	 * \return 此顺序表的引用。
	 */
	template <typename T>
	SeqList<T>& SeqList<T>::operator=(SeqList target)
	{
		/** COPY AND SWAP：利用 std::swap 方法，在拥有复制构造函数的前提下，交换两个指针所对应的对象。*/
		/** 由此，target 成为原有的 *this，在方法调用结束后自然释放。可以自然处理 *this == target 的情况。*/
		std::swap(*this, target);
		return *this;
	}

	/**
	 * \brief 获取顺序表的 begin 迭代器。
	 * \return 指向顺序表第一个元素的迭代器。
	 */
	template <typename T>
	SeqListIterator<T> SeqList<T>::begin()
	{
		return SeqListIterator<T>(&this->m_data[0]);
	}

	/**
	 * \brief 获取顺序表的 end 迭代器。
	 * \return 指向顺序表最后一个元素后的迭代器。
	 */
	template <typename T>
	SeqListIterator<T> SeqList<T>::end()
	{
		return SeqListIterator<T>(&this->m_data[this->m_size_]);
	}

	/**
	 * \brief 判断此顺序表是否为空表。
	 * \return 如果此顺序表为空表，返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool SeqList<T>::empty() const
	{
		return this->m_length_ == 0;
	}

	/**
	 * \brief 获取顺序表的长度。
	 * \return 返回顺序表内的元素个数。
	 */
	template <typename T>
	size_t SeqList<T>::length() const
	{
		return this->m_length_;
	}

	/**
	 * \brief 获取顺序表的容量。
	 * \return 返回顺序表的最大长度。
	 */
	template <typename T>
	size_t SeqList<T>::size() const
	{
		return this->m_size_;
	}

	/**
	 * \brief 在顺序表中查找目标元素。
	 * \param target 目标元素。
	 * \return 如果存在目标元素，返回指向第一个目标元素的迭代器；若不存在，返回 end 迭代器。
	 */
	template <typename T>
	SeqListIterator<T> SeqList<T>::find(const T& target) const
	{
		for (SeqListIterator<T> it = begin(); it != end(); ++it)    ///< end 迭代器指向末尾元素的后一位，当 it 与 end() 相等时，即为遍历结束。
		{
			if (*it == target)
				return it;
		}
		return end();
	}

	/**
	 * \brief 获取顺序表目标索引的元素。
	 * \param index 目标索引。
	 * \return 索引对应的元素。
	 * \exception index_out_of_range 若索引超出范围，抛出此异常。
	 */
	template <typename T>
	const T& SeqList<T>::get(size_t index) const
	{
		if (index >= this->m_length_)
		{
			throw DataStructureException::index_out_of_range();
		}
		else
		{
			return this->m_data[index];
		}
	}

	/**
	 * \brief 设置顺序表目标索引的元素。
	 * \param index 目标索引。
	 * \param target 待设定的元素。
	 * \return 若设定成功，返回 true；否则返回 false。
	 * \exception index_out_of_range 若索引超出范围，抛出此异常。
	 */
	template <typename T>
	bool SeqList<T>::set(size_t index, const T& target)
	{
		if (index >= this->m_length_)
		{
			throw DataStructureException::index_out_of_range();
		}
		else
		{
			this->m_data[index] = target;
			return true;
		}
	}

	/**
	 * \brief 从顺序表尾部插入目标元素。
	 * \param target 目标元素。
	 * \return 若元素插入成功，返回 true；否则返回 false。
	 */
	template<typename T>
	bool SeqList<T>::add(const T& target)
	{
		if (this->m_length_ == this->m_size_)    ///< 当 m_length_ 与 m_size_ 相等时，表示顺序表已满，插入失败。
		{
			return false;
		}
		else
		{
			this->m_data[this->m_length_] = target;
			++this->m_length_;
			return true;
		}
	}

	/**
	 * \brief 从目标索引处插入目标元素。
	 * \param index 目标索引。
	 * \param target 目标元素。
	 * \return 若元素插入成功则返回 true；否则返回 false。
	 * \exception index_out_of_range 若索引超出范围，抛出此异常。
	 */
	template <typename T>
	bool SeqList<T>::insert(size_t index, const T& target)
	{
		if (this->m_length_ == this->m_size_)    ///< 同上，不再赘述。
		{
			return false;
		}
		else if (index > this->m_length_)
		{
			throw DataStructureException::index_out_of_range();
		}
		else
		{
			/** 从顺序表末尾依次将元素后移，达到索引处或 size_t 类型向下溢出时停止。*/
			for (size_t i = this->m_length_ - 1; i >= index && i != static_cast<size_t>(-1); --i)
			{
				this->m_data[i + 1] = this->m_data[i];
			}
			/** 插入指定的元素。*/
			this->m_data[index] = target;
			++this->m_length_;
			return true;
		}
	}
	
	/**
	 * \brief 移除目标索引处的元素。
	 * \param index 目标索引。
	 * \return 若移除成功，返回 true；否则返回 false。
	 * \exception access_empty_container 当容器为空时，抛出此异常。
	 * \exception index_out_of_range 当索引超出范围时，抛出此异常。
	 */
	template <typename T>
	bool SeqList<T>::remove(size_t index)
	{
		if (empty())
		{
			throw DataStructureException::access_empty_container();
		}
		else if (index >= this->m_length_)
		{
			throw DataStructureException::index_out_of_range();
		}
		else
		{
			for (size_t i = index; i < this->m_length_ - 1; i++)    ///< 只需要将索引后的所有元素前移覆盖掉索引元素即可。
			{
				this->m_data[i] = this->m_data[i + 1];
			}
			--this->m_length_;    ///< 使长度自减，这样就无法访问末尾未删除的值，末尾的值不用删除。
			return true;
		}
	}

	/**
	 * \brief 查询目标迭代器所指向元素的索引。
	 * \param iterator 目标迭代器。
	 * \return 目标迭代器所指向的元素的索引。
	 */
	template <typename T>
	size_t SeqList<T>::iterator_to_index(const SeqListIterator<T> iterator) const
	{
		return iterator.m_ptr - this->m_data;    ///< 视为数组的指针相减得到索引。
	}

	/**
	 * \brief 创建指向目标索引的迭代器。
	 * \param index 目标索引。
	 * \return 指向目标索引的迭代器。
	 */
	template <typename T>
	SeqListIterator<T> SeqList<T>::index_to_iterator(size_t index) const
	{
		return SeqListIterator<T>(this->m_data + index);    ///< 同理，基址与偏移值相加得到目标指针后构造迭代器。
	}

	/**
	 * \brief 重置顺序表。将释放顺序表所占用的内存。
	 * \note 如果您在使用顺序表方法时捕获到异常，请调用此方法避免内存泄漏。
	 */
	template <typename T>
	void SeqList<T>::reset()
	{
		if (this->m_data != nullptr)
		{
			delete[] this->m_data;    ///< 释放所占用的内存。
			this->m_data = nullptr;    ///< 将指针置空，以免造成访问异常。
		}
		this->m_length_ = 0;
		this->m_size_ = 0;
	}
}
