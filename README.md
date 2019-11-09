# Mean-Filter

### 주제
```
Mean Filtering을 수행하는 myFastestMeanFilter 함수를 구현하고 다음 입출력 조건을 만족하는 프로그램을 구현하여라
(myFastMeanFilter 함수를 main에서 호출하여 결과가 나올 수 있도록 할 것)
```

### 구현할 함수의 원형
```
void myFastestMeanFilter(IplImage * src, IplImage * dst, int k)
(k: 네이버의 범위를 정의하는 숫자. 즉, 커널의 한 변의 크기는 (2k+1)이 된다.)
예) k=1 일 경우 커널의 사이즈는 3x3이 됨
```

### 함수조건
```
- cvSmooth함수를 사용하지 말 것
- 커널의 크기에 상관없이 일정한 속도로 수행 될 수 있게 할 것
```

### 프로그램 입출력 조건
```
입력 그림의 file_path를 입력 받고, 또한 k를 입력 받으면 필터링 된 이미지가 출력
```

### 버그 및 기능 요청

**양재연**

- [**@reyeon1209**](https://github.com/reyeon1209)   
- <reyeon5368@naver.com>
