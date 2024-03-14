# SeqList.h
此文件定义了顺序表的简单实现。类均定义在`DataStructure`命名空间内。

## SeqListIterator 类
|方法列表|简介|
| :---------------------------------------------------------------------: | :-------------------------------: |
|`SeqListIterator(T* ptr);`                                               |利用元素指针构造迭代器。|
|`T& operator*() override;`                                               |返回迭代器所指元素的引用。|
|`const T& operator*() const override`                                    |返回迭代器所指元素的 `const` 引用。|
|`SeqListIterator& operator++() override;`                                |使迭代器向后索引并返回元素的引用。|
|`SeqListIterator& operator++(int) override;`                             |返回当前元素的引用并使迭代器向后索引。|
|`bool operator!=(const DataStructureIterator<T>& target) const override;`|判断两个迭代器所指的元素是否不为同一元素。|
|`bool operator==(const DataStructureIterator<T>& target) const override;`|判断两个迭代器所指的元素是否为同一元素。|

## SeqList 类
|方法列表|简介|
| :----------------------------------------------------------: | :-----------------: |
|`SeqList(size_t size);`                                       |根据大小构建顺序表。|
|`SeqList(T* target, size_t size);`                            |利用数组构造顺序表。|
|`SeqList<T>::SeqList(const SeqList& target);`                 |利用另一个顺序表复制构造。|
|`~SeqList() override;`                                        |析构顺序表。|
|`SeqList<T>& SeqList<T>::operator=(SeqList target);`          |完成顺序表间的赋值。|
|`SeqListIterator<T> begin();`                                 |返回 `begin()` 迭代器。|
|`SeqListIterator<T> end();`                                   |返回 `end()` 迭代器。|
|`bool empty() const override;`                                |判断顺序表是否为空。|
|`size_t length() const override;`                             |返回顺序表的长度。|
|`size_t size() const override;`                               |返回顺序表的容量。|
|`SeqListIterator<T> SeqList<T>::find(const T& target) const;` |在顺序表中查找指定元素。|
|`const T& get(size_t index) const override;`                  |返回指定下标的元素。|
|`bool set(size_t index, const T& target) override;`           |设定指定下标的元素。|
|`bool add(const T& target) override;`                         |从顺序表尾部添加元素。|
|`bool insert(size_t index, const T& target);`                 |从指定下标处插入元素。|
|`bool remove(size_t index);`                                  |移除指定下标处的元素。|
|`SeqListIterator<T> begin()`                                  |返回 `begin()` 迭代器。|
|`SeqListIterator<T> end()`                                    |返回 `end()` 迭代器。|
|`void reset();`                                               |重置顺序表。|

