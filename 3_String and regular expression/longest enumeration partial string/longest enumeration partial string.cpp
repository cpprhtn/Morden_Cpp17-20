//가장 긴 회문 부분 문자열 출력
/*
입력 문자열이 주어졌을 때, 문자열 안에서 가장 긴 회문을 찾아 반환하는 함수
단 같은 길이의 회문이 여러 개일경우 첫 번쨰로 찾은 결과 반환
*/

#include <string>
#include <string_view>
#include <vector>
#include <assert.h>

std::string longest_palindrome(std::string_view str)
{
   size_t const len = str.size();
   size_t longestBegin = 0;
   size_t maxLen = 1;

   std::vector<bool> table(len * len, false);

   for (size_t i = 0; i < len; i++)
   {
      table[i*len + i] = true;
   }

   for (size_t i = 0; i < len - 1; i++)
   {
      if (str[i] == str[i + 1]) 
      {
         table[i*len + i + 1] = true;
         if (maxLen < 2)
         {
            longestBegin = i;
            maxLen = 2;
         }
      }
   }

   for (size_t k = 3; k <= len; k++)
   {
      for (size_t i = 0; i < len - k + 1; i++)
      {
         size_t j = i + k - 1;
         if (str[i] == str[j] && table[(i + 1)*len + j - 1])
         {
            table[i*len +j] = true;
            if (maxLen < k)
            {
               longestBegin = i;
               maxLen = k;
            }
         }
      }
   }

   return std::string(str.substr(longestBegin, maxLen));
}

int main()
{
   using namespace std::string_literals;

   assert(longest_palindrome("sahararahnide") == "hararah");
   assert(longest_palindrome("level") == "level");
   assert(longest_palindrome("s") == "s");
   assert(longest_palindrome("aabbcc") == "aa");
   assert(longest_palindrome("abab") == "aba");
}
