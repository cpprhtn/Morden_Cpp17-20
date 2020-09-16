# 3_string and regular expression

## convert binary data to string.cpp
std::array, std::vector, C형식 배열 등의 다양한 종류의 입력 형식을 다룰 수 있는 범용함수를 위해서 템플릿 사용

작성한 코드에서 함수 템플릿의 두 가지 오버로드를 볼 수 있다. 하나는 컨테이너와 문자열의 대/소문자 여부를 결정하기 위한 플래그를 인자로 받음

입력 데이터의 내용은 너비, 채움문자, 대소문자 플래그 등의 I/O manipulator를 적절하게 이용해 std::ostringstream에 사용