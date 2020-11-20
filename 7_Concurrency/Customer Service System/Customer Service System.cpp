//고객 서비스 시스템 구현
/*
고객 서비스가 이루어지는 사무실을 시뮬레이션하는 프로그램을 작성

- 사무실에는 세 개의 데스크가 있어 동시에 여려 명의 고객을 응대할 수 있다
- 고객은 사무실에 언제든지 들어올 수 있다
- 고객은 발권기에서 대기 번호표를 발급하고 데스크 중 한 곳이 자신의 순서를 부를 때까지 기다린다
- 고객은 사무실에 들어온 순서대로, 좀더 정확하게는 번호표를 뽑은 순서대로 서비스를 받게 된다
- 서비스 데스크에서는 한 고객의 서비스가 끝날 땜마다 순서대로 다음 고객을 응대한다
- 시뮬레이션은 특정한 수의 고객이 번호표를 발급하고 서비스를 받을 때까지 지속된다
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <string_view>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <array>

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

class ticketing_machine
{
public:
   ticketing_machine(int const start) : last_ticket(start), first_ticket(start) {}

   int next() { return last_ticket++; }
   int last() const { return last_ticket - 1; }
   void reset() { last_ticket = first_ticket; }
private:
   int first_ticket;
   int last_ticket;
};

class customer
{
public:
   customer(int const no) : number(no)
   {}

   int ticket_number() const noexcept { return number; }

private:
   int number;

   friend bool operator<(customer const & l, customer const & r);
};

bool operator<(customer const & l, customer const & r)
{
   return l.number > r.number;
}

int main()
{
   std::priority_queue<customer> customers;
   bool store_open = true;
   std::mutex mt;
   std::condition_variable cv;
   
   std::vector<std::thread> desks;
   for (int i = 1; i <= 3; ++i)
   {
      desks.emplace_back([i, &store_open, &mt, &cv, &customers]() {
         std::random_device rd;
         auto seed_data = std::array<int, std::mt19937::state_size> {};
         std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
         std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
         std::mt19937 eng(seq);
         std::uniform_int_distribution<> ud(2000, 3000);
         
         logger::instance().log("desk " + std::to_string(i) + " open");
         
         while (store_open || !customers.empty())
         {
            std::unique_lock<std::mutex> locker(mt);
            
            cv.wait_for(locker, std::chrono::seconds(1),
                        [&customers]() {return !customers.empty(); });
            
            if (!customers.empty())
            {
               auto const c = customers.top();
               customers.pop();
               
               logger::instance().log("[-] desk " + std::to_string(i) + " handling customer " + std::to_string(c.ticket_number()));
               
               logger::instance().log("[=] queue size: " + std::to_string(customers.size()));
               
               locker.unlock();
               cv.notify_one();
               
               std::this_thread::sleep_for(std::chrono::milliseconds(ud(eng)));
               
               logger::instance().log("[ ] desk " + std::to_string(i) + " done with customer " + std::to_string(c.ticket_number()));
            }
         }
         
         logger::instance().log("desk " + std::to_string(i) + " closed");
      });
   }
   
   std::thread store([&store_open, &customers, &mt, &cv]() {
      ticketing_machine tm(100);
      std::random_device rd;
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      std::mt19937 eng(seq);
      std::uniform_int_distribution<> ud(200, 500);
      
      for (int i = 1; i <= 25; ++i)
      {
         customer c(tm.next());
         customers.push(c);
         
         logger::instance().log("[+] new customer with ticket " + std::to_string(c.ticket_number()));
         logger::instance().log("[=] queue size: " + std::to_string(customers.size()));
         
         cv.notify_one();
         
         std::this_thread::sleep_for(std::chrono::milliseconds(ud(eng)));
      }
      
      store_open = false;
   });
   
   store.join();
   
   for (auto & desk : desks) desk.join();
}