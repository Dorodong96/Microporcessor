# 마이크로프로세서 Microprocessor



## Chap0. Outline of Microprocessor

 **마이크로프로세서**란, 컴퓨터의 산술논리연산기(ALU), 레지스터, 프로그램 카운터(PC), 명령디코더, 제어회로 등의 연산장치와 제어장치를 1개의 작은 실리콘 칩에 모아놓은 처리장치이다. 여기서 프로세서는 데이터 연산을 목적으로 하는 기기를 말하며, 컴퓨터에서는 이러한 기능을 위해 중앙 처리 장치인 CPU(Central Processing Unit)가 존재한다.

### 1. Interface

 마이크로프로세서 과목에서는 마이크로프로세서의 사용법을 학습한다. 이는 마이크로프로세서의 **인터페이스** 사용법을 익히는 것을 말한다. 인터페이스란, **어떤 두 시스템의 경계에서 서로 통신 및 접속이 가능하도록 하는 매개체**를 의미한다.

 이러한 인터페이스 중 운영체제와 응용프로그램 사이의 통신에 사용되는 개념이 **API (Application Programming Interface)**이다. API를 통해 사용자는 상세 기능이 **추상화**된 상태에서 내부 구조를 알 필요 없이 필요한 부분만을 사용할 수 있게 된다. 

### 2. ISA (Instruction Set Architecture)

마이크로프로세서의 인터페이스는 명령어 집합 **ISA (Instruction Set Architecture)**에 의해 구현된다. ISA는 인간이 사용하는 언어에 비교하여 생각해 볼 수 있는데, 그 관계는 아래와 같다.

![image](https://user-images.githubusercontent.com/45297745/95107023-4dee5d80-0774-11eb-9657-499bc6047dda.png)

 말하자면, 명령어 집합인 **Instruction Set에 Instruction을 사용하기 위한 정해진 문법을 더한 것**을 일컬어 ISA라고 한다. 프로그램은 이러한 명령어의 조합으로 구성된다. 이러한 ISA가 마이크로 프로세서의 인터페이스로 사용되며, 이는 제조사마다 다르기 때문에 서로 호환되지 않는다. 

### 3. RISC-V

 앞서 말했듯 ISA는 제조사마다 그 형식이 다르다. 대표적으로 PC에 가장 많이 사용되는 Intel x86 Architecture의 경우, 오랜 역사에 따라 그 명령어가 8-bit부터 64-bit까지 매우 다양하다. 비교적 최근에 많이 사용되는 ARM기반의 Architecture는 그 구조가 x86에 비해 간단하여 사용이 편하게 여겨졌지만, 이마저도 그 명령어가 점차 늘어가고 있다. 이처럼 세대를 거듭할수록 이전의 명령어를 포함하면서 사용할 수 있는 ISA를 **증분형 ISA라**고 한다. 그에 비해 새로 등장한 ISA개념이 있는데, 그것이 바로 이번 수업에서 사용할 **모듈형 ISA** RISC-V이다.

* **증분형 ISA (Incremental ISA)**
    * 이전 세대의 명령어를 포함하여 구성된다
    * 세대를 거듭할수록 명령어가 증가하여 복잡해진다
    * ex) Intel Pentium, ARM, ...
* **모듈형 ISA (Modular ISA)**
    * 사용하고자 하는 명령어만 필요에 의해 추가/삭제하여 사용할 수 있다
    * ex) RISC-V

 본 수업에서는 RISC-V를 통해 **ISS (Instruction Set Simulator)**를 구현하여 명령어를 따서 실행 후, 실행 결과를 보여주는 프로그램을 제작한다. 이를 통해 CPU의 작동 원리 및 어셈블리어를 학습하고, 나아가 ARM 프로세서를 다루어 보는 방향으로 나아갈 것이다.



## Chap1. Computer Abstractions & Technology

이 장에서는 기본적인 컴퓨터에 대한 지식과 구조, 특징 및 개념에 대해 알아보도록 한다. 

### 1. Classes of Computers

