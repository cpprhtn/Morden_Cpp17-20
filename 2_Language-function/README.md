# 2_Language-function

## calc 2D array.cpp
고정된 길이나 가변 길이를 지원하는 표준 컨테이너가 존재한다

이 2차원 배열 클래스는 이러한 컨테이너들의 어댑터 역할을 할것이다

std::array와 std::vector중 무엇을 사용할 것인지 결정하기 위해 아래 두가지 사항을 고려해야 한다

- 이 array2d 클래스는 이 타입의 객체를 이동 가능하도록 만드는 이동 의미론을 지원해야 한다
- list initialization을 지원해야 한다

std::array 컨테이너는 오직 담고 있는 원소가 이동 생성 가능하며 이동 할당 가능할 때만 이동할 수 있다

또한 std::initializer_list를 통해 생성될 수 없다

따라서  std::vector이 주어진 사항을 만족하는 선택지 이다

