# 3_string and regular expression

## convert binary data to string.cpp
std::array, std::vector, C형식 배열 등의 다양한 종류의 입력 형식을 다룰 수 있는 범용함수를 위해서 템플릿 사용

작성한 코드에서 함수 템플릿의 두 가지 오버로드를 볼 수 있다. 하나는 컨테이너와 문자열의 대/소문자 여부를 결정하기 위한 플래그를 인자로 받음

입력 데이터의 내용은 너비, 채움문자, 대소문자 플래그 등의 I/O manipulator를 적절하게 이용해 std::ostringstream에 사용

## convert a string to a title.cpp
입력 문자열을 수정하지 않고 새로운 문자열을 만들어 내기 위해서 std::stringstream을 사용

모든 문자들을 순회하며 공백이나 구두점이 나올때 마다 새로운 단어를 의미하는 플래그를 True로 주어서 처리

## combining strings divided by parcel characters.cpp
join_strings()라는 함수 템플릿의 두 가지 오버로드를 사용

하나는 구분 문자를 나타내는 포인터를 인자로 받고, 다른 하나는 범위의 처음과 끝을 의미하는 두 랜덤 액세스 반복자와 함께 구분 문자를 인자로 받음

std::ostream_iterator를 사용해 반복자에 값이 할당될 때마다 지정된 출력 스트림에 해당값을 write함

## detach string as token.cpp
문자열 분리함수에 대해서 아래 2가지 유형으로 생각해봤다

1. 하나의 문자를 구획 문자로 사용하여 입력 문자열의 내용으로 초기화된 문자열 스트림을 사용해, std::getline()으로 다음 구획 문자나 개행 문자를 마주질 때까지 영역을 읽어옴

2. std::string으로 가능한 구획 문자의 리스트를 받는것으로 std::string::find_first_of()를 사용해 주어진 위치에서부터 처음으로 등장하는 구획 문자의 위치를 찾고, 이를 반복하여 추출한 부분 문자열은 vector에 추가시킴

## longest enumeration partial string.cpp
브루트 포스 접근법을 이용해 각각의 부분 문자열이 회문인지 확인하는 형태

## vehicle license plate verification.cpp
아래의 정규표현식을 사용함

"[A-Z]{3}-[A-Z]{2} \d{3,4}"