# CS50
## 소개
+ CS50은 Havard University에서 공개하는 **컴퓨터과학 입문 강의**입니다.
+ [CS50 fall 2019](https://cs50.harvard.edu/college/2019/fall/) 과제의 풀이 저장소입니다.
+ CS50에서 제공하는 과제 체크 프로그램(check50)을 통과하면 완료로 처리했습니다.
<br>
<br>

## 📁 problem set 1 - C
### 1. Mario
사용자에게 높이를 입력받고, 해당 크기의 '#'으로 만든 피라미드를 콘솔에 출력하는 과제
+ 반복문 이용
### 2. Cash
사용자에게 금액을 입력받고, 거슬러줄 수 있는 동전의 최소 개수를 구하는 과제
+ Greedy algorithm
### 3. Credit
카드 번호를 입력받아 유효한 번호인지 체크하고, 맞다면 발행 카드사의 명칭을 출력하는 과제
+ Luhn's algorithm

<br>

## 📁 problem set 2 - Arrays
### 1. Readability
사용자에게 텍스트를 입력받아 Coleman-Liau index를 계산하여 해당 텍스트를 읽기에 적절한 학년을 구하는 과제
### 2. Caesar
사용자에게 암호키는 명령행 인자로, 평문은 프롬프트로 입력받고 카이사르 암호 알고리즘에 따라 평문을 암호화하여 출력하는 과제
+ 카이사르 암호 : 평문의 각 문자를 일정 자릿수만큼 회전시켜서 암호화하는 방식
### 3. Substitution
사용자에게 암호키는 명령행 인자로, 평문은 프롬프트로 입력받고 치환 암호 알고리즘에 따라 평문을 암호화하여 출력하는 과제
+ 치환 암호 : 26자리의 알파벳 배열을 암호키로 사용하여, A부터 Z까지 알파벳 문자를 순서대로 암호키에 대응시키고 평문의 각 문자를 그에 상응하는 것으로 치환하여 암호화하는 방식

<br>

## 📁 problem set 3 - Algorithms
### 1. Plurality
명령행 인자로 입후보자들의 이름을 받고 프롬프트로 투표자 수를 입력받은 후 다수결 투표를 시뮬레이션하는 프로그램을 만드는 과제
### 2. Runoff
동점자를 처리하지 못하는 다수결 투표를 보완한, 순위선택투표 시스템의 일종인 즉각결선투표를 시뮬레이션하는 프로그램을 만드는 과제
+ 순위선택투표 : 투표자가 선호하는 순서대로 복수의 후보자에게 투표할 수 있는 투표 방식(여기서는 각 투표자가 모든 후보자에 대해 순위를 매긴다고 가정) 
+ 즉각결선투표 : 당선자(과반수의 득표를 한 후보자)가 없는 경우 가장 적은 표를 얻은 후보자를 탈락시키고 해당 후보자를 뽑은 투표자의 차선 후보자에게 표를 이동시켜 즉각적으로 결선을 진행하는 것을 반복하여 최종 당선자를 가리는 투표 시스템
### 3. Tideman
콩도르세 역설이 발생하지 않도록 즉각결선투표를 보완한 투표 시스템을 시뮬레이션하는 프로그램을 만드는 과제
+ 콩도르세 역설 : 다른 모든 후보자들과의 일대일 대결에서 승리하는 후보자가 투표에서 패배하는 경우
+ 재귀 함수 이용

<br>

## 📁 problem set 4 - Memory
### 1. Filter
입력받은 BMP 이미지 파일의 RGB 값을 조정하여 다양한 효과를 적용한 새 이미지 파일을 출력하는 프로그램을 만드는 과제
+ Grayscale : 흑백 이미지로 변환하는 효과
+ Sepia : 오래된 느낌이 나는 적갈색 이미지로 변환하는 효과
+ Reflection : 좌우 반전된 이미지로 변환하는 효과
+ Blur : 흐릿한 이미지로 변환하는 효과
+ Edges : Sobel operator를 이용하여 이미지에 존재하는 윤곽을 강조하는 효과
### 2. Recover
RAW 파일 데이터에서 JPEG 시그니처 바이트를 찾아 이미지 파일로 복원하는 프로그램을 만드는 과제

<br>

## 📁 problem set 5 - Data Structures
### 1. Speller
검사 대상 텍스트 파일과 사전 텍스트 파일을 받아 사전에 없는 단어를 검사하는 프로그램을 만드는 과제
+ 해시 테이블 및 연결 리스트 사용
