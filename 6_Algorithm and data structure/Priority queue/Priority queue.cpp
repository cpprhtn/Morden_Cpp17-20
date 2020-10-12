//우선순위 큐 데이터 구조 구현
/*
가장 큰 원소를 탐색하는 작업은 상수 시간안에, 원소를 추가하거나 제거하는 작업은 로그 시간 복잡도 안에 이뤄져야 함
새로운 원소는 큐의 끝에 삽입되며, 제거 연산은 꼭대기에 있는 원소부터 진행 돼야 함
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include<assert.h>

template <class T,
   class Compare = std::less<typename std::vector<T>::value_type>>
   class priority_queue
{
   typedef typename std::vector<T>::value_type      value_type;
   typedef typename std::vector<T>::size_type       size_type;
   typedef typename std::vector<T>::reference       reference;
   typedef typename std::vector<T>::const_reference const_reference;
public:
   bool empty() const noexcept { return data.empty(); }
   size_type size() const noexcept { return data.size(); }

   void push(value_type const & value)
   {
      data.push_back(value);
      std::push_heap(std::begin(data), std::end(data), comparer);
   }

   void pop()
   {
      std::pop_heap(std::begin(data), std::end(data), comparer);
      data.pop_back();
   }

   const_reference top() const { return data.front(); }

   void swap(priority_queue& other) noexcept
   {
      swap(data, other.data);
      swap(comparer, other.comparer);
   }

private:
   std::vector<T> data;
   Compare comparer;
};

template< class T, class Compare>
void swap(
   priority_queue<T, Compare>& lhs,
   priority_queue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
   lhs.swap(rhs);
}

int main()
{
   priority_queue<int> q;
   for (int i : {1, 5, 3, 1, 13, 21, 8})
   {
      q.push(i);
   }

   assert(!q.empty());
   assert(q.size() == 7);

   while (!q.empty())
   {
      std::cout << q.top() << ' ';
      q.pop();
   }
}
