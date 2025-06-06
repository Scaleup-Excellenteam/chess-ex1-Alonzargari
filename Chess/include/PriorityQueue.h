#pragma once
#include <list>
#include <iostream>
#include <algorithm>
#include <memory>

template<typename T>
struct MyComparator {
    bool operator()(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b) const {
        return *a < *b;
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
        m_data.insert(it, std::move(value)); 
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
    int count = 0;
    auto it = pq.end();

    while (it != pq.begin() && count < 3) {
        --it;
        os << **it << "\n";
        ++count;
    }

    return os;
}