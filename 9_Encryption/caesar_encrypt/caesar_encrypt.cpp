//카이사르 암호법을 적용한 프로그램 구현
/*
임의의 이동 값을 지정해 오른쪽으로 회전하는 카이사르 암호법을 사용해 메시지를 암호화하고 복호화하는 프로그램 작성
- 단순화를 위해 알파벳 대문자로 이뤄진 메시지만을 고려하며 숫자나 기호, 다른 유형의 문자들은 무시함
*/

#include <iostream>
#include <string>
#include <string_view>
#include <assert.h>

std::string caesar_encrypt(std::string_view text, int const shift)
{
    std::string str;
    str.reserve(text.length());
    for (auto const c : text)
    {
        if (isalpha(c) && isupper(c))
            str += 'A' + (c - 'A' + shift) %26;
        
        else
            str += c;
    }

    return str;
}


std::string caesar_decrypt(std::string_view text, int const shift)
{
    std::string str;
    str.reserve(text.length());
    for (auto const c : text)
    {
        if (isalpha(c) && isupper(c))
            str += 'A' + (26 + c - 'A' - shift) % 26;

        else 
            str += c;
    }

    return str;
}


int main()
{
    auto text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 1; i <= 26; ++i)
    {
        auto enc = caesar_encrypt(text, i);
        auto dec = caesar_decrypt(enc, i);
        assert(text == dec);
    }
}