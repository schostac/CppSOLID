#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <cassert>

/* Collection example of LSP (continuation of the previous example, not really better). 
 * Imagine that we've implemented vector, array and list containers as follows.
 * Note problems and complexity with multiple inheritance.
 * With excessive abstraction it's easier to violate LSP.
 * Plus virtual functions cannot be template functions.
 * So it would not be a good idea to make standard containers polymorphic and inherit.
 */

class Iterator {};

template<typename T>
class Collection {
public:
    virtual ~Collection() = default;
    virtual int size() const = 0;
};

template<typename T>
class DynamicCollection : public Collection<T> {
public:
    virtual Iterator insert(Iterator, T&&) = 0;
    virtual int erase(Iterator, const T&) = 0;
};

template<typename T>
class ContiguousCollection : public Collection<T> {
public:
    virtual T& operator[](int) = 0; 
};

template<typename T>
class PreallocatableCollection : public virtual ContiguousCollection<T>,
                                 public virtual DynamicCollection<T> {
public:
    virtual int capacity() const = 0;
    virtual void reserve(int) = 0;
};

template<typename T>
class StaticCollection : public ContiguousCollection<T> {
};

template<typename T>
class UnidirectionalCollection : public DynamicCollection<T> {
public:
    virtual void pushBack(T &&) = 0;
    virtual void popBack() = 0;
};

template<typename T>
class BidirectionalCollection : public UnidirectionalCollection<T> {
public:
    virtual void pushFront(T &&) = 0;
    virtual void popFront() = 0;
};

template<typename T, int N>
class ArrayCollection : public StaticCollection<T> {
    std::array<T, N> collection;
public:
    int size() const { return collection.size(); };
    T& operator[](int i) override { return collection[i]; } 
};

template<typename T>
class ListCollection : public BidirectionalCollection<T> {
    std::list<T> collection;
public:
    int size() const { return collection.size(); };
    int capacity() const { return size(); };
    void pushFront(T && val) override { collection.push_front(std::move(val)); }
    void popFront() override { collection.pop_front(); };  
    void pushBack(T && val) override { collection.push_back(std::move(val)); }
    void popBack() override { collection.pop_back(); };
    Iterator insert(Iterator, T&&) override { /* Implementation omitted */ return {}; };
    int erase(Iterator, const T&) override { /* Implementation omitted */ return {}; };
};

template<typename T>
class VectorCollection : public virtual UnidirectionalCollection<T>,
                         public virtual PreallocatableCollection<T>,
                         public virtual ContiguousCollection<T> {
    std::vector<int> collection;
public:
    int size() const { return collection.size(); };
    int capacity() const { return collection.capacity(); };
    T& operator[](int i) override { return collection[i]; } 
    void reserve(int sz) override { return collection.reserve(sz); };
    void pushBack(T && val) override { collection.push_back(std::move(val)); }
    void popBack() override { collection.pop_back(); };
    Iterator insert(Iterator, T&&) override { /* Implementation omitted */ return {}; };
    int erase(Iterator, const T&) override { /* Implementation omitted */ return {}; };
};

template<typename T>
void test(Collection<T> & collection) {
    collection.size();    
}

template<typename T>
void test(UnidirectionalCollection<T> & collection) {
    collection.pushBack(150);
    collection.popBack();
}

template<typename T>
void test(BidirectionalCollection<T> & collection) {
    collection.pushFront(150);
    collection.popFront();

    collection.pushBack(150);
    collection.popBack();
}

int main() {
    VectorCollection<int> vec;
    ArrayCollection<int, 5> arr;
    ListCollection<int> lst;

    std::cout << "Test VectorCollection" << std::endl;
    test(vec);
    std::cout << std::endl;

    std::cout << "Test ArrayCollection" << std::endl;
    test(arr);
    std::cout << std::endl;

    std::cout << "Test ListCollection" << std::endl;
    test(lst);
    std::cout << std::endl;
}
