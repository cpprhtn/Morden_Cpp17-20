//선택 알고리즘 함수
/*
어떤 값들의 범위와 투영 함수가 주어졌을 때, 각 값들을 새로운 형태로 변환하고 선택한 부분만을 반환하는 함수 작성
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <
   typename T, typename A, typename F,
   typename R = typename std::decay<typename std::result_of<typename std::decay<F>::type&(typename std::vector<T, A>::const_reference)>::type>::type>
   std::vector<R> select(std::vector<T, A> const & c, F&& f)
{
   std::vector<R> v;
   std::transform(
      std::cbegin(c), std::cend(c),
      std::back_inserter(v),
      std::forward<F>(f));

   return v;
}

struct book
{
   int id;
   std::string title;
   std::string author;
};

int main()
{
   std::vector<book> books{
      {101, "The C++ Programming Language", "Bjarne Stroustrup"},
      {203, "Effective Modern C++", "Scott Meyers"},
      {404, "The Modern C++ Programming Cookbook", "Marius Bancila"}};

   auto titles = select(books, [](book const & b) {return b.title; });

   for (auto const & title : titles)
   {
      std::cout << title << std::endl;
   }
}
