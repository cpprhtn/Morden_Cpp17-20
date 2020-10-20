//쌍 알고리즘
/*
어떤 범위가 주어졌을 때, 연속한 두 원소를 쌍으로 묶고 새로운 범위를 만들어 변환하는 범용 함수 작성
- 입력 범위에 원소가 홀수 개 있으면 마지막 원소는 무시
*/

#include <iostream>
#include <vector>

template <typename Input, typename Output>
void pairwise(Input begin, Input end, Output result)
{
   auto it = begin;
   while (it != end)
   {
      auto v1 = *it++; if (it == end) break;
      auto v2 = *it++;
      result++ = std::make_pair(v1, v2);
   }
}

template <typename T>
std::vector<std::pair<T, T>> pairwise(std::vector<T> const & range)
{
   std::vector<std::pair<T, T>> result;
   pairwise(std::begin(range), std::end(range),
      std::back_inserter(result));

   return result;
}

int main()
{
   std::vector<int> v{ 1, 1, 3, 5, 8, 13, 21 };

   auto result = pairwise(v);

   for (auto const & p : result)
   {
      std::cout << '{' << p.first << ',' << p.second << '}' << std::endl;
   }
}
