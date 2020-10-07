//임시 로그 파일
/*
임시 디렉토리에 텍스트 파일을 만들고, 쓰기 용도로 여는 생성자가 있어야 함
객체가 소멸할 때 파일이 있다면 이를 닫고 삭제해야 함
파일을 닫고 영구적인 경로로 이동하는 메소드를 가져야 함
<< 연산자를 오버로드해 출력 파일에 텍스트 메시지를 쓸 수 있어야 함
*/

#include <iostream>
#include <fstream>

#include "uuid.h"

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

class logger
{
   fs::path       logpath;
   std::ofstream  logfile;
public:
   logger()
   {
      auto name = uuids::to_string(uuids::uuid_random_generator{}());
      logpath = fs::temp_directory_path() / (name + ".tmp");
      logfile.open(logpath.c_str(), std::ios::out|std::ios::trunc);
   }

   ~logger() noexcept
   {
      try {
         if(logfile.is_open())
            logfile.close();
         if (!logpath.empty())
            fs::remove(logpath);
      }
      catch (...) {
      }
   }

   void persist(fs::path const & path)
   {
      logfile.close();
      fs::rename(logpath, path);
      logpath.clear();
   }

   logger& operator<<(std::string_view message)
   {
      logfile << message.data() << '\n';
      return *this;
   }
};

int main()
{
   logger log;
   try
   {
      log << "this is a line" << "and this is another one";

      throw std::runtime_error("error");
   }
   catch (...)
   {
      log.persist(R"(lastlog.txt)");
   }
}
