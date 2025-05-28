//#pragma once
//#include <list>
//
//template<typename T>
//struct MyComparator {
//    bool operator()(const T& a, const T& b) const {
//        return a < b;
//    }
//};
//
//template<typename T, typename Comparator = MyComparator<T>>
//
//class PriorityQueue {
//public:
//    void push(const T& value) {
//        auto it = m_data.begin();
//        while (it != m_data.end() && comp(*it, value)) {
//            ++it;
//        }
//        m_data.insert(it, value);
//    }
//
//    T poll() {
//        if (m_data.empty()) {
//            return;
//        }
//        T front = m_data.front();
//        m_data.pop_front();
//        return front;
//    }
//private:
//    std::list<T> m_data;
//    MyComparator comp;
//};