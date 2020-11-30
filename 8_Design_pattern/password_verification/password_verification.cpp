// 패스워드 검증 프로그램 구현
/*
다양한 조합으로 선택할 수 있는 사전 정의 규칙을 기반으로 패스워드의 강도를 검증하는 프로그램 작성
- 모든 비밀번호는 최소 길이에 대한 요구사항을 충족해야 함
- 패스워드는 하나 이상의 기호나 숫자, 대문자, 소문자 등을 포함해야 하는 것처럼 여러 다른 규칙이 적용될 수 있음
*/

#include <string>
#include <string_view>
#include <memory>
#include <assert.h>

class password_validator
{
public:
   virtual bool validate(std::string_view password) = 0;
   virtual ~password_validator() {}
};

class length_validator final : public password_validator
{
public:
   length_validator(unsigned int min_length):
      length(min_length)
   {}
   
   virtual bool validate(std::string_view password) override
   {
      return password.length() >= length;
   }
   
private:
   unsigned int length;
};

class password_validator_decorator : public password_validator
{
public:
   explicit password_validator_decorator(std::unique_ptr<password_validator> validator):
      inner(std::move(validator))
   {
   }
   
   virtual bool validate(std::string_view password) override
   {
      return inner->validate(password);
   }
   
private:
   std::unique_ptr<password_validator> inner;
};

class digit_password_validator final : public password_validator_decorator
{
public:
   explicit digit_password_validator(std::unique_ptr<password_validator> validator):
   password_validator_decorator(std::move(validator))
   {
   }
   
   virtual bool validate(std::string_view password) override
   {
      if(!password_validator_decorator::validate(password))
         return false;
      
      return password.find_first_of("0123456789") != std::string::npos;
   }
};

class case_password_validator final : public password_validator_decorator
{
public:
   explicit case_password_validator(std::unique_ptr<password_validator> validator):
   password_validator_decorator(std::move(validator))
   {
   }
   
   virtual bool validate(std::string_view password) override
   {
      if(!password_validator_decorator::validate(password))
         return false;
      
      bool haslower = false;
      bool hasupper = false;
      
      for(size_t i = 0; i < password.length() && !(hasupper && haslower); ++i)
      {
         if(islower(password[i])) haslower = true;
         else if(isupper(password[i])) hasupper = true;
      }
      
      return haslower && hasupper;
   }
};

class symbol_password_validator final : public password_validator_decorator
{
public:
   explicit symbol_password_validator(std::unique_ptr<password_validator> validator):
   password_validator_decorator(std::move(validator))
   {
   }
   
   virtual bool validate(std::string_view password) override
   {
      if(!password_validator_decorator::validate(password))
         return false;
      
      return password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
   }
};

int main()
{
   {
      auto validator = std::make_unique<length_validator>(8);
   
      assert(validator->validate("abc123!@#"));
      assert(!validator->validate("abc123"));
   }
   
   {
      auto validator = std::make_unique<digit_password_validator>(
                           std::make_unique<length_validator>(8));
      
      assert(validator->validate("abc123!@#"));
      assert(!validator->validate("abcde!@#"));
   }
   
   {
      auto validator = std::make_unique<case_password_validator>(
                           std::make_unique<digit_password_validator>(
                              std::make_unique<length_validator>(8)));
      
      assert(validator->validate("Abc123!@#"));
      assert(!validator->validate("abc123!@#"));
   }
   
   {
      auto validator = std::make_unique<symbol_password_validator>(
                           std::make_unique<case_password_validator>(
                              std::make_unique<digit_password_validator>(
                                 std::make_unique<length_validator>(8))));
      
      assert(validator->validate("Abc123!@#"));
      assert(!validator->validate("Abc123567"));
   }
}