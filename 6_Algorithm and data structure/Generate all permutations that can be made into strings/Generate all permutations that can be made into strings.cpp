//문자열로 만들 수 있는 모든 순열 생성
/*
콘솔에 주어진 문자열로 만들 수 잏ㅆ는 모든 순열을 출력하는 함수 작성
재귀를 사용한 버전과 그렇지 않은 버전 2가지를 작성 해야함
*/

#include <iostream>
#include <string>
#include <algorithm>

void print_permutations(std::string str)
{
   std::sort(std::begin(str), std::end(str));

   do
   {
      std::cout << str << std::endl;
   } while (std::next_permutation(std::begin(str), std::end(str)));
}

void next_permutation(std::string str, std::string perm)
{
   if (str.empty()) std::cout << perm << std::endl;
   else
   {
      for (size_t i = 0; i < str.size(); ++i)
      {
         next_permutation(str.substr(1), perm + str[0]);

         std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
      }
   }
}

void print_permutations_recursive(std::string str)
{
   next_permutation(str, "");
}

int main()
{
   std::cout << "non-recursive version" << std::endl;
   print_permutations("main");

   std::cout << std::endl;
   
   std::cout << "recursive version" << std::endl;
   print_permutations_recursive("main");
}
