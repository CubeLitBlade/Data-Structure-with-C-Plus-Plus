# SeqList.hpp

此文件定义了顺序表的简单实现。类均定义在 `DataStructure` 命名空间内。

## SeqListIterator 类

### SeqListIterator 公有成员

|成员列表|
| :------------------------------------------------------------------------ |
|`SeqListIterator(const SeqList<T>& target, size_t index);`                 |
|`SeqListIterator(const SeqListIterator<T>& target);`                       |
|`const T& operator*() const override;`                                     |
|`T& operator*() override;`                                                 |
|`T& operator[](int index);`                                                |
|`SeqListIterator& operator=(SeqListIterator<T> target);`                   |
|`SeqListIterator& operator++() override;`                                  |
|`SeqListIterator operator++(int);`                                         |
|`SeqListIterator& operator--();`                                           |
|`SeqListIterator operator--(int);`                                         |
|`SeqListIterator& operator+=(int offset);`                                 |
|`SeqListIterator& operator-=(int offset);`                                 |
|`std::strong_ordering operator<=>(const SeqListIterator& target) const;`   |

### SeqListIterator 私有成员

|成员列表|
| :---------------------------- |
|`T* IteratorPtr;`              |
|`const T* IteratorLowerBound;` |
|`const T* IteratorUpperBound;` |

### SeqListIterator 友元

|友元列表|
| :-------------------------------------------------------------------------------------------------------------------- |
|`template <typename U> friend SeqListIterator<U> operator+(const SeqListIterator<U>& iterator, int n);`                |
|`template <typename U> friend SeqListIterator<U> operator-(const SeqListIterator<U>& iterator, int n);`                |
|`template <typename U> friend int operator-(const SeqListIterator<U>& iteratorL, const SeqListIterator<U>& iteratorR);`|

### 即将废除

|成员列表|
| :---- |
|`bool operator!=(const DataStructureIterator<T>& target) const override;`|
|`bool operator==(const DataStructureIterator<T>& target) const override;`|

## SeqList 类

### SeqList 公有成员

|成员列表|
| :---------------------------------------------------- |
|`explicit SeqList(size_t capacity);`                   |
|`SeqList(size_t capacity, const T& defaultVal);`       |
|`SeqList(T* array, size_t capacity);`                  |
|`SeqList(const SeqList& targetToCopy);`                |
|`~SeqList() override;`                                 |
|`SeqListIterator<T> begin() const;`                    |
|`SeqListIterator<T> end() const;`                      |
|`SeqList& operator=(SeqList targetToCopy);`            |
|`bool Empty() const override;`                         |
|`size_t Length() const override;`                      |
|`size_t size() const override;`                        |
|`SeqListIterator<T> Find(const T& targetVal) const;`   |
|`const T& Get(size_t index) const override;`           |
|`bool Set(size_t index, const T& val) override;`       |
|`bool Add(const T& target) override;`                  |
|`bool Insert(size_t index, const T& target);`          |
|`bool Remove(size_t index);`                           |
|`void Clear();`                                        |

### SeqList 私有成员

|成员列表|
| :--- |
|`T* DataPtr = nullptr;`    |
|`size_t Len = 0;`          |
|`size_t Capacity = 0;`     |

### SeqList 友元

|友元列表|
| :------------------------ |
|`class SeqListIterator<T>;`|
