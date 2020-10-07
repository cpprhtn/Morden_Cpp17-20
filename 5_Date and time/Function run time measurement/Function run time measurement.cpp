//함수 실행 시간 측정
/*
임의의 수의 전달 인자를 가진 어떤 함수의 실행 시간을 측정하는 함수를 작성
*/

#include <iostream>
#include <chrono>
#include <thread>

template <typename Time = std::chrono::microseconds,
   typename Clock = std::chrono::high_resolution_clock>
   struct perf_timer
{
   template <typename F, typename... Args>
   static Time duration(F&& f, Args... args)
   {
      auto start = Clock::now();

      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
   }
};

using namespace std::chrono_literals;

void f()
{
   // simulate work
   std::this_thread::sleep_for(2s);
}

void g(int const a, int const b)
{
   // simulate work
   std::this_thread::sleep_for(1s);
}

int main()
{
   auto t1 = perf_timer<std::chrono::microseconds>::duration(f);
   auto t2 = perf_timer<std::chrono::milliseconds>::duration(g, 1, 2);

   auto total = std::chrono::duration<double, std::nano>(t1 + t2).count();

   std::cout << total << std::endl;
}
