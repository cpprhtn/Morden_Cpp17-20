//문자열을 바이너리 데이터로 변환
/*
입력 인자로 16진수 문자열이 주어질 때, 문자열을 deserialization(역직렬화)하고 8비트 정수들의 벡터를 반환하는 함수
*/

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <array>
#include <assert.h>

unsigned char hexchar_to_int(char const ch)
{
   if (ch >= '0' && ch <= '9') return ch - '0';
   if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
   if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
   throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<unsigned char> hexstr_to_bytes(std::string_view str)
{
   std::vector<unsigned char> result;

   for (size_t i = 0; i < str.size(); i += 2) 
   {
      result.push_back(
         (hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i+1]));
   }

   return result;
}

int main()
{
   std::vector<unsigned char> expected{ 0xBA, 0xAD, 0xF0, 0x0D, 0x42 };
   assert(hexstr_to_bytes("BAADF00D42") == expected);
   assert(hexstr_to_bytes("BaaDf00d42") == expected);
}
