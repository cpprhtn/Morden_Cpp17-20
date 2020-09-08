//과잉수는 진약수들의 합이 수 자신보다 작은 수를 말함
//12의 진약수는 1,2,3,4,6
//이 수의 합은 16이므로 과잉수가 되며, 과잉은 16-12를 한 4가 됨

#include <iostream>
#include <cmath>

int sum_proper_divisors(int const number)
{
   int result = 1;
   for (int i = 2; i <= std::sqrt(number); i++)
   {
      if (number%i == 0)
      {
         result += (i == (number / i)) ? i : (i + number / i);
      }
   }

   return result;
}

void print_abundant(int const limit)
{
   for (int number = 10; number <= limit; ++number)
   {
      auto sum = sum_proper_divisors(number);
      if (sum > number)
      {
         std::cout
            << number
            << ", abundance=" << sum - number << std::endl;
      }
   }
}

int main()
{
   int limit = 0;
   std::cout << "Upper limit: ";
   std::cin >> limit;

   print_abundant(limit);
}
