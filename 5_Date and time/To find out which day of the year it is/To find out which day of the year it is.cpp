//한 해의 몇 번째 날인지 찾기
/*
어떤 날짜가 주어졌을 때, 날짜가 그 해의 몇 번째 날인지 찾아, 반환하는 함수와 주어진 날짜가 그 해의 몇 번째 주에 속하는지 찾는 함수를 각각 작성
*/

#include <iostream>
#include "date.h"
#include "iso_week.h"

unsigned int calendar_week(int const y, unsigned int const m, unsigned int const d)
{
   using namespace date;
   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return (unsigned int)tiso.weeknum();
}

int day_of_year(int const y, unsigned int const m, unsigned int const d)
{
   using namespace date;
   
   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   return (sys_days{ year{ y } / month{ m } / day{ d } } -
      sys_days{ year{ y } / jan / 0 }).count();
}

int main()
{
   int y = 0;
   unsigned int m = 0, d = 0;
   std::cout << "Year:"; std::cin >> y;
   std::cout << "Month:"; std::cin >> m;
   std::cout << "Day:"; std::cin >> d;

   std::cout << "Calendar week:" << calendar_week(y, m, d) << std::endl;
   std::cout << "Day of year:" << day_of_year(y, m, d) << std::endl;
}
