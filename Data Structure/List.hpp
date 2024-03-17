#pragma once
#include "DataStructure.hpp"
#include <algorithm>

namespace DataStructure
{
	/**
	 * \brief 链表的节点类。包含下一个节点的地址、上一个节点的地址和保存的元素。
	 * \tparam T 元素的类型。
	 */
	template <typename T>
	class ListNode
	{
	public:
		ListNode(ListNode<T>* prev, ListNode<T>* next, const T& data);
		
		ListNode* m_prev = nullptr;
		ListNode* m_next = nullptr;
		T m_data;
	};

	/**
	 * \brief 链表的迭代器类，派生自数据结构迭代器类。
	 * \tparam T 迭代器所指向的链表数据类型。
	 */
	template <typename T>
	class ListIterator final : public DataStructureIterator<T>
	{
	public:
		ListIterator() = default;
		explicit  ListIterator(ListNode<T>* ptr);
		T& operator*() override;
		const T& operator*() const override;
		
		ListIterator& operator++() override;
		ListIterator& operator++(int) override;
		ListIterator& operator--();
		ListIterator& operator--(int);
		
		bool operator!=(const DataStructureIterator<T>& target) const override;
		bool operator==(const DataStructureIterator<T>& target) const override;

		ListIterator next();
		ListIterator prev();
		
		ListNode<T>* m_ptr = nullptr;    ///< 当前迭代器指向的节点的地址。
	};

	/**
	 * \brief 链表类，派生自数据结构类。
	 * \tparam T 链表所存储数据的类型。
	 */
	template <typename T>
	class List final : public DataStructure<T>
	{
	public:
		List();
		List(const List& target);
		~List() override;
		List& operator=(List target);

		ListIterator<T> begin();
		ListIterator<T> begin() const;
		ListIterator<T> end();
		ListIterator<T> end() const;
		ListIterator<T> rev_begin();
		ListIterator<T> rev_begin() const;
		ListIterator<T> rev_end();
		ListIterator<T> rev_end() const;

		bool empty() const override;
		size_t length() const override;
		size_t size() const override;
		ListIterator<T> find(const T& target);
		const T& get(size_t index) const override;
		bool set(size_t index, const T& target) override;
		bool add(const T& target) override;

		bool he_add(const T& target);
		bool insert(size_t index, const T& target);
		bool remove(size_t index);
		void reset();
		
		ListNode<T>* m_head = nullptr;
		ListNode<T>* m_tail = nullptr;
	};



	/**
	 * \brief 
	 * \param prev 指向前一个节点的指针。
	 * \param next 指向后一个节点的指针。
	 * \param data 所保存的元素。
	 */
	template <typename T>
	ListNode<T>::ListNode(ListNode<T>* prev, ListNode<T>* next, const T& data) : m_prev(prev), m_next(next), m_data(data) {}

	/**
	 * \brief 创建指向特定节点的迭代器。
	 * \param ptr 指向对应节点的指针。
	 */
	template <typename T>
	ListIterator<T>::ListIterator(ListNode<T>* ptr): m_ptr(ptr) {}

	/**
	 * \brief 返回迭代器所指向节点元素的引用。
	 * \return 迭代器所指向的节点元素的引用。
	 */
	template <typename T>
	T& ListIterator<T>::operator*()
	{
		return m_ptr->m_data;
	}

	/**
	 * \brief 返回迭代器所指向节点元素的 const 引用。
	 * \return 迭代器所指向的节点元素的 const 引用。
	 */
	template <typename T>
	const T& ListIterator<T>::operator*() const
	{
		return m_ptr->m_data;
	}

	/**
	 * \brief 使此迭代器指向下一个元素后返回此迭代器。
	 * \return 当前迭代器的引用。
	 */
	template <typename T>
	ListIterator<T>& ListIterator<T>::operator++()
	{
		m_ptr = m_ptr->m_next;    ///< 指向下一个节点保存在节点类的 m_next 中。
		return *this;
	}

	/**
	 * \brief 返回此迭代器的副本，然后使迭代器指向下一个元素。
	 * \return 当前迭代器的副本的引用。
	 */
	template <typename T>
	ListIterator<T>& ListIterator<T>::operator++(int)
	{
		ListIterator<T> it = *this;   ///< 创建此迭代器的副本，返回此副本即可。
		++*this;
		return it;
	}

	/**
	 * \brief 使此迭代器指向上一个元素后返回此迭代器。
	 * \return 当前迭代器的引用。
	 */
	template <typename T>
	ListIterator<T>& ListIterator<T>::operator--()
	{
		m_ptr = m_ptr->m_prev;    ///< 指向下一个节点保存在节点类的 m_prev 中。
		return *this;
	}

	/**
	 * \brief 返回此迭代器的副本，然后使迭代器指向上一个元素。
	 * \return 当前迭代器的副本的引用。
	 */
	template <typename T>
	ListIterator<T>& ListIterator<T>::operator--(int)
	{
		ListIterator<T> it = *this;   ///< 创建此迭代器的副本，返回此副本即可。
		--*this;
		return it;
	}

