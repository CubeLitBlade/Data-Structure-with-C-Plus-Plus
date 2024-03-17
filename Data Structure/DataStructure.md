# DataStructure.hpp

此文件定义了两个命名空间。`DataStructure` 命名空间中包含了所有数据结构及其迭代器的基类。而 `DataStructureException` 命名空间中定义了这些数据结构所使用的异常类。

## DataStructure 命名空间

在此命名空间中定义了数据结构及其迭代器的基类。

### DataStructureIterator 类

此类是所有数据结构迭代器的抽象基类，定义了一些公用接口。这些接口在派生类中应当全部实现。

|接口|功能|
| :--------------------------------------------------------------------: | :-----------------------------------------: |
|`virtual ~DataStructureIterator();`                                     |析构迭代器。|
|`virtual T& operator*();`                                               |返回迭代器所指定元素的引用。|
|`virtual const T& operator*() const;`                                   |返回迭代器所指定元素的 `const` 引用。|
|`virtual DataStructureIterator& operator++();`                          |使迭代器访问下一个元素，并且返回对自身的引用。|
|`virtual DataStructureIterator& operator++(int);`                       |返回对自身的一个副本的引用，并使迭代器访问下一个元素。|
|`virtual bool operator!=(const DataStructureIterator<T>& target) const;`|判断两个迭代器是否指向不同的元素。|
|`virtual bool operator==(const DataStructureIterator<T>& target) const;`|判断两个迭代器是否指向同一个元素。|

### DataStructure 类

此类是所有数据结构的抽象基类，定义了一些公用接口。这些接口在派生类中应当全部实现。

|接口|功能|
| :----------------------------------------------: | :----------------: |
|`virtual ~DataStructure();`                       |析构数据结构。|
|`virtual bool empty() const;`                     |判断数据结构是否为空。|
|`virtual size_t length() const = 0;`              |获取数据结构的长度。|
|`virtual size_t size() const = 0;`                |获取数据结构的容量。|
|`virtual const T& get(size_t index) const;`       |获取相应索引的元素。|
|`virtual bool set(size_t index, const T& target);`|设置相应索引的元素。|
|`virtual bool add(const T& target);`              |在数据结构尾部添加元素。|

## DataStructureException 命名空间

在此命名空间中定义了数据结构所使用的异常类。这些异常类派生自标准异常类。因此，您既可以捕获这些异常类，也可以捕获他们的基类。
除此之外，这些类包含默认的错误信息。如果您没有传入错误信息的话，将使用默认的错误信息。

|异常类|派生自|默认错误信息|常见错误情况|
|:------------------------:|:---------------------:|:--------------------------------:|:------------------:|
|`param_nullptr_passed`    |`std::invalid_argument`|`"nullptr passed as parameter(s)"`|传入的指针参数是空指针。|
|`param_unacceptable_value`|`std::invalid_argument`|`"value passed is unacceptable"`  |传入的值参数无效。|
|`index_out_of_range`      |`std::out_of_range`    |`"index out of range"`            |索引越界。|
|`iterator_out_of_bounds`  |`std::out_of_range`    |`"iterator access out of bounds"` |迭代器访问越界。|
|`access_empty_container`  |`std::out_of_range`    |`"container is empty"`            |尝试访问空容器。|
