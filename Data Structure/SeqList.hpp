#pragma once
#include  "DataStructure.hpp"
#include <algorithm>
#include <compare>

namespace DataStructure
{
    /** 前向声明两个类模板。 */
    template <typename T> class SeqList;
    template <typename T> class SeqListIterator;

    /**
      * @brief 顺序表迭代器类，派生自数据结构迭代器类。
      * @tparam T 迭代器所指向的顺序表数据类型。
      */
    template <typename T>
    class SeqListIterator final : public DataStructureIterator<T>
    {
        /** 声明 SeqListIterator 的友元。 */
        template <typename U> friend SeqListIterator<U> operator+(const SeqListIterator<U>& iterator, int n);
        template <typename U> friend SeqListIterator<U> operator-(const SeqListIterator<U>& iterator, int n);
        template <typename U> friend int operator-(const SeqListIterator<U>& iteratorL, const SeqListIterator<U>& iteratorR);

    public:
        SeqListIterator(const SeqList<T>& target, size_t index);
        SeqListIterator(const SeqListIterator<T>& target);

        const T& operator*() const override;
        T& operator*() override;
        T& operator[](int index);
        SeqListIterator& operator=(SeqListIterator<T> target);
        SeqListIterator& operator++() override;
        SeqListIterator operator++(int);
        SeqListIterator& operator--();
        SeqListIterator operator--(int);
        SeqListIterator& operator+=(int offset);
        SeqListIterator& operator-=(int offset);
        std::strong_ordering operator<=>(const SeqListIterator& target) const;

        /** 这些方法将在不久后废除。 */
        bool operator!=(const DataStructureIterator<T>& target) const override;
        bool operator==(const DataStructureIterator<T>& target) const override;

    private:
        T* IteratorPtr = nullptr; ///< 迭代器所指向的元素。
        const T* IteratorLowerBound; ///< 迭代器下界，即 begin 迭代器所指的地址。
        const T* IteratorUpperBound; ///< 迭代器上界，即 end 迭代器所指的地址。
    };

    /**
     * @brief 顺序表类，派生自数据结构类。
     * @tparam T 顺序表所存储数据的类型。
     */
    template <typename T>
    class SeqList final : public DataStructure<T>
    {
        /** 声明 SeqList 的友元。 */
        friend class SeqListIterator<T>;

    public:
        explicit SeqList(size_t capacity);
        SeqList(size_t capacity, const T& defaultVal);
        SeqList(T* array, size_t capacity);
        SeqList(const SeqList& targetToCopy);
        ~SeqList() override;

        SeqListIterator<T> begin() const;
        SeqListIterator<T> end() const;

        SeqList& operator=(SeqList targetToCopy);
        bool Empty() const override;
        size_t Length() const override;
        size_t size() const override;
        SeqListIterator<T> Find(const T& targetVal) const;
        const T& Get(size_t index) const override;
        bool Set(size_t index, const T& val) override;
        bool Add(const T& target) override;
        bool Insert(size_t index, const T& target);
        bool Remove(size_t index);
        void Clear();

    private:
        T* DataPtr = nullptr; ///< 顺序表数据段地址。
        size_t Len = 0; ///< 顺序表所存放的元素个数。
        size_t Capacity = 0; ///< 顺序表的最大容量。
    };

    /**
     * @brief 构造指向目标顺序表对应索引的迭代器。
     * @param target 目标顺序表。
     * @param index 索引。
     * @exception IteratorOutOfBounds 如果传入的索引会使迭代器对于此顺序表越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T>::SeqListIterator(const SeqList<T>& target, size_t index)
        : IteratorPtr(target.DataPtr + index), IteratorLowerBound(target.DataPtr),
          IteratorUpperBound(target.DataPtr + target.Len)
    {
        if (IteratorPtr < IteratorLowerBound || IteratorPtr > IteratorUpperBound) ///< 判断越界，如果越界，则抛出异常。
            throw DataStructureException::IteratorOutOfBounds();
    }

    /**
     * @brief 复制构造顺序表。
     */
    template <typename T>
    SeqListIterator<T>::SeqListIterator(const SeqListIterator<T>& target)
    {
        IteratorPtr = target.IteratorPtr;
        IteratorLowerBound = target.IteratorLowerBound;
        IteratorUpperBound = target.IteratorUpperBound;
    }

