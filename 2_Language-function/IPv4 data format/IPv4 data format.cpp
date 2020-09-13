//IPv4 데이터 형식 표현하는 함수
/* 
IPv4 주소를 표현하는 클래스 생성
   - 콘솔을 통해 주소를 읽고 쓰는 기능을 하는 함수
   - 사용자는 123.0.0.1 처럼 점으로 구분된 IPv4 주소 입력가능
   - 출력결과도 같은형식
*/

#include <iostream>
#include <array>
#include <sstream>
#include <assert.h>

/*해결방안
ipv4주소는 32비트 값이고, 주로 점으로 구분되어있음
각각의 부분은 0~255까지의 범위를 가짐
각부분을 쉽게 다루기 위해 unsigned char 변수 4개를 사용
*/
class ipv4
{
   std::array<unsigned char, 4> data;
public:
   constexpr ipv4() :data{ {0} } {}
   constexpr ipv4(unsigned char const a, unsigned char const b, 
                  unsigned char const c, unsigned char const d):
      data{{a,b,c,d}} {}
   explicit constexpr ipv4(unsigned long a) :
      data{ { static_cast<unsigned char>((a >> 24) & 0xFF), 
              static_cast<unsigned char>((a >> 16) & 0xFF),
              static_cast<unsigned char>((a >> 8) & 0xFF),
              static_cast<unsigned char>(a & 0xFF) } } {}
   ipv4(ipv4 const & other) noexcept : data(other.data) {}
   ipv4& operator=(ipv4 const & other) noexcept 
   {
      data = other.data;
      return *this;
   }

   std::string to_string() const
   {
      std::stringstream sstr;
      sstr << *this;
      return sstr.str();
   } 

   constexpr unsigned long to_ulong() const noexcept
   {
      return
         (static_cast<unsigned long>(data[0]) << 24) |
         (static_cast<unsigned long>(data[1]) << 16) |
         (static_cast<unsigned long>(data[2]) << 8) |
         static_cast<unsigned long>(data[3]);
   }

   friend std::ostream& operator<<(std::ostream& os, const ipv4& a)
   {
      os << static_cast<int>(a.data[0]) << '.' 
         << static_cast<int>(a.data[1]) << '.'
         << static_cast<int>(a.data[2]) << '.'
         << static_cast<int>(a.data[3]);
      return os;
   }

   friend std::istream& operator>>(std::istream& is, ipv4& a)
   {
      char d1, d2, d3;
      int b1, b2, b3, b4;
      is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
      if (d1 == '.' && d2 == '.' && d3 == '.')
         a = ipv4(b1, b2, b3, b4);
      else
         is.setstate(std::ios_base::failbit);

      return is;
   }
};

int main()
{
   ipv4 a(168, 192, 0, 1);
   std::cout << a << std::endl;
   std::cout << a.to_string() << std::endl;

   ipv4 b = a;
   ipv4 c;
   c = b;

   ipv4 ip;
   std::cout << ip << std::endl;
   std::cin >> ip;
   if(!std::cin.fail())
      std::cout << ip << std::endl;
}
