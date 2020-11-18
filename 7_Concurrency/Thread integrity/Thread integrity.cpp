// 스레드 안전하게 콘솔에 로그 메시지를 출력하는 함수
/*
표준 출력 스트림에 대한 접근을 동기화해 출력 무결성을 보장함으로써 
여러 스레드에서 도착하는 컴포넌트가 안전하게 콘솔에 로그 메시지를 출력할 수 있게 하는 클래스 작성

- 이 로깅 컴포넌트는 콘솔에 출력될 메시지 문자열을 전달 인자로 받는 log()라는 이름의 메소드를 가져야 함
*/


#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <string_view>
#include <mutex>
#include <string>

class logger
{
protected:
   logger() {}
public:
   static logger& instance()
   {
      static logger lg;
      return lg;
   }
   
   logger(logger const &) = delete;
   logger& operator=(logger const &) = delete;
   
   void log(std::string_view message)
   {
      std::lock_guard<std::mutex> lock(mt);
      std::cout << "LOG: " << message << std::endl;
   }
   
private:
   std::mutex mt;
};

int main()
{
   std::vector<std::thread> modules;
   
   for(int id = 1; id <= 5; ++id)
   {
      modules.emplace_back([id](){
         std::random_device rd;
         std::mt19937 mt(rd());
         std::uniform_int_distribution<> ud(100, 1000);
         
         logger::instance().log("module " + std::to_string(id) + " started");
         
         std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));
         
         logger::instance().log("module " + std::to_string(id) + " finished");
      });
   }
   
   for(auto & m : modules) m.join();
}