	/**
	 * \brief 比较当前迭代器与目标迭代器是否指向不同节点。
	 * \param target 目标迭代器。
	 * \return 如果当前迭代器与目标迭代器指向不同元素则返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool ListIterator<T>::operator!=(const DataStructureIterator<T>& target) const
	{
		const ListIterator& temp = dynamic_cast<const ListIterator&>(target);
		return m_ptr != temp.m_ptr;
	}

	/**
	 * \brief 比较当前迭代器与目标迭代器是否指向同一节点。
	 * \param target 目标迭代器。
	 * \return 如果当前迭代器与目标迭代器指向同一节点则返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool ListIterator<T>::operator==(const DataStructureIterator<T>& target) const
	{
		const ListIterator& temp = dynamic_cast<const ListIterator&>(target);
		return m_ptr == temp.m_ptr;
	}

	/**
	 * \brief 返回下一个元素所对应的迭代器。
	 * \return 下一个元素所对应的迭代器。
	 */
	template <typename T>
	ListIterator<T> ListIterator<T>::next()
	{
		return ListIterator(m_ptr->m_next);
	}

	/**
	* \brief 返回上一个元素所对应的迭代器。
	* \return 上一个元素所对应的迭代器。
	*/
	template <typename T>
	ListIterator<T> ListIterator<T>::prev()
	{
		return ListIterator(m_ptr->m_prev);
	}

	/**
	 * \brief 创建空链表。
	 */
	template <typename T>
	List<T>::List()
	{
		m_head = nullptr;
		m_tail = nullptr;
	}

	/**
	 * \brief 由已有链表复制构造新的链表。
	 * \param target 待复制的链表。
	 */
	template <typename T>
	List<T>::List(const List& target)
	{
		m_head = new ListNode<T>(nullptr, nullptr, target.begin());
		m_tail = m_head;
		for(ListIterator<T> victim = ++target.begin(), it = begin(); victim != target.end(); ++victim, ++it)
		{
			it.m_ptr->m_next = new ListNode<T>(it.m_ptr, nullptr, *victim);
			m_tail = it.m_ptr->m_next;
		}
	}

	/**
	 * \brief 删除链表并释放其占用的内存。
	 */
	template <typename T>
	List<T>::~List()
	{
		ListIterator<T> prev = rev_begin();
		for(ListIterator<T> it = prev; it != rev_end(); it = prev)
		{
			--prev;
			delete it.m_ptr;
			it.m_ptr = nullptr;
		}
	}

	/**
	 * \brief 将目标链表的所有属性和元素复制到当前数据表。
	 * \param target 目标链表。
	 * \return 此链表的引用。
	 */
	template <typename T>
	List<T>& List<T>::operator=(List target)
	{
		std::swap(*this, target);
		return *this;
	}

	/**
	 * \brief 获取链表的 begin 迭代器。
	 * \return 指向链表第一个元素的迭代器。
	 */
	template <typename T>
	ListIterator<T> List<T>::begin()
	{
		return ListIterator<T>(this->m_head);
	}

	template <typename T>
	ListIterator<T> List<T>::begin() const
	{
		return ListIterator<T>(this->m_head);
	}

	/**
	 * \brief 获取链表的 end 迭代器。
	 * \return 指向链表最后一个元素后的迭代器。
	 */
	template <typename T>
	ListIterator<T> List<T>::end()
	{
		return ListIterator<T>(nullptr);
	}

	template <typename T>
	ListIterator<T> List<T>::end() const
	{
		return ListIterator<T>(nullptr);
	}

	/**
	 * \brief 获取链表的反向 begin 迭代器。
	 * \return 指向链表最后一个元素的迭代器。
	 */
	template <typename T>
	ListIterator<T> List<T>::rev_begin()
	{
		return ListIterator<T>(this->m_tail);
	}

	template <typename T>
	ListIterator<T> List<T>::rev_begin() const
	{
		return ListIterator<T>(&this->m_tail);
	}

	/**
	 * \brief 获取链表的反向 end 迭代器。
	 * \return 指向链表第一个元素前的迭代器。
	 */
	template <typename T>
	ListIterator<T> List<T>::rev_end()
	{
		return ListIterator<T>(nullptr);
	}

	template <typename T>
	ListIterator<T> List<T>::rev_end() const
	{
		return ListIterator<T>(nullptr);
	}

	/**
	 * \brief 判断此链表是否为空表。
	 * \return 如果此链表为空表，返回 true ；否则返回 false 。
	 */
	template <typename T>
	bool List<T>::empty() const
	{
		return this->m_head == nullptr;
	}

	/**
	 * \brief 获取链表的长度。
	 * \return 链表内的元素个数。
	 */
	template <typename T>
	size_t List<T>::length() const
	{
		size_t length = 0;
		for(const T value : *this)
		{
			++length;
		}
		return length;
	}

