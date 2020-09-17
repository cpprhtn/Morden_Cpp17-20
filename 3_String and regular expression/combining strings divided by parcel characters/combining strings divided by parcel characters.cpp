//구획 문자로 나누어진 문자열 조합
/*
문자열 리스트와 구획 문자가 주어졌을 때, 구획 문자를 사이에 두고 주어진 문자 열들을 합쳐 하나의 새로운 문자열을 만드는 함수를 작성
구획 문자는 마지막 문자열 뒤에는 나타나지 않아야 하며, 입력 문자열이 주어지지 않을 경우 함수는 빈 문자열을 반환해야 함
*/

#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <array>
#include <list>
#include <assert.h>

template <typename Iter>
std::string join_strings(Iter begin, Iter end, char const * const separator)
{
   std::ostringstream os;
   std::copy(begin, end-1, std::ostream_iterator<std::string>(os, separator));
   os << *(end-1);
   return os.str();
}


template <typename C>
std::string join_strings(C const & c, char const * const separator)
{
   if (c.size() == 0) return std::string{};
   return join_strings(std::begin(c), std::end(c), separator);
}

int main()
{
   using namespace std::string_literals;

   std::vector<std::string> v1{ "this","is","an","example" };
   std::vector<std::string> v2{ "example" };
   std::vector<std::string> v3{ };
   
   assert(
      join_strings(v1, " ") == "this is an example"s);

   assert(
      join_strings(v2, " ") == "example"s);

   assert(
      join_strings(v3, " ") == ""s);

   std::array<std::string, 4> a1{ {"this","is","an","example"} };
      std::array<std::string, 1> a2{ {"example"} };
   std::array<std::string, 0> a3{};

   assert(
      join_strings(a1, " ") == "this is an example"s);

   assert(
      join_strings(a2, " ") == "example"s);

   assert(
      join_strings(a3, " ") == ""s);
}
