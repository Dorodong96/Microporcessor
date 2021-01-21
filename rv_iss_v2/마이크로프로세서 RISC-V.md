# 마이크로프로세서 RISC-V RV32I

RISC-V 32-bit 명령어 RV32I의 Instruction Set Simulator (ISS)를 C언어로 구현하였습니다.



## 명령어 유형

### RISC-V Base Instruction Format

![image](https://user-images.githubusercontent.com/45297745/105386797-2dc9a800-5c58-11eb-9c53-5a4e314e92c7.png)

(출처 : RISC-V 프로세서의 모의실행 및 합성, 이종복 [http://www.koreascience.or.kr/article/JAKO201912937047301.pdf])



## 구현 명령어

수업 시간 및 예제 실행을 위해 구현한 명령어입니다. (유사한 방식의 구현은 별도 설명 생략)

### 1. add

* *Add* 
* R[rd] = R[rs1] + R[rs2]
* R-type 명령어
* 레지스터 rs1의 값과 rs2의 값을 더한 결과를 rd에 저장합니다.



### 2. addi

* *Add Immediate* 
* R[rd] = R[rs1] + imm
* I-type 명령어
* 레지스터 rs1의 값과 imm값을 더한 결과를 rd에 저장합니다.



### 3. sll

* *Shift Left Logical*
* R[rd] = R[rs1] << R[rs2]
* R-type 명령어
* 레지스터 rs1의 값을 rs2의 값만큼 왼쪽으로 시프트 한 결과를 rd에 저장합니다.



### 4. slli

* *Shift Left Logical Immediate* 
* R[rd] = R[rs1] << imm
* I-type 명령어
* 레지스터 rs1의 값과 imm값만큼 왼쪽으로 시프트 한 결과를 rd에 저장합니다.



### 5. or

* *OR*
* R[rd] = R[rs1] | R[rs2]
* R-type 명령어
* 레지스터 rs1의 값과 rs2의 값을 or연산 한 결과를 rd에 저장합니다.



### 6. ori

* *OR Immediate*
* R[rd] = R[rs1] | imm
* I-type 명령어
* 레지스터 rs1의 값과 imm값을 or연산 한 결과를 rd에 저장합니다.



### 7. and

* *AND*
* R[rd] = R[rs1] & R[rs2]
* R-type 명령어
* 레지스터 rs1의 값과 rs2의 값을 and연산 한 결과를 rd에 저장합니다.



### 8. andi

* *AND Immediate* 
* R[rd] = R[rs1] & imm
* I-type 명령어
* 레지스터 rs1의 값과 imm값을 and연산 한 결과를 rd에 저장합니다.



### 9. lb, lh, lw

* *Load Byte, Halfword, Word*
* lb : R[rd] = M[R[rs1] + imm] [7 : 0] (Sign Extension)
* lh : R[rd] = M[R[rs1] + imm] [15 : 0] (Sign Extension)
* lw : R[rd] = M[R[rs1] + imm] [31 : 0] (Sign Extension)
* I-type 명령어
* 메모리의 [rs1+imm]주소부터 1-Byte(Byte), 2-Byte(Halfword), 4-Byte(Word) Data를 rd에 저장합니다.



### 10. lbu, lhu

* *Load Byte, Half Unsigned*
* lbu : R[rd] = M[rs1 + imm] [7 : 0]
* lhu : R[rd] = M[rs1 + imm] [15 : 0]
* I-type 명령어
* 메모리의 [rs1+(Unsigned)imm]주소부터 1-Byte(Byte), 2-Byte(Half) Data를 rd에 저장합니다.



### 11. sb, sh, sw

* *Store Byte, Halfword, Word*
* sb : M[R[rs1] + imm] = R[rs2] [7 : 0]
* sh : M[R[rs1] + imm] = R[rs2] [15 : 0]
* sw : M[R[rs1] + imm] = R[rs2] [31 : 0]
* S-type 명령어
* 메모리의 [rs1+imm]주소에 R[rs2]의 하위 1-Byte(Byte), 2-Byte(Halfword), 4-Byte(Word) Data를 저장합니다.



### 12. beq, bne

* *Branch If (Not) Equal*
* beq : if (R[rs1] == R[rs2])    PC += imm
* bne : if (R[rs1] != R[rs2])    PC += imm
* B-type 명령어
* 레지스터 rs1의 값과 rs2의 값이 같으면(다르면) 현재 PC값에 imm(offset)값을 더합니다.



### 13. blt

* *Branch if Less Than*
* if (R[rs1] < R[rs2])    PC += imm
* SB-type 명령어
* 레지스터 rs1의 값이 rs2의 값보다 작으면 현재 PC값에 imm(offset)값을 더합니다.



### 14. bltu

* *Branch if Less Than, Unsigned*
* if (R[rs1] < R[rs2])    PC += imm
* SB-type 명령어
* 부호없는 레지스터 rs1의 값이 rs2의 값보다 작으면 현재 PC값에 imm(offset)값을 더합니다.



### 15. bge

* *Branch if Greater Than or Equal*
* if (R[rs1] >= R[rs2])    PC += imm
* SB-type 명령어
* 레지스터 rs1의 값이 rs2의 값보다 작으면) 현재 PC값에 imm(offset)값을 더합니다.



### 15. bgeu

* *Branch if Greater Than or Equal, Unsigned*
* if (R[rs1] >= R[rs2])    PC += imm
* SB-type 명령어
* 부호 없는 레지스터 rs1의 값이 rs2의 값보다 작으면) 현재 PC값에 imm(offset)값을 더합니다.



## 추가 구현

수업 시간 및 과제에서 다룬 내용 이외의 부분들을 구현하였습니다.

### 1. xor

* *XOR* 

* R[rd] = R[rs1] ^ R[rs2]

* type 명령어

* 레지스터 rs1의 값과 rs2의 값을 xor연산 한 결과를 rd에 저장합니다.

  ![image](https://user-images.githubusercontent.com/45297745/105386335-9ebc9000-5c57-11eb-9107-0bac6682ba26.png)

  

### 2. xori

* *XOR Immediate* 
* R[rd] = R[rs1] ^ imm
* type 명령어
* 레지스터 rs1의 값과 imm값을 xor연산 한 결과를 rd에 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386338-9fedbd00-5c57-11eb-83ac-1c8294789689.png)



### 3. slt 

* *Set Less Than* 
* R[rd] = (R[rs1] < R[rs2])? 1 : 0
* type 명령어
* 레지스터 rs1 값이 rs2의 값 보다 작으면 rd를 1로, 그렇지 않으면 0으로 set합니다.

![image](https://user-images.githubusercontent.com/45297745/105386343-a2501700-5c57-11eb-94bd-53ab4d62bd83.png)



### 4. slti

* *Set Less Than Immediate* 
* R[rd] = (R[rs1] < imm)? 1 : 0
* type 명령어
* 레지스터 rs1 값이 imm의 값 보다 작으면 rd를 1로, 그렇지 않으면 0으로 set합니다.

![image](https://user-images.githubusercontent.com/45297745/105386346-a3814400-5c57-11eb-8e20-64a0bf220d98.png)



### 5. sltu

* *Set Less Than Unsigned*
* R[rd] = (R[rs1] < R[rs2])? 1 : 0
* type 명령어
* 레지스터 rs1 값이 rs2 값 보다 작으면 rd를 1, 그렇지 않으면 0으로 set합니다.(unsigned)

![image](https://user-images.githubusercontent.com/45297745/105386349-a54b0780-5c57-11eb-8e11-b3bd02f4c269.png)



### 6. sltiu

* *Set Less Than Immediate Unsigned* 
* R[rd] = (R[rs1] < imm)? 1 : 0
* type 명령어
* 레지스터 rs1 값이 imm값 보다 작으면 rd를 1, 그렇지 않으면 0으로 set합니다.(unsigend)

![image](https://user-images.githubusercontent.com/45297745/105386356-a67c3480-5c57-11eb-9326-f1637ad51f4f.png)



### 7. srl

* *Shift Right Logical* 
* R[rd] = R[rs1] >> R[rs2]
* type 명령어
* 레지스터 rs1값을 rs2값만큼 우측 논리시프트 한 값을 rd에 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386363-a845f800-5c57-11eb-9691-6e38229665c6.png)



### 8. srli

* *Shift Right Logical Immediate* 
* R[rd] = R[rs1] >> imm
* type 명령어
* 레지스터 rs1값을 imm(shamt)값만큼 우측 논리시프트 한 값을 rd에 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386371-a9772500-5c57-11eb-97a9-ab9e5d507a0f.png)



### 9. sra

* *Shift Right Arithmetic* 
* R[rd] = R[rs1] >> R[rs2]
* type 명령어
* 레지스터 rs1값을 rs2값만큼 우측 산술시프트 한 값을 rd에 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386376-ab40e880-5c57-11eb-8386-ba8ddf2769d3.png)



### 10. srai

* *Shift Right Arithmetic Immediate* 
* R[rd] = R[rs1] >> imm
* type 명령어
* 레지스터 rs1값을 imm(shamt)값만큼 우측 산술시프트 한 값을 rd에 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386382-ad0aac00-5c57-11eb-9bc2-ddd398d968c3.png)



### 11. lui 

* *Load Upper Immediate* 
* x[rd] = imm[31:12] << 12
* type 명령어
* 레지스터 rd에 32비트 imm의 상위 20비트를 저장합니다. (addi와 함께 사용)

![image](https://user-images.githubusercontent.com/45297745/105386390-ae3bd900-5c57-11eb-8a49-875b15c04a2d.png)



### 12. auipc

* *Add upper Immediate to PC* 
* x[rd] = pc + imm[31:12] << 12
* type 명령어
* 레지스터 rd에 32비트 imm의 상위 20비트에 현재 pc값을 더한 값을 저장합니다.

![image](https://user-images.githubusercontent.com/45297745/105386398-b09e3300-5c57-11eb-8f09-3098ff6103aa.png)