    /**
    * @brief 返回迭代器所指向的元素的 const 引用。
    * @return 迭代器所指向的元素的 const 引用。
    * @exception IteratorAccessEnd 如果尝试对 end 迭代器解引用，抛出此异常。
    */
    template <typename T>
    const T& SeqListIterator<T>::operator*() const
    {
        if (IteratorPtr == IteratorUpperBound) ///< 如果迭代器为 end 迭代器则抛出异常。
            throw DataStructureException::IteratorAccessEnd();
        return *IteratorPtr;
    }

    /**
     * @brief 返回迭代器所指向的元素的引用。
     * @return 迭代器所指向的元素的引用。
     * @exception IteratorAccessEnd 如果尝试对 end 迭代器解引用，抛出此异常。
     */
    template <typename T>
    T& SeqListIterator<T>::operator*()
    {
        if (IteratorPtr == IteratorUpperBound) ///< 如果迭代器为 end 迭代器则抛出异常。
            throw DataStructureException::IteratorAccessEnd();
        return *IteratorPtr;
    }

    /**
     * @brief 返回迭代器后对应索引元素的引用。
     * @param index 迭代器的偏移索引。
     * @return 对应元素的引用。
     */
    template <typename T>
    T& SeqListIterator<T>::operator[](int index)
    {
        return *(IteratorPtr + index); ///< 在加法运算符和解引用运算符中已经会检测异常，故不检测。
    }

    /**
     * @brief 复制目标迭代器，，并返回引用。
     * @param target 目标迭代器。
     * @return 当前迭代器的引用。
     */
    template <typename T>
    SeqListIterator<T>& SeqListIterator<T>::operator=(SeqListIterator<T> target)
    {
        IteratorPtr = target.IteratorPtr;
        IteratorLowerBound = target.IteratorLowerBound;
        IteratorUpperBound = target.IteratorUpperBound;
        return *this;
    }

    /**
     * @brief 使此迭代器指向下一个元素后返回此迭代器。
     * @return 当前迭代器的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T>& SeqListIterator<T>::operator++()
    {
        ++IteratorPtr; ///< 顺序表的内存是连续的，将指针自增后即可指向下一元素。
        if (IteratorPtr < IteratorLowerBound || IteratorPtr > IteratorUpperBound) ///< 判断越界，如果越界则抛出异常。
        {
            throw DataStructureException::IteratorOutOfBounds();
        }
        return *this;
    }

    /**
     * @brief 返回此迭代器的副本，然后使迭代器指向下一个元素。
     * @return 当前迭代器的副本的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T> SeqListIterator<T>::operator++(int)
    {
        SeqListIterator<T> it = *this; ///< 创建此迭代器的副本，返回此副本即可。
        ++*this; ///< 由此语句抛出异常。
        return it;
    }

    /**
     * @brief 使此迭代器指向上一个元素后返回此迭代器。
     * @return 当前迭代器的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T>& SeqListIterator<T>::operator--()
    {
        --IteratorPtr;
        if (IteratorPtr < IteratorLowerBound || IteratorPtr > IteratorUpperBound) ///< 判断越界，如果越界则抛出异常。
        {
            throw DataStructureException::IteratorOutOfBounds();
        }
        return *this;
    }

    /**
     * @brief 返回此迭代器的副本，然后使迭代器指向上一个元素。
     * @return 当前迭代器的副本的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T> SeqListIterator<T>::operator--(int)
    {
        SeqListIterator<T> it = *this; ///< 创建此迭代器的副本，返回此副本即可。
        --*this; ///< 由此语句抛出异常。
        return it;
    }

    /**
     * @brief 使此迭代器所指向的位置与偏移量加算后返回自身的引用。
     * @param offset 偏移量。
     * @return 此迭代器的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T>& SeqListIterator<T>::operator+=(int offset)
    {
        IteratorPtr += offset;
        if (IteratorPtr < IteratorLowerBound || IteratorPtr > IteratorUpperBound) ///< 判断越界，如果越界则抛出异常。
        {
            throw DataStructureException::IteratorOutOfBounds();
        }
        return *this;
    }

    /**
     * @brief 使此迭代器所指向的位置与偏移量减算后返回自身的引用。
     * @param offset 偏移量
     * @return 此迭代器的引用。
     * @exception IteratorOutOfBounds 如果迭代器访问越界，抛出此异常。
     */
    template <typename T>
    SeqListIterator<T>& SeqListIterator<T>::operator-=(int offset)
    {
        IteratorPtr -= offset;
        if (IteratorPtr < IteratorLowerBound || IteratorPtr > IteratorUpperBound) ///< 判断越界，如果越界则抛出异常。
        {
            throw DataStructureException::IteratorOutOfBounds();
        }
        return *this;
    }

