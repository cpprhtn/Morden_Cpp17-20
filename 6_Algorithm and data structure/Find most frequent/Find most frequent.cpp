//범위 안에서 가장 빈번하게 등장하는 원소와 등장 횟수 반환
/*
주어진 범위 안에서 가장 빈번하게 나타나는 원소와 그 등장 횟수를 반환하는 함수를 작성
- 가장 많이 나타나는 원소가 둘 이상이라면 해당하는 모든 원소를 반환해야 함
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<std::pair<T, size_t>> find_most_frequent(std::vector<T> const & range)
{
   std::map<T, size_t> counts;

   for (auto const & e : range) counts[e]++;

   auto maxelem = std::max_element(
      std::cbegin(counts), std::cend(counts),
      [](auto const & e1, auto const & e2) {
         return e1.second < e2.second;
      });

   std::vector<std::pair<T, size_t>> result;

   std::copy_if(
      std::begin(counts), std::end(counts),
      std::back_inserter(result),
      [maxelem](auto const & kvp) {
         return kvp.second == maxelem->second;
      });
      
   return result;
}

int main()
{
   auto range = std::vector<int>{1,1,3,5,8,13,3,5,8,8,5};
   auto result = find_most_frequent(range);

   for (auto const & e : result)
   {
      std::cout << e.first << " : " << e.second << std::endl;
   }
}
