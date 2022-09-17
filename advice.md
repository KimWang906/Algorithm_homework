# advice

```C++
/*
    Q.  지금 학교 과제로 재귀함수를 사용해서 프로그램을 만들어보라는 과제가 나와서 C++로 사용자가 원하는 디렉터리를 암호화 해주는 프로그램을 만들어 보고 있는데
        file >> std::noskipws >> byte가 조건인 것 같은데 정확히 어떤 조건인지 잘 파악이 안되서 혹시 아시는 분 계시나요?

    >> 연산자는 티르님이 잘 설명해 주셨구요, readInByte를 반복문에서 재귀로 바꾸는건 매우 이상한 것 같습니다
    일반적으로 재귀는 벡터보다는 트리에 적합합니다
    디렉토리라고 하면 서브디렉토리로 재귀하는게 자연스러울 것 같아요

    재귀를 하면 뭐가 좋은가 생각을 해봐야 하는데, 재귀를 하면 스택에 암시적으로 상태가 저장되는 거거든요
    그래서 트리 왼쪽 갔다가 다시 오른쪽 갈때 상태를 복구할 필요가 있으니까 적합한데
    바이트를 순서대로 읽는건 한 방향으로만 가니까 복구할 상태가 없어요

    복구할 상태가 없는 경우 반복과 동일하기 때문에 자동으로 그렇게 바꾸어 줄 수 있는데요 ("꼬리 재귀")
    C++은 꼬리 재귀를 지원 안하기 때문에 C++에서 그렇게 짜는건 부적합합니다
    - sanxiyn

    네 그리고 C++를 포함해서 대부분의 언어는 재귀를 몇천 번 이상씩 도는 걸 잘 가정하지 않고요
    그래서 파일을 바이트 단위로 읽는 코드 같은 걸 재귀로 짜면 몇십 킬로바이트만 넘겨도 실행 중에 stack overflow로 터지는 프로그램이 됩니다
    - Kroisse

    Q. 그럼 말하신대로 서브 디렉터리로 재귀문을 돌리면 괜찮을까요?

    네 그건 괜찮아 보여요
    - Synxiyn

    보통 디렉토리 깊이가 (갯수 말고) 몇천 개씩 들어가는 일은 거의 없으니까 괜찮습니다
    디렉토리 깊이가 몇천 개씩 들어가면 이제 깊이 말고 다른 게 문제가 될 거니까 역시 괜찮습니다
    - Kroisse
*/
```