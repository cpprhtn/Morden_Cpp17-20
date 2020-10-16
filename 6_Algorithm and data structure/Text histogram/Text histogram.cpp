//텍스트 히스토그램
/*
텍스트가 주어졌을 때 텍스트 안에 등장하는 알파벳 문자의 등장 빈도에 대한 히스토그램을 구하고 출력하는 프로그램 작성.
등장 빈도는 전체 문자의 수에서 각 문자가 등장하는 횟수를 백분율로 나타낸 것
- 오직 알파벳 문자만 계산해야 하며 숫자나 기호, 다른 문자들은 무시
- 등장 빈도는 문자의 등장 횟수로만 결정되며 텍스트의 길이와는 무관
*/

#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>
#include <string_view>

std::map<char, double> analyze_text(std::string_view text)
{
   std::map<char, double> frequencies;
   for (char ch = 'a'; ch <= 'z'; ch++)
      frequencies[ch] = 0;

   for (auto ch : text)
   {
      if (isalpha(ch))
         frequencies[tolower(ch)]++;
   }

   auto total = std::accumulate(
      std::cbegin(frequencies), std::cend(frequencies),
      0ull,
      [](auto const sum, auto const & kvp) {
      return sum + static_cast<unsigned long long>(kvp.second);
   });

   std::for_each(
      std::begin(frequencies), std::end(frequencies),
      [total](auto & kvp) {
      kvp.second = (100.0 * kvp.second) / total;
   });

   return frequencies;
}

int main()
{
   auto result = analyze_text(R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.)");

   for (auto const & kvp : result)
   {
      std::cout
         << kvp.first << " : "
         << std::fixed
         << std::setw(5) << std::setfill(' ')
         << std::setprecision(2) << kvp.second << std::endl;
   }
}