현대에 들어 많은 종류의 컴퓨터들이 있지만, 대표적으로 다음과 같은 종류의 컴퓨터들이 많이 사용되고 있다.

* **Personal Computers**
    * 일반적인 목적으로 사용되며, 다양한 소프트웨어가 존재한다
    * 비용 대비 성능에 가장 영향을 많이 받는다
* **Server Computers** 
    * 네트워크 기반이다
    * 고용량, 고성능, 고안정성이 요구된다
    * 작은 사이즈부터 빌딩크기의 사이즈까지 다양하다
* **Supercomputers**
    * 과학 및 공학 연산에 특화된 컴퓨터이다
    * 다양한 기능이 있지만, 전체 컴퓨터 시장에서는 매우 적은 부분을 차지한다
* **Embedded Computers**
    * 보통 아주 작은 사이즈로, 시스템의 구성요소로 숨겨져 있다
    * 저전력, 고성능, 저비용 등의 요소가 고려된다
    * MCU (Micro Controller Unit) : 자동차, 가전에 들어가는 제어기
    * AP (Application Processor) : 스마트폰, 태블릿에 사용되는 고성능 임베디드 시스템	

### 2. Understanding Performance

컴퓨터, 혹은 어떤 프로그램의 속도를 향상시키는 데에는 다음과 같은 방법들이 있다.

* **알고리즘 (Algorithm)**
    * 실행되는 명령어  수를 결정한다.
* **프로그래밍언어, 컴파일러, 아키텍쳐** **(Programming language, Compiler, architecture)**
    * 명령어 수행 당 필요한 기계어 명령의 수를 결정한다.
* **프로세서, 메모리 시스템 (Processor, Memory System)**
    * 명령어 처리 속도를 결정한다.
* **입출력 시스템 (I/O System (including OS))**
    * I/O 동작이 얼마나 빠르게 수행되는지 결정

### 3. Program Architecture

프로그램의 구조는 다음과 같이 구성된다. 

* **Application software**
    * HLL(High-Level Language)로 작성된다
* **System software**
    * Compiler : HLL을 기계어로 변환시켜 주는 역할을 한다.
    * Operating System : HW를 직접 이용한다
        * Input / Output 관리
        * memory, storage 관리
        * task scheduling, resource sharing
* **Hardware**
    * 프로세서, 메모리, 입출력 제어기

### 4. Levels of Program Code

프로그램을 구성하는 코드는 여러 단계를 거치도록 설계되어 왔다. 인간이 이해하기 쉬운 HLL부터, 컴퓨터가 직접 처리하는 기계어에 이르기까지 다양한 과정을 통해 사용된다. 아래의 그림을 통해 그 특징과 종류를 확인할 수 있다.



### 5. Inside the Processor (CPU)

CPU는 아래의 부분들로 구성되어 다양한 작업을 수행한다.

* **Datapath**
* **Control**
* **Cache memory**

### 6. Abstractions

앞선 API 설명에서 추상화를 통해 내부 구조를 상세히 알 필요 없이 필요한 부분만 파악하는 것에 대한 효율성에 대해 언급한 바 있다. 컴퓨터(CPU)에서의 추상화는 다음과 같은 특징과 역할을 가진다.

* **복잡성 처리**
* **Instruction Set Architecture (ISA)**
* **이진 인터페이스 적용**
* **이행**

### 7. A Safe Place for Data

### 8. Response Time and Troughout

### 9. Execution Time

### 10. CPU Time

### 11. Instruction Count and CPI

--------

## 참고 자료

* *Computer Organization and Design (RISC-V Edition)* / **Morgan Kaufmann** 

    ([http://home.ustc.edu.cn/~louwenqi/reference_books_tools/Computer%20Organization%20and%20Design%20RISC-V%20edition.pdf](http://home.ustc.edu.cn/~louwenqi/reference_books_tools/Computer Organization and Design RISC-V edition.pdf))

* *The RISC-V Reader* / **David Patterson, Andrew Waterman**

    

