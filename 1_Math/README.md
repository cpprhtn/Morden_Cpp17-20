# 1_Math

## GCD.cpp, LCM.cpp
C++17에서는 <numeric> 헤더에서 최대공약수를 계산하는 gcd(), 최소공배수를 계산하는 lcm() 이라는 constexpr 함수를 제공한다

## LCM.cpp
int v{0}; 과 같은 구문의 초기화 기법은 유니폼 초기화(uniform initialization)라고 하는데,

원래 초기화 리스트(initializer list)를 통해 객체를 초기화하는 방법을 의미하지만 C++11부터는 이런 초기화 기법이 내장 자료형 (built-in type)을 포함한 모든 자료형으로 확장되었다
