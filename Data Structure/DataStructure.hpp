#pragma once
#include <stdexcept>

#define DEFAULT_MESSAGE_PARAM_NULLPTR_PASSED "nullptr passed as parameter(s)"     ///< 参数传递空指针时的默认错误消息。
#define DEFAULT_MESSAGE_PARAM_UNACCEPTABLE_VALUE "value passed is unacceptable"   ///< 参数传递无效值时的默认错误消息。
#define DEFAULT_MESSAGE_INDEX_OUT_OF_RANGE "index out of range"                   ///< 索引越界时的默认错误消息。
#define DEFAULT_MESSAGE_ITERATOR_OUT_OF_BOUNDS "iterator access out of bounds"    ///< 迭代器访问越界时的默认错误消息。
#define DEFAULT_MESSAGE_ACCESS_EMPTY_CONTAINER "container is empty"               ///< 尝试操作空容器时的默认错误消息。

namespace DataStructure
{
	/**
	 * \brief 数据结构迭代器的基类。
	 * \tparam T 数据类型。
	 */
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

	/**
	 * \brief 数据结构类的基类。
	 * \tparam T 数据类型。
	 */
	template <typename T>
	class DataStructure
	{
	public:
		virtual ~DataStructure() {}
		virtual bool empty() const = 0;
		virtual size_t length() const = 0;
		virtual size_t size() const = 0;
		virtual const T& get(size_t index) const = 0;
		virtual bool set(size_t index, const T& target) = 0;
		virtual bool add(const T& target) = 0;


	protected:
		T* m_data = nullptr;
		size_t m_length_ = 0;
		size_t m_size_ = 0;
	};

};

namespace DataStructureException
{
	/**
	 * \brief 参数传入 nullptr 时产生的异常。
	 * \note 派生自 std::invalid_argument。
	 */
	class param_nullptr_passed : public std::invalid_argument
	{
	public:
		explicit param_nullptr_passed(const std::string& arg) : std::invalid_argument(arg) {}
		explicit param_nullptr_passed(const char* arg = DEFAULT_MESSAGE_PARAM_NULLPTR_PASSED) : std::invalid_argument(arg) {}
	};
	
	/**
	 * \brief 参数传入无效值时产生的异常。
	 * \note 派生自 std::invalid_argument。
	 */
	class param_unacceptable_value : public std::invalid_argument
	{
	public:
		explicit param_unacceptable_value(const std::string& arg) : std::invalid_argument(arg) {}
		explicit param_unacceptable_value(const char* arg = DEFAULT_MESSAGE_PARAM_UNACCEPTABLE_VALUE) : std::invalid_argument(arg) {}
	};
	
	/**
	 * \brief 索引越界时产生的异常。
	 * \note 派生自 std::out_of_range。
	 */
	class index_out_of_range : public std::out_of_range
	{
	public:
		explicit index_out_of_range(const std::string& arg) : std::out_of_range(arg) {}
		explicit index_out_of_range(const char* arg = DEFAULT_MESSAGE_INDEX_OUT_OF_RANGE) : std::out_of_range(arg) {}
	};

	/**
	 * \brief 迭代器访问越界时产生的异常。
	 * \note 派生自 std::out_of_range。 
	 */
	class iterator_out_of_bounds : public std::out_of_range
	{
	public:
		explicit iterator_out_of_bounds(const std::string& arg) : std::out_of_range(arg) {}
		explicit iterator_out_of_bounds(const char* arg = DEFAULT_MESSAGE_ITERATOR_OUT_OF_BOUNDS) : std::out_of_range(arg) {}
	};

	/**
	 * \brief 尝试操作空容器时产生的异常。
	 * \note 派生自 std::out_of_range。 
	 */
	class access_empty_container : public std::out_of_range
	{
	public:
		explicit access_empty_container(const std::string& arg) : std::out_of_range(arg) {}
		explicit access_empty_container(const char* arg = DEFAULT_MESSAGE_ACCESS_EMPTY_CONTAINER) : std::out_of_range(arg) {}
	};

}