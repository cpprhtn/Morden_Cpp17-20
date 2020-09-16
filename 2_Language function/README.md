# 2_Language function

## calc 2D array.cpp
고정된 길이나 가변 길이를 지원하는 표준 컨테이너가 존재한다

이 2차원 배열 클래스는 이러한 컨테이너들의 어댑터 역할을 할것이다

std::array와 std::vector중 무엇을 사용할 것인지 결정하기 위해 아래 두가지 사항을 고려해야 한다

- 이 array2d 클래스는 이 타입의 객체를 이동 가능하도록 만드는 이동 의미론을 지원해야 한다
- list initialization을 지원해야 한다

std::array 컨테이너는 오직 담고 있는 원소가 이동 생성 가능하며 이동 할당 가능할 때만 이동할 수 있다

또한 std::initializer_list를 통해 생성될 수 없다

따라서  std::vector 사용

## minimum function.cpp
가변 인자 함수 템플릿(variadic function template)을 사용해 여러 개의 전달 인자를 받는 함수 템플릿 작성가능

이를 위해서 컴파일 시간 재귀를 구현

## insert multiple values into container.cpp
가변 인자 함수 템플릿(variadic function template)을 사용해 여러 개의 전달 인자를 받는 함수 템플릿 작성가능

함수는 컨테이너를 첫 번째 매개변수로 받아야 하며, 컨테이너의 뒤에 삽입할 값을 의미하는 불특정한 수의 인자가 따라와야 함

폴드 표현식을 통해 이러한 함수 템플릿을 아주 간단하게 작성

## ckeck multiple values into container.cpp

주어진 각 조건이 맞는지를 bool 값을 통해 반환하는 헬퍼 함수 사용

폴드 표현식을 사용

## system handle wrapper.cpp

<windows.h> 헤더파일은 맥 os에서 작동이 불가

아래의 기능구현으로 만족하는걸로..

- 핸들의 명시적인 휙득 및 객체가 파괴될 때의 자동 해제
- 이동 의미론을 통한 핸들 소유권 전달
- 비교 연산자를 통해 두 객체가 같은 핸들을 참도하는지 확인
- 교환이나 리셋과 같은 추가적인 연산

## temperature unit literal.cpp

섭씨, 화씨, 캘빈단위에 대한 연산과 변환기능 구현