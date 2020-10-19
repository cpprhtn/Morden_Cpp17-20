//전화번호 목록 변형
/*
주어진 목록에 있는 전화번호 모두를 변환해 + 기호로 시작하는 특정한 국가 코드를 앞에 덧붙이는 함수 생성
- 전화번호 안의 모든 공백은 제거
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool starts_with(std::string_view str, std::string_view prefix)
{
   return str.find(prefix) == 0;
}

void normalize_phone_numbers(
   std::vector<std::string>& numbers,
   std::string const & countryCode)
{
   std::transform(
      std::cbegin(numbers), std::cend(numbers),
      std::begin(numbers),
      [countryCode](std::string const & number) {
      std::string result;
      if (number.size() > 0)
      {
         if (number[0] == '0')
            result = "+" + countryCode + number.substr(1);
         else if (starts_with(number, countryCode))
            result = "+" + number;
         else if (starts_with(number, "+" + countryCode))
            result = number;
         else
            result = "+" + countryCode + number;
      }

      result.erase(
         std::remove_if(
            std::begin(result), std::end(result),
            [](const char ch) {return isspace(ch); }),
         std::end(result));

      return result;
   });
}

int main()
{
   std::vector<std::string> numbers{
      "07555 123456",
      "07555123456",
      "+44 7555 123456",
      "44 7555 123456",
      "7555 123456"
   };

   normalize_phone_numbers(numbers, "44");

   for (auto const & number : numbers)
   {
      std::cout << number << std::endl;
   }
}
