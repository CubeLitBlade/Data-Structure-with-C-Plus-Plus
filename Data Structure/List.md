# List.hpp

此文件定义了链表的简单实现。类均定义在 `DataStructure` 命名空间内。

## ListNode 类

|成员列表|可见性|简介|
| :------------------------------------------ | :-----: |:------------------|
|`ListNode(ListNode<T>* next, const T& data);`|`public` |构造元素节点。|
|`ListNode* m_next`                           |`private`|指向下一个节点的指针。|
|`T m_data`                                   |`private`|节点所存储的数据。|

## ListIterator 类

|成员列表|可见性|简介|
| :---------------------------------------------------------------------- | :-----: | :-------------------------------- |
|`ListIterator(ListNode<T>* ptr);`                                        |`public` |利用元素节点指针构造迭代器。|
|`T& operator*() override;`                                               |`public` |返回迭代器所指节点数据的引用。|
|`const T& operator*() const override`                                    |`public` |返回迭代器所指节点数据的 `const` 引用。|
|`ListIterator& operator++() override;`                                   |`public` |使迭代器向后索引并返回迭代器的引用。|
|`ListIterator& operator++(int) override;`                                |`public` |返回当前迭代器的引用并使迭代器向后索引。|
|`bool operator!=(const DataStructureIterator<T>& target) const override;`|`public` |判断两个迭代器所指的节点是否不指向同一节点。|
|`bool operator==(const DataStructureIterator<T>& target) const override;`|`public` |判断两个迭代器所指的节点是否为同一节点。|
|`ListNode<T>* m_ptr`                                                     |`private`|迭代器当前所指向的节点的地址。|

## List 类

|成员列表|可见性|简介|
| :------------------------------------------------ | :----: | :------------------ |
|`List();`                                          |`public`|构建空链表。|
|`List(const SeqList& target);`                     |`public`|利用另一个链表复制构造。|
|`~List() override;`                                |`public`|析构链表。|
|`List<T>& operator=(List target);`                 |`public`|完成链表间的赋值。|
|`ListIterator<T> begin();`                         |`public`|返回 `begin()` 迭代器。|
|`ListIterator<T> end();`                           |`public`|返回 `end()` 迭代器。|
|`bool empty() const override;`                     |`public`|判断链表是否为空。|
|`size_t length() const override;`                  |`public`|返回链表的长度。|
|`size_t size() const override;`                    |`public`|返回链表的容量。|
|`ListIterator<T> find(const T& target) const;`     |`public`|在链表中查找指定元素。|
|`const T& get(size_t index) const override;`       |`public`|返回指定索引的元素。|
|`bool set(size_t index, const T& target) override;`|`public`|设定指定索引的元素。|
|`bool add(const T& target) override;`              |`public`|从链表尾部添加元素。|
|`bool he_add(const T& target) override;`           |`public`|从链表头部添加元素。|
|`bool insert(size_t index, const T& target);`      |`public`|从指定下标处插入元素。|
|`bool remove(size_t index);`                       |`public`|移除指定下标处的元素。|
|`void reset();`                                    |`public`|重置链表。|
