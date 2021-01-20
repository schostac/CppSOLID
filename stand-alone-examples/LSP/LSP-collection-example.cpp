#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <cassert>

/* Collection example of LSP (in this case violated). 
 * Imagine that we've implemented vector, array and list containers as follows.
 * It’s just for the sake of learning, perhaps in C++ it would not be a good idea to make
 * standard containers polymorphic and inherit. 
 */

template<typename T>
class Collection {
public:
    virtual ~Collection() = default;
    virtual int size() const = 0;
    virtual int capacity() const = 0;
    virtual void reserve(int) = 0;
    virtual void pushFront(T &&) = 0;
    virtual void popFront() = 0;
    virtual void pushBack(T &&) = 0;
    virtual void popBack() = 0;
};

template<typename T>
class VectorCollection : public Collection<T> {
    std::vector<int> collection;
public:
    int size() const { return collection.size(); };
    int capacity() const { return collection.capacity(); };
    void reserve(int sz) override { return collection.reserve(sz); };
    void pushFront(T && val) override { throw std::logic_error{"Not supported"}; }; // LSP violated
    void popFront() override { throw std::logic_error{"Not supported"}; }; // LSP violated
    void pushBack(T && val) override { collection.push_back(std::move(val)); }
    void popBack() override { return collection.pop_back(); }; 
};

template<typename T, int N>
class ArrayCollection : public Collection<T> {
    std::array<T, N> collection;
public:
    int size() const { return collection.size(); };
    int capacity() const { return size(); }; // LSP violation smell
    void reserve(int sz) override { throw std::logic_error{"Not supported"}; }; // LSP violated
    void pushFront(T && val) override { throw std::logic_error{"Not supported"}; }; // LSP violated
    void popFront() override  { return throw std::logic_error{"Not supported"}; }; // LSP violated
    void pushBack(T && value) override { throw std::logic_error{"Not supported"}; } // LSP violated
    void popBack() override { throw std::logic_error{"Not supported"}; }; // LSP violated
};

template<typename T>
class ListCollection : public Collection<T> {
    std::list<T> collection;
public:
    int size() const { return collection.size(); };
    int capacity() const { return size(); }; // LSP violation smell
    void reserve(int sz) override { throw std::logic_error{"Not supported"}; }; // LSP violated
    void pushFront(T && val) override { collection.push_front(std::move(val)); }
    void popFront() override { collection.pop_front(); }; 
    void pushBack(T && val) override { collection.push_back(std::move(val)); }
    void popBack() override { return collection.pop_back(); };  
};


template<typename T>
void test(Collection<T> & collection) try {    
    collection.pushBack(150);
    std::cout << "Size after pushBack " << collection.size() << std::endl;
    std::cout << "Capacity after pushBack " << collection.capacity() << std::endl;
    
    collection.popBack();
    std::cout << "Size after popBack " << collection.size() << std::endl;
    std::cout << "Capacity after popBack " << collection.capacity() << std::endl;

    if (dynamic_cast<VectorCollection<T>*>(&collection)) { // LSP violation smell
        collection.reserve(10);
        std::cout << "Size after reserve " << collection.size() << std::endl;
        std::cout << "Capacity after reserve " << collection.capacity() << std::endl;
    }
}
catch(const std::exception & e) {
    std::cerr << e.what() << std::endl;
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
