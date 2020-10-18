//전화번호 목록 필터링
/*
전화번호 목록이 주어졌을 때 특정 국가의 전화번호만을 반환하는 함수를 작성
- 전화번호의 국가는 국가번호로 결정 (ex)영국의 국가번호는 44
- 전화번호는 +기호로 시작하는 국가번호가 앞에 있거나, 국가번호가 생략돼 있을 수도 있음
- 국가번호가 없는 번호는 무시
*/

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>

bool starts_with(std::string_view str, std::string_view prefix)
{
   return str.find(prefix) == 0;
}

template <typename InputIt>
std::vector<std::string> filter_numbers(
   InputIt begin, InputIt end,
   std::string const & countryCode)
{
   std::vector<std::string> result;

   std::copy_if(
      begin, end,
      std::back_inserter(result),
      [countryCode](auto const & number) {
      return starts_with(number, countryCode) ||
             starts_with(number, "+" + countryCode);
   });

   return result;
}

std::vector<std::string> filter_numbers(
   std::vector<std::string> const & numbers,
   std::string const & countryCode)
{
   return filter_numbers(
      std::cbegin(numbers), std::cend(numbers), 
      countryCode);
}


int main()
{
   std::vector<std::string> numbers{
      "+40744909080",
      "44 7520 112233",
      "+44 7555 123456",
      "40 7200 123456",
      "7555 123456"
   };

   auto result = filter_numbers(numbers, "44");

   for (auto const & number : result)
   {
      std::cout << number << std::endl;
   }
}
