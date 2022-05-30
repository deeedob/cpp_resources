#include <cstddef>
#include <memory>
#include <mutex>
#include <iostream>

using namespace std;

template<typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t size)
        : buffer(unique_ptr<T[]>(new T[size])),
          max_size(size)
        {}

    void push_back( T item) {
        lock_guard<mutex> lock(mtx);
        buffer[head] = item;
        if(full_) {
            tail = (tail + 1) % max_size;
        }
        head = (head + 1) % max_size;
        full_ = (head == tail);
    }

    T pop_front() {
        lock_guard<mutex> lock(mtx);
        if(empty())
            return T();

        auto val = buffer[tail];
        full_ = false;
        tail = (tail + 1) % max_size;
        return val;
    }

    void reset() {
        lock_guard<mutex> lock(mtx);
        head = tail;
        full_ = false;
    }

    bool empty() const {
        return (!full_ && (head == tail));
    }

    bool full() const {
        return full_;
    }

    size_t capacity() const {
        return max_size;
    }

    size_t size() const {
        size_t size = max_size;
        if(!full_) {
            size = (head >= tail) ? (head - tail) : (max_size + head - tail);
        }
        return size;
    }

private:
    std::mutex mtx;
    unique_ptr<T[]> buffer;
    size_t head = 0;
    size_t tail = 0;
    const size_t max_size;
    bool full_ = false;
};


int main() {
    CircularBuffer<char> cb(10);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.push_back('D');

    cout << cb.pop_front() << endl;
    cout << cb.pop_front() << endl;
    cout << cb.pop_front() << endl;
    cb.push_back('E');
    cout << cb.pop_front() << endl;
    cout << cb.pop_front() << endl;

    return 0;
}