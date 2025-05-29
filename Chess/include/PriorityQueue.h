#pragma once
#include <list>
#include <iostream>
#include <algorithm>

template<typename T>
struct MyComparator {
    bool operator()(const T* a, const T* b) const {
        return a < b;
    }
};

template<typename T, typename Comparator = MyComparator<T>>

class PriorityQueue {
public:
    void push(T value) {
        auto it = m_data.begin();
        while (it != m_data.end() && comp(*it, value)) {
            ++it;
        }
        m_data.insert(it, value);
    }

    void poll() {
        if (!m_data.empty()) {
            m_data.pop_front();
        }
    }

    int size() const { return m_data.size();}
    auto begin() const { return m_data.begin(); }
    auto end() const { return m_data.end(); }


private:
    std::list<T> m_data;
    Comparator comp;
};

template<typename T, typename Comparator>
std::ostream& operator<<(std::ostream& os, const PriorityQueue<T, Comparator>& pq) {
    std::for_each(pq.begin(), pq.end(), [&os](const T& item) {
        os << *item << "\n";
        });
    return os;
}