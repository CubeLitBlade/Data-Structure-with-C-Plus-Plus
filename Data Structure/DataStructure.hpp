﻿#pragma once
#include <stdexcept>

#define DEFAULT_MESSAGE_PARAM_NULLPTR_PASSED "nullptr passed as parameter(s)"					///< 参数传递空指针时的默认错误消息。
#define DEFAULT_MESSAGE_PARAM_UNACCEPTABLE_VALUE "value passed is unacceptable"					///< 参数传递无效值时的默认错误消息。
#define DEFAULT_MESSAGE_INDEX_OUT_OF_RANGE "index out of range"									///< 索引越界时的默认错误消息。
#define DEFAULT_MESSAGE_ITERATOR_OUT_OF_BOUNDS "iterator access out of bounds"					///< 迭代器访问越界时的默认错误消息。
#define DEFAULT_MESSAGE_ITERATOR_ACCESS_END "dereference of the end iterator is not allowed"	///< 尝试解引用 end 迭代器时的默认错误消息。
#define DEFAULT_MESSAGE_ACCESS_EMPTY_CONTAINER "container is empty"								///< 尝试操作空容器时的默认错误消息。

namespace DataStructure
{
	/**
	 * @brief 数据结构迭代器的基类。
	 * @tparam T 数据类型。
	 */
	template <typename T>
	class DataStructureIterator
	{
	public:
		virtual ~DataStructureIterator() {};
		virtual T& operator*() = 0;
		virtual const T& operator*() const = 0;
		virtual DataStructureIterator& operator++() = 0;
		// virtual DataStructureIterator operator++(int) = 0;
		virtual bool operator!=(const DataStructureIterator<T>& target) const = 0;
		virtual bool operator==(const DataStructureIterator<T>& target) const = 0;
	};

	/**
	 * @brief 数据结构类的基类。
	 * @tparam T 数据类型。
	 */
	template <typename T>
	class DataStructure
	{
	public:
		virtual ~DataStructure() {}
		virtual bool Empty() const = 0;
		virtual size_t Length() const = 0;
		virtual size_t size() const = 0;
		virtual const T& Get(size_t index) const = 0;
		virtual bool Set(size_t index, const T& target) = 0;
		virtual bool Add(const T& target) = 0;
	};

};

namespace DataStructureException
{
	/**
	 * @brief 参数传入 nullptr 时产生的异常。
	 * \note 派生自 std::invalid_argument。
	 */
	class ParamNullptrPassed final : public std::invalid_argument
	{
	public:
		explicit ParamNullptrPassed(const std::string& arg) : std::invalid_argument(arg) {}
		explicit ParamNullptrPassed(const char* arg = DEFAULT_MESSAGE_PARAM_NULLPTR_PASSED) : std::invalid_argument(arg) {}
	};
	
	/**
	 * @brief 参数传入无效值时产生的异常。
	 * \note 派生自 std::invalid_argument。
	 */
	class ParamUnacceptableValue final : public std::invalid_argument
	{
	public:
		explicit ParamUnacceptableValue(const std::string& arg) : std::invalid_argument(arg) {}
		explicit ParamUnacceptableValue(const char* arg = DEFAULT_MESSAGE_PARAM_UNACCEPTABLE_VALUE) : std::invalid_argument(arg) {}
	};
	
	/**
	 * @brief 索引越界时产生的异常。
	 * \note 派生自 std::out_of_range。
	 */
	class IndexOutOfRange final : public std::out_of_range
	{
	public:
		explicit IndexOutOfRange(const std::string& arg) : std::out_of_range(arg) {}
		explicit IndexOutOfRange(const char* arg = DEFAULT_MESSAGE_INDEX_OUT_OF_RANGE) : std::out_of_range(arg) {}
	};

	/**
	 * @brief 迭代器访问越界时产生的异常。
	 * \note 派生自 std::out_of_range。 
	 */
	class IteratorOutOfBounds final : public std::out_of_range
	{
	public:
		explicit IteratorOutOfBounds(const std::string& arg) : std::out_of_range(arg) {}
		explicit IteratorOutOfBounds(const char* arg = DEFAULT_MESSAGE_ITERATOR_OUT_OF_BOUNDS) : std::out_of_range(arg) {}
	};

	/**
	 * @brief 迭代器访问越界时产生的异常。
	 * \note 派生自 std::out_of_range。
	*/
	class IteratorAccessEnd final : public std::out_of_range
	{
	public:
		explicit IteratorAccessEnd(const std::string& arg) : std::out_of_range(arg) {}
		explicit IteratorAccessEnd(const char* arg = DEFAULT_MESSAGE_ITERATOR_ACCESS_END) : std::out_of_range(arg) {}
	};

	/**
	 * @brief 尝试操作空容器时产生的异常。
	 * \note 派生自 std::out_of_range。 
	 */
	class AccessEmptyContainer final : public std::out_of_range
	{
	public:
		explicit AccessEmptyContainer(const std::string& arg) : std::out_of_range(arg) {}
		explicit AccessEmptyContainer(const char* arg = DEFAULT_MESSAGE_ACCESS_EMPTY_CONTAINER) : std::out_of_range(arg) {}
	};

}