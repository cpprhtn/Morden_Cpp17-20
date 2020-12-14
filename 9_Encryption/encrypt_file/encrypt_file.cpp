//파일 암호화 및 복호화 프로그램 구현
/*
고급 암호화 표준을 이용해 파일을 암호화하고 복호화하는 프로그램을 작성
- 패스워드와 함께 원본 파일과 결과 파일 경로를 지정할 수 있어야 함
*/

#include <iostream>
#include <string>
#include <string_view>

#include "sha.h"
#include "hex.h"
#include "files.h"
#include "default.h"

#ifdef USE_BOOST_FILESYSTEM
#  include <boost/filesystem/path.hpp>
#  include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#else
#  include <filesystem>
#  ifdef FILESYSTEM_EXPERIMENTAL
namespace fs = std::experimental::filesystem;
#  else
namespace fs = std::filesystem;
#  endif
#endif

void encrypt_file(
   fs::path const & sourcefile,
   fs::path const & destfile,
   std::string_view password)
{
   CryptoPP::FileSource source(
      sourcefile.c_str(),
      true,
      new CryptoPP::DefaultEncryptorWithMAC(
      (CryptoPP::byte*)password.data(), password.size(),
         new CryptoPP::FileSink(
            destfile.c_str())
      )
   );
}

void encrypt_file(
   fs::path const & filepath,
   std::string_view password)
{
   auto temppath = fs::temp_directory_path() / filepath.filename();

   encrypt_file(filepath, temppath, password);

   fs::remove(filepath);
   fs::rename(temppath, filepath);
}

void decrypt_file(
   fs::path const & sourcefile,
   fs::path const & destfile,
   std::string_view password)
{
   CryptoPP::FileSource source(
      sourcefile.c_str(),
      true,
      new CryptoPP::DefaultDecryptorWithMAC(
      (CryptoPP::byte*)password.data(), password.size(),
         new CryptoPP::FileSink(
            destfile.c_str())
      )
   );
}

void decrypt_file(
   fs::path const & filepath,
   std::string_view password)
{
   auto temppath = fs::temp_directory_path() / filepath.filename();

   decrypt_file(filepath, temppath, password);

   fs::remove(filepath);
   fs::rename(temppath, filepath);
}

int main()
{
   encrypt_file("sample.txt", "sample.txt.enc", "cppchallenger");
   decrypt_file("sample.txt.enc", "sample.txt.dec", "cppchallenger");

   encrypt_file("sample.txt", "cppchallenger");
   decrypt_file("sample.txt", "cppchallenger");
}
