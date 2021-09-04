#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_


#include <mutex>
#include <memory>
#include <vector>


template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue();

    ThreadSafeQueue(const ThreadSafeQueue<T>& rhs);

    ThreadSafeQueue& operator= (ThreadSafeQueue rhs);

    // Put inEle at the back of _list
    void Enque(T inEle);

    // Remove and return at the front of _list
    T Deque();

    // Remove and return at the back of _list
    T PopBack();

    // Remove element at position i of _list
    void Remove(int i);

    // Remove element at position i of _list
    T Get(int i);

    unsigned int Size();

private:
    std::shared_ptr<std::vector<T>> _list;
    std::shared_ptr<std::mutex> _mutex;

};


template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{
    _list = std::make_shared<std::vector<T>>();
    _mutex = std::make_shared<std::mutex>();
}

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T>& rhs)
{
    _list = rhs._list;
    _mutex = rhs._mutex;
}

template<typename T>
ThreadSafeQueue<T>& ThreadSafeQueue<T>::operator= (ThreadSafeQueue<T> rhs)
{
    _list = rhs._list;
    _mutex = rhs._mutex;
    return *this;
}

template<typename T>
void ThreadSafeQueue<T>::Enque(T inEle)
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    //_list.get().push_back(inEle);
    _list->push_back(inEle);
}


template<typename T>
T ThreadSafeQueue<T>::Deque()
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    T ret = (*_list.get())[0];
    _list->erase(_list->begin());
    return ret;
}


template<typename T>
T ThreadSafeQueue<T>::PopBack()
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    return _list->pop_back();
}


template<typename T>
void ThreadSafeQueue<T>::Remove(int i)
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    _list->erase(_list->begin() + i);
}

// Remove element at position i of _list
template<typename T>
T ThreadSafeQueue<T>::Get(int i)
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    return (*_list.get())[i];
}

template<typename T>
unsigned int ThreadSafeQueue<T>::Size()
{
    std::lock_guard<std::mutex> guard(*_mutex.get());
    return (unsigned int)_list->size();
}

#endif