    /**
     * @brief 此迭代器的三路比较运算符，用于比较此迭代器与目标迭代器所指内存地址的位置关系。
     * @param target 目标迭代器。
     * @return 如果此迭代器的指向的地址在目标迭代器之前，返回 std::strong_ordering::less；
     * @return 如果此迭代器的指向的地址在目标迭代器之后，返回 std::strong_ordering::greater；
     * @return 如果此迭代器与目标迭代器指向同一地址，返回 std::strong_ordering::equal。
     */
    template <typename T>
    std::strong_ordering SeqListIterator<T>::operator<=>(const SeqListIterator& target) const
    {
        if (IteratorPtr < target.IteratorPtr)
        {
            return std::strong_ordering::less;
        }
        else if (IteratorPtr > target.IteratorPtr)
        {
            return std::strong_ordering::greater;
        }
        else
        {
            return std::strong_ordering::equal;
        }
    }

    /**
     * @brief 比较当前迭代器与目标迭代器是否指向不同元素。
     * @param target 目标迭代器。
     * @return 如果当前迭代器与目标迭代器指向不同元素则返回 true ；否则返回 false 。
     * @deprecated 功能将被 operator<=> 取代。
     */
    template <typename T>
    bool SeqListIterator<T>::operator!=(const DataStructureIterator<T>& target) const
    {
        const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target);
        ///< 使用类型转换将 target 转换为 DataStructureIterator 类型。
        return IteratorPtr != temp.IteratorPtr;
    }

    /**
     * @brief 比较当前迭代器与目标迭代器是否指向同一元素。
     * @param target 目标迭代器。
     * @return 如果当前迭代器与目标迭代器指向同一元素则返回 true ；否则返回 false 。
     * @deprecated 功能将被 operator<=> 取代。
     */
    template <typename T>
    bool SeqListIterator<T>::operator==(const DataStructureIterator<T>& target) const
    {
        const SeqListIterator& temp = dynamic_cast<const SeqListIterator&>(target); ///< 同上，不多赘述。
        return IteratorPtr == temp.IteratorPtr;
    }

    /**
     * @brief 返回迭代器所指向的位置与偏移量加算后所对应的迭代器。
     * @tparam U 数据类型。
     * @param iterator 加数迭代器。
     * @param n 偏移量。
     * @return 经过加算后对应位置的迭代器。
     */
    template <typename U>
    SeqListIterator<U> operator+(const SeqListIterator<U>& iterator, int n)
    {
        SeqListIterator<U> result = SeqListIterator<U>(iterator);
        result += n;
        return result;
    }

    /**
     * @brief 返回迭代器所指向的位置与偏移量减算后所对应的迭代器。
     * @tparam U 数据类型。
     * @param iterator 被减数迭代器。
     * @param n 偏移量。
     * @return 经过减算后对应位置的迭代器。
     */
    template <typename U>
    SeqListIterator<U> operator-(const SeqListIterator<U>& iterator, int n)
    {
        SeqListIterator<U> result = SeqListIterator<U>(iterator);
        result -= n;
        return result;
    }

    /**
     * @brief 返回两个迭代器之间的索引差值。
     * @tparam U 
     * @param iteratorL 被减数迭代器。
     * @param iteratorR 减数迭代器。
     * @return 两个迭代器所指位置的索引差值。
     */
    template <typename U>
    int operator-(const SeqListIterator<U>& iteratorL, const SeqListIterator<U>& iteratorR)
    {
        return iteratorL.IteratorPtr - iteratorR.IteratorPtr;
    }

    /**
     * @brief 根据给定的容量创建空顺序表。
     * @param capacity 顺序表的容量。
     * @exception ParamUnacceptableValue 指定的顺序表的容量为 0 时，抛出此异常。
     */
    template <typename T>
    SeqList<T>::SeqList(const size_t capacity)
    {
        if (capacity == 0)
        {
            Clear(); ///< 在抛出异常前主动重置顺序表，以免造成内存泄漏。
            throw DataStructureException::ParamUnacceptableValue();
        }
        else
        {
            DataPtr = new T[capacity];
            Len = 0;
            Capacity = capacity;
        }
    }

    /**
     * @brief 根据给定的容量创建空顺序表，并用默认值初始化所有元素。
     * @param capacity 顺序表的容量。
     * @param defaultVal 用于初始化的默认值。
     * @exception ParamUnacceptableValue 指定的顺序表的容量为 0 时，抛出此异常。
     */
    template <typename T>
    SeqList<T>::SeqList(const size_t capacity, const T& defaultVal)
    {
        if (capacity == 0)
        {
            Clear(); ///< 在抛出异常前主动重置顺序表，以免造成内存泄漏。
            throw DataStructureException::ParamUnacceptableValue();
        }
        else
        {
            DataPtr = new T[capacity];
            Len = capacity;
            Capacity = capacity;
            for (SeqListIterator<T> it = begin(); it != end(); ++it) ///< 使用迭代器为所有元素赋初值。
            {
                *it = defaultVal;
            }
        }
    }

    /**
     * @brief 由已有的数组创建顺序表。
     * @param array 包含要存入顺序表的元素的数组。
     * @param capacity 顺序表的容量。
     * @exception ParamNullptrPassed 传入的指针为 nullptr 时，抛出此异常。
     * @exception ParamUnacceptableValue 指定的顺序表的容量为 0 时，抛出此异常。
     */
    template <typename T>
    SeqList<T>::SeqList(T* array, const size_t capacity)
    {
        if (array == nullptr)
        {
            Clear();
            throw DataStructureException::ParamNullptrPassed();
        }
        else if (capacity == 0)
        {
            Clear();
            throw DataStructureException::ParamUnacceptableValue();
        }
        else
        {
            // 为顺序表分配空间，并且初始化其成员。
            Capacity = capacity;
            Len = capacity;
            DataPtr = new T[capacity];

            // 通过循环将目标数组中的元素复制到顺序表内。
            for (size_t i = 0; i < capacity; ++i)
            {
                DataPtr[i] = array[i];
            }
        }
    }

    /**
     * @brief 由已有顺序表复制构造新顺序表。
     * @param targetToCopy 待复制的顺序表。
     */
    template <typename T>
    SeqList<T>::SeqList(const SeqList& targetToCopy)
    {
        // 为顺序表分配空间，并且初始化其成员。
        Capacity = targetToCopy.Capacity;
        Len = targetToCopy.Len;
        DataPtr = new T[Capacity];

        // 使用迭代器遍历两个顺序表并依次将其赋值。
        for (SeqListIterator<T> it1 = begin(), it2 = targetToCopy.begin(); it1 != end() && it2 != targetToCopy.end(); ++it1, ++it2)
        {
            *it1.IteratorPtr = *it2.IteratorPtr;
        }
    }

    /**
     * @brief 删除顺序表并释放其占用的内存。
     */
    template <typename T>
    SeqList<T>::~SeqList()
    {
        if (DataPtr != nullptr)
        {
            delete[] DataPtr; ///< 释放所占用的内存。
            DataPtr = nullptr; ///< 将指针置空，以免造成访问异常。
        }
    }

    /**
     * @brief 将目标顺序表的所有属性和元素复制到当前数据表。
     * @param targetToCopy 目标顺序表。
     * @return 此顺序表的引用。
     */
    template <typename T>
    SeqList<T>& SeqList<T>::operator=(SeqList targetToCopy)
    {
        /** COPY AND SWAP：利用 std::swap 方法，在拥有复制构造函数的前提下，交换两个指针所对应的对象。*/
        /** 由此，_target_to_copy 成为原有的 *this，在方法调用结束后自然释放。可以自然处理 *this == _target_to_copy 的情况。*/
        std::swap(*this, targetToCopy);
        return *this;
    }

    /**
     * @brief 获取顺序表的 begin 迭代器。
     * @return 指向顺序表第一个元素的迭代器。
     */
    template <typename T>
    SeqListIterator<T> SeqList<T>::begin() const
    {
        return SeqListIterator<T>(*this, 0);
    }

    /**
     * @brief 获取顺序表的 end 迭代器。
     * @return 指向顺序表最后一个元素后的迭代器。
     */
    template <typename T>
    SeqListIterator<T> SeqList<T>::end() const
    {
        return SeqListIterator<T>(*this, Len);
    }

    /**
     * @brief 判断此顺序表是否为空表。
     * @return 如果此顺序表为空表，返回 true ；否则返回 false 。
     */
    template <typename T>
    bool SeqList<T>::Empty() const
    {
        return Len == 0;
    }

    /**
     * @brief 获取顺序表的长度。
     * @return 返回顺序表内的元素个数。
     */
    template <typename T>
    size_t SeqList<T>::Length() const
    {
        return Len;
    }

    /**
     * @brief 获取顺序表的容量。
     * @return 返回顺序表的最大长度。
     */
    template <typename T>
    size_t SeqList<T>::size() const
    {
        return Capacity;
    }

    /**
     * @brief 在顺序表中查找目标元素。
     * @param targetVal 目标元素。
     * @return 如果存在目标元素，返回指向第一个目标元素的迭代器；若不存在，返回 end 迭代器。
     */
    template <typename T>
    SeqListIterator<T> SeqList<T>::Find(const T& targetVal) const
    {
        for (SeqListIterator<T> it = begin(); it != end(); ++it) ///< end 迭代器指向末尾元素的后一位，当 it 与 end() 相等时，即为遍历结束。
        {
            if (*it == targetVal) return it;
        }
        return end();
    }

    /**
     * @brief 获取顺序表目标索引的元素。
     * @param index 目标索引。
     * @return 索引对应的元素。
     * @exception IndexOutOfRange 若索引超出范围，抛出此异常。
     */
    template <typename T>
    const T& SeqList<T>::Get(size_t index) const
    {
        if (index >= Len)
        {
            throw DataStructureException::IndexOutOfRange();
        }
        else
        {
            return DataPtr[index];
        }
    }

    /**
     * @brief 设置顺序表目标索引的元素。
     * @param index 目标索引。
     * @param val 待设定的元素。
     * @return 若设定成功，返回 true；否则返回 false。
     * @exception IndexOutOfRange 若索引超出范围，抛出此异常。
     */
    template <typename T>
    bool SeqList<T>::Set(size_t index, const T& val)
    {
        if (index >= Len)
        {
            throw DataStructureException::IndexOutOfRange();
        }
        else
        {
            DataPtr[index] = val;
            return true;
        }
    }

    /**
     * @brief 从顺序表尾部插入目标元素。
     * @param target 目标元素。
     * @return 若元素插入成功，返回 true；否则返回 false。
     */
    template <typename T>
    bool SeqList<T>::Add(const T& target)
    {
        if (Len == Capacity) ///< 当 Len 与 capacity_ 相等时，表示顺序表已满，插入失败。
        {
            return false;
        }
        else
        {
            DataPtr[Len] = target;
            ++Len;
            return true;
        }
    }

    /**
     * @brief 从目标索引处插入目标元素。
     * @param index 目标索引。
     * @param target 目标元素。
     * @return 若元素插入成功则返回 true；否则返回 false。
     * @exception IndexOutOfRange 若索引超出范围，抛出此异常。
     */
    template <typename T>
    bool SeqList<T>::Insert(size_t index, const T& target)
    {
        if (Len == Capacity) ///< 同上，不再赘述。
        {
            return false;
        }
        else if (index > Len)
        {
            throw DataStructureException::IndexOutOfRange();
        }
        else
        {
            /** 从顺序表末尾依次将元素后移，达到索引处或 size_t 类型向下溢出时停止。*/
            for (size_t i = this->Len - 1; i >= index && i != static_cast<size_t>(-1); --i)
            {
                DataPtr[i + 1] = DataPtr[i];
            }
            /** 插入指定的元素。*/
            DataPtr[index] = target;
            ++Len;
            return true;
        }
    }

    /**
     * @brief 移除目标索引处的元素。
     * @param index 目标索引。
     * @return 若移除成功，返回 true；否则返回 false。
     * @exception AccessEmptyContainer 当容器为空时，抛出此异常。
     * @exception IndexOutOfRange 当索引超出范围时，抛出此异常。
     */
    template <typename T>
    bool SeqList<T>::Remove(size_t index)
    {
        if (Empty())
        {
            throw DataStructureException::AccessEmptyContainer();
        }
        else if (index >= Len)
        {
            throw DataStructureException::IndexOutOfRange();
        }
        else
        {
            for (size_t i = index; i < this->Len - 1; ++i) ///< 只需要将索引后的所有元素前移覆盖掉索引元素即可。
            {
                DataPtr[i] = DataPtr[i + 1];
            }
            --Len; ///< 使长度自减，这样就无法访问末尾未删除的值，末尾的值不用删除。
            return true;
        }
    }

    /**
     * @brief 清空顺序表。
     */
    template <typename T>
    void SeqList<T>::Clear()
    {
        if (DataPtr != nullptr)
        {
            delete[] DataPtr; ///< 释放所占用的内存。
            DataPtr = nullptr; ///< 将指针置空，以免造成访问异常。
        }
        Len = 0;
        Capacity = 0;
    }
}
