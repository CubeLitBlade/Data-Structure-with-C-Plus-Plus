# SeqList.h
���ļ�������˳���ļ�ʵ�֡����������`DataStructure`�����ռ��ڡ�

## SeqListIterator ��
|�����б�|���|
| :---------------------------------------------------------------------: | :-------------------------------: |
|`SeqListIterator(T* ptr);`                                               |����Ԫ��ָ�빹���������|
|`T& operator*() override;`                                               |���ص�������ָԪ�ص����á�|
|`const T& operator*() const override`                                    |���ص�������ָԪ�ص� `const` ���á�|
|`SeqListIterator& operator++() override;`                                |ʹ�������������������Ԫ�ص����á�|
|`SeqListIterator& operator++(int) override;`                             |���ص�ǰԪ�ص����ò�ʹ���������������|
|`bool operator!=(const DataStructureIterator<T>& target) const override;`|�ж�������������ָ��Ԫ���Ƿ�ΪͬһԪ�ء�|
|`bool operator==(const DataStructureIterator<T>& target) const override;`|�ж�������������ָ��Ԫ���Ƿ�ΪͬһԪ�ء�|

## SeqList ��
|�����б�|���|
| :----------------------------------------------------------: | :-----------------: |
|`SeqList(size_t size);`                                       |���ݴ�С����˳���|
|`SeqList(T* target, size_t size);`                            |�������鹹��˳���|
|`SeqList<T>::SeqList(const SeqList& target);`                 |������һ��˳����ƹ��졣|
|`~SeqList() override;`                                        |����˳���|
|`SeqList<T>& SeqList<T>::operator=(SeqList target);`          |���˳����ĸ�ֵ��|
|`SeqListIterator<T> begin();`                                 |���� `begin()` ��������|
|`SeqListIterator<T> end();`                                   |���� `end()` ��������|
|`bool empty() const override;`                                |�ж�˳����Ƿ�Ϊ�ա�|
|`size_t length() const override;`                             |����˳���ĳ��ȡ�|
|`size_t size() const override;`                               |����˳����������|
|`SeqListIterator<T> SeqList<T>::find(const T& target) const;` |��˳����в���ָ��Ԫ�ء�|
|`const T& get(size_t index) const override;`                  |����ָ���±��Ԫ�ء�|
|`bool set(size_t index, const T& target) override;`           |�趨ָ���±��Ԫ�ء�|
|`bool add(const T& target) override;`                         |��˳���β�����Ԫ�ء�|
|`bool insert(size_t index, const T& target);`                 |��ָ���±괦����Ԫ�ء�|
|`bool remove(size_t index);`                                  |�Ƴ�ָ���±괦��Ԫ�ء�|
|`SeqListIterator<T> begin()`                                  |���� `begin()` ��������|
|`SeqListIterator<T> end()`                                    |���� `end()` ��������|
|`void reset();`                                               |����˳���|

