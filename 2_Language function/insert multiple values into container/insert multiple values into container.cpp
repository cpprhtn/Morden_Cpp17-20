//컨테이너에 여러 값 삽입
//push_back(T&& value) 메소드를 갖는 임의의 컨테이너 끝 부분에 여러 개의 원소를 삽입하는 범용 함수를 작성

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <list>

template<typename C, typename... Args>
void push_back(C& c, Args&&... args)
{
   (c.push_back(args), ...);
}

int main()
{
   std::vector<int> v;
   push_back(v, 1, 2, 3, 4);
   std::copy(std::begin(v), std::end(v), 
             std::ostream_iterator<int>(std::cout, " "));

   std::list<int> l;
   push_back(l, 1, 2, 3, 4);   
   std::copy(std::begin(l), std::end(l), 
             std::ostream_iterator<int>(std::cout, " "));
}