	/**
	 * \brief 获取链表的容量。
	 * \return 链表内的元素个数。
	 */
	template <typename T>
	size_t List<T>::size() const
	{
		size_t size = 0;
		for (const T value : *this)
		{
			++size;
		}
		return size;
	}

	/**
	 * \brief 在链表中查找目标元素。
	 * \param target 目标元素。
	 * \return 如果存在目标元素，返回指向第一个目标元素的迭代器；若不存在，返回 end 迭代器。
	 */
	template <typename T>
	ListIterator<T> List<T>::find(const T& target)
	{
		for (auto it = begin(); it != end(); ++it)    ///< 利用迭代器遍历链表。
		{
			if (*it == target)
			{
				return it;
			}
		}
		return end();
	}

	/**
	 * \brief 获取链表目标索引节点的元素。
	 * \param index 目标索引。
	 * \return 索引节点的元素。
	 * \exception index_out_of_range 若索引超出范围，抛出此异常。
	 */
	template <typename T>
	const T& List<T>::get(size_t index) const
	{
		for (ListIterator<T> it = begin(); it != end(); ++it, --index)
		{
			if (index == 0)
			{
				return *it;
			}
		}
		throw DataStructureException::index_out_of_range();
	}

	/**
	 * \brief 设置链表目标索引节点的元素。
	 * \param index 目标索引。
	 * \param target 待设定的元素。
	 * \return 若设定成功，返回 true；否则返回 false。
	 * \exception index_out_of_range 若索引超出范围，抛出此异常。
	 */
	template <typename T>
	bool List<T>::set(size_t index, const T& target)
	{
		for (ListIterator<T> it = begin(); it != end(); ++it, --index)
		{
			if (index == 0)
			{
				*it = target;
				return true;
			}
		}
		throw DataStructureException::index_out_of_range();
	}

	/**
	 * \brief 从链表尾部插入目标元素。
	 * \param target 目标元素。
	 * \return 若元素插入成功，返回 true；否则返回 false。
	 */
	template <typename T>
	bool List<T>::add(const T& target)
	{
		if (empty())
		{
			try
			{
				m_head = new ListNode<T>(nullptr, nullptr, target);
				m_tail = m_head;
				return true;
			}
			catch (std::bad_alloc&)
			{
				return false;
			}
		}
		else
		{
			try
			{
				ListIterator<T> it = begin();
				while (it.next() != end()) ++it;
				it.m_ptr->m_next = new ListNode<T>(it.m_ptr, nullptr, target);
				m_tail = it.m_ptr->m_next;
				return true;
			}
			catch (std::bad_alloc&)
			{
				return false;
			}
		}
	}

	/**
	 * \brief 从链表头部插入目标元素。
	 * \param target 目标元素。
	 * \return 若元素插入成功，返回 true；否则返回 false。
	 */
	template <typename T>
	bool List<T>::he_add(const T& target)
	{
		try
		{
			ListNode<T>* tmp = new ListNode<T>(m_head, target);
			this->m_head = tmp;
			return true;
		}
		catch (std::bad_alloc&)
		{
			return false;
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
	bool List<T>::insert(size_t index, const T& target)
	{
		if (index == 0)
		{
			return he_add(target);
		}
		else
		{
			for (ListIterator<T> it = begin(); it != end(); ++it, --index)
			{
				if (index == 1)
				{
					try
					{
						it.m_ptr->m_next = new ListNode<T>(it.m_ptr->m_next, target);
						return true;
					}
					catch (std::bad_alloc&)
					{
						return false;
					}
				}
			}
		}
		throw DataStructureException::index_out_of_range();
	}

	/**
	 * \brief 移除目标索引处的元素。
	 * \param index 目标索引。
	 * \return 若移除成功，返回 true；否则返回 false。
	 * \exception access_empty_container 当容器为空时，抛出此异常。
	 * \exception index_out_of_range 当索引超出范围时，抛出此异常。
	 */
	template <typename T>
	bool List<T>::remove(size_t index)
	{
		if (m_head == nullptr)
		{
			throw DataStructureException::access_empty_container();
		}
		else if (index == 0)
		{
			ListIterator<T> it = begin();
			m_head = it.m_ptr->m_next;
			delete it.m_ptr;
			return true;
		}
		else
		{
			for (ListIterator<T> it = begin(); it != end(); ++it, --index)
			{
				if (index == 1)
				{
					auto victim = it.m_ptr->m_next;
					it.m_ptr->m_next = victim->m_next;
					delete victim;
					return true;
				}
			}
		}
		throw DataStructureException::index_out_of_range();
	}

	/**
	 * \brief 重置链表。将释放链表所占用的内存。
	 * \note 如果您在使链表方法时捕获到异常，请调用此方法避免内存泄漏。
	 */
	template <typename T>
	void List<T>::reset()
	{
		ListIterator<T> prev = rev_begin();
		for (ListIterator<T> it = prev; it != rev_end(); it = prev)
		{
			--prev;
			delete it.m_ptr;
			it.m_ptr = nullptr;
		}
	};
}
