//사용자 자격을 증명하는 인증 프로그램 구현
/*
보호된 시스템에 사용자가 접속하고 인증하는 과정을 시뮬레이션하는 프로그램을 작성
- 미리 등록된 사용자만 시스템에 로그인 가능
- 프로그램은 먼저 사용자가 입력한 사용자 이름과 패스워드가 등록된 사용자 중 하나와 일치하는지 확인
    - 이 과정이 성공한다면 사용자에게 접근 권한을 부여
    - 이외의 경우는 실패
- 보안상의 이유로 이 프로그램은 패스워드를 직접 저장하는 대신 SHA 해시를 사용

* 암호화 관련 기능뿐 아니라 다양한 기능들을 제공하는 Crypto++ 라이브러리를 다운받아 사용
*/

#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>
#include <vector>

#include "sha.h"
#include "hex.h"

struct user
{
   int id;
   std::string username;
   std::string password;
   std::string firstname;
   std::string lastname;
};

std::string get_hash(std::string_view password)
{
   CryptoPP::SHA512 sha;
   CryptoPP::byte digest[CryptoPP::SHA512::DIGESTSIZE];

   sha.CalculateDigest(
      digest,
      reinterpret_cast<CryptoPP::byte const*>(password.data()),
      password.length());

   CryptoPP::HexEncoder encoder;
   std::string result;

   encoder.Attach(new CryptoPP::StringSink(result));
   encoder.Put(digest, sizeof(digest));
   encoder.MessageEnd();

   return result;
}

int main()
{
   std::vector<user> users
   {
      {
         101, "scarface",
         "07A8D53ADAB635ADDF39BAEACFB799FD7C5BFDEE365F3AA721B7E25B54A4E87D419ADDEA34BC3073BAC472DCF4657E50C0F6781DDD8FE883653D10F7930E78FF",
         "Tony", "Montana"
      },
      {
         202, "neo",
         "C2CC277BCC10888ECEE90F0F09EE9666199C2699922EFB41EA7E88067B2C075F3DD3FBF3CFE9D0EC6173668DD83C111342F91E941A2CADC46A3A814848AA9B05",
         "Thomas", "Anderson"
      },
      {
         303, "godfather",
         "0EA7A0306FE00CD22DF1B835796EC32ACC702208E0B052B15F9393BCCF5EE9ECD8BAAF27840D4D3E6BCC3BB3B009259F6F73CC77480C065DDE67CD9BEA14AA4D",
         "Vito", "Corleone"
      }
   };

   std::string username, password;
   std::cout << "Username: ";
   std::cin >> username;

   std::cout << "Password: ";
   std::cin >> password;

   auto hash = get_hash(password);

   auto pos = std::find_if(
      std::begin(users), std::end(users),
      [username, hash](user const & u) {
      return u.username == username &&
         u.password == hash; });

   if (pos != std::end(users))
      std::cout << "Login successful!" << std::endl;
   else
      std::cout << "Invalid username or password" << std::endl;
}
