# SeqList.hpp

此文件定义了顺序表的简单实现。类均定义在 `DataStructure` 命名空间内。

## SeqListIterator 类

|成员列表|可见性|简介|
| :---------------------------------------------------------------------- | :-----: | :-------------------------------- |
|`SeqListIterator(T* ptr);`                                               |`public` |利用元素指针构造迭代器。|
|`T& operator*() override;`                                               |`public` |返回迭代器所指元素的引用。|
|`const T& operator*() const override`                                    |`public` |返回迭代器所指元素的 `const` 引用。|
|`SeqListIterator& operator++() override;`                                |`public` |使迭代器向后索引并返回元素的引用。|
|`SeqListIterator& operator++(int) override;`                             |`public` |返回当前元素的引用并使迭代器向后索引。|
|`bool operator!=(const DataStructureIterator<T>& target) const override;`|`public` |判断两个迭代器所指的元素是否不为同一元素。|
|`bool operator==(const DataStructureIterator<T>& target) const override;`|`public` |判断两个迭代器所指的元素是否为同一元素。|
|`T& m_ptr`                                                               |`private`|迭代器当前所指向的元素的地址。|

## SeqList 类

|成员列表|可见性|简介|
| :----------------------------------------------------------------- | :----: | :------------------ |
|`SeqList(size_t size);`                                             |`public`|根据大小构建顺序表。|
|`SeqList(T* target, size_t size);`                                  |`public`|利用数组构造顺序表。|
|`SeqList<T>::SeqList(const SeqList& target);`                       |`public`|利用另一个顺序表复制构造。|
|`~SeqList() override;`                                              |`public`|析构顺序表。|
|`SeqList<T>& SeqList<T>::operator=(SeqList target);`                |`public`|完成顺序表间的赋值。|
|`SeqListIterator<T> begin();`                                       |`public`|返回 `begin()` 迭代器。|
|`SeqListIterator<T> end();`                                         |`public`|返回 `end()` 迭代器。|
|`bool empty() const override;`                                      |`public`|判断顺序表是否为空。|
|`size_t length() const override;`                                   |`public`|返回顺序表的长度。|
|`size_t size() const override;`                                     |`public`|返回顺序表的容量。|
|`SeqListIterator<T> SeqList<T>::find(const T& target) const;`       |`public`|在顺序表中查找指定元素。|
|`const T& get(size_t index) const override;`                        |`public`|返回指定索引的元素。|
|`bool set(size_t index, const T& target) override;`                 |`public`|设定指定索引的元素。|
|`bool add(const T& target) override;`                               |`public`|从顺序表尾部添加元素。|
|`bool insert(size_t index, const T& target);`                       |`public`|从指定下标处插入元素。|
|`bool remove(size_t index);`                                        |`public`|移除指定下标处的元素。|
|`size_t iterator_to_index(const SeqListIterator<T> iterator) const;`|`public`|返回迭代器对应的索引。|
|`SeqListIterator<T> index_to_iterator(size_t index) const;`         |`public`|返回索引对应的迭代器。|
|`void reset();`                                                     |`public`|重置顺序表。|
