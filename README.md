<p align = "center">
  <img width="720" height="316"  alt="image" src="https://github.com/user-attachments/assets/afeec5d8-44cf-43a1-8afa-59db78741844" />
</p>
<h1 align="center">🩸 말초 혈류속도 스마트 측정기 </h1>


## 📌 Introduction

- 고혈압, 동맥경화, 당뇨병, 비만 등 다양한 요인으로 인한 심뇌혈관 질환은 고령화와 함께 환자 수가 꾸준히 증가하고 있습니다.
- 초기에 이상 증상이 나타나지 않아 **조기 발견과 지속적인 모니터링이 매우 중요하며**, 이를 위해 말초 동맥 압력, 맥파 속도, 말초 혈류 속도 등 **다양한 혈역학적 생체 정보 측정이 필요합니다.**
- 누구나 시간과 장소 제약 없이 사용 가능하도록 PPG 센서(광용적맥파 측정 센서)와 소형 아두이노를 활용한 **손목 착용형 스마트 혈류속도 측정기**를 개발하여 심뇌혈관 건강 관리를 위한 새로운 플랫폼을 제공하고자 하였습니다.

---
## 📊 Project Overview
- **프로젝트명**: 말초혈류속도 스마트 측정기
- **개발기간**: 2024.03.20 ~ 2024.11.25
- **팀명**: Hope-세이프티넷
---
## 👥 팀 구성 및 역할
- **김용찬(팀장)**: 말초혈류속도 측정 및 계산 알고리즘 구축, H/w 부품 납땜 및 회로설계
- **이하정(팀원)**: DB구축, Node red(IOT 통신 및 데이터 시각화 UI), 부품 디자인  
---

## 🔍 Method

<img width="750" height="350" alt="image" src="https://github.com/user-attachments/assets/d2553506-a4c4-4ac7-8c67-78f3a46319d2" /><br>

- (a) **공간말초혈류속도(SPBFV)**: 손목의 요골동맥에 위치한 PPG-1과 손가락 모세혈관에 위치한 PPG-2로부터 동시에 측정된 두 맥파의 피크시간 차이(△τ)를 손길이(LH)로 나누어 정의.
- (b)(c) PPG-1 첫 번째 피크와 PPG-2 두 번째 피크의 시간 차이(△τ1i)를 정의하며, i는 5번까지 연속 카운트를 나타냄 △τ의 평균값(△τave)을 계산하여 손길이(LH)로 나눔으로써 SPBFV 도출.

---

### ⚙ Hardware & Software Components

<table>
  <tr>
    <td align="center">
      <b>🔧 Hardware</b><br>
      <img src="https://github.com/user-attachments/assets/e5808a50-5fcc-43c3-b456-481075cf57a3" width="360"/>
    </td>
    <td align="center">
      <b>💻 Software</b><br>
      <img src="https://github.com/user-attachments/assets/16116485-c362-445f-b983-4112d6dc3b29" width="360"/>
    </td>
  </tr>
</table>

---

### 📡 System Workflow

<img width="1200" height="450" alt="image" src="https://github.com/user-attachments/assets/7beef9fc-d2a1-455c-8f2d-9d59612b3694" /> <br>

- 스마트 혈류속도 측정기로 손목과 손가락 데이터의 피크지점을 검출하여 심박수 측정하고 공간말초혈류속도(SPBFV)는 계산 알고리즘을 통해 산출.
- 실시간 심박수와 공간말초혈류속도는 Wifi를 통해 MQTT 통신으로 라즈베리파이5 서버에 전송되고 스마트폰/PC에서 기기측정 및 결과 확인 가능.

---

## ✅ Result

<table>
  <tr>
    <td align="center">
      <b>착용 전면</b><br>
      <img src="https://github.com/user-attachments/assets/d91ccfae-f1c8-48a5-90f4-f988b95a1de8" width="320"/>
    </td>
    <td align="center">
      <b>착용 후면</b><br>
      <img src="https://github.com/user-attachments/assets/e4424c5c-092c-451f-93a1-37a1baf51f5e" width="320"/>
    </td>
    <td align="center">
      <b>내부</b><br>
      <img src="https://github.com/user-attachments/assets/4c0e9794-6f6c-40d3-a5b5-7f7f2f28d60f" width="320"/>
    </td>
  </tr>
</table>

<br>

<table>
  <tr>
    <td align="center" width="50%">
      <b>👤 사용자 정보 입력 및 측정시작 화면</b><br>
      <img src="https://github.com/user-attachments/assets/0642e4c4-36bf-49a5-8490-d7835b21bcb6"
           style="height:300px; object-fit:contain;"/>
    </td>
    <td align="center" width="50%">
      <b>📈 실시간 심박수 공간말초혈류도 측정 화면</b><br>
      <img src="https://github.com/user-attachments/assets/be5cc483-cda7-4095-86cb-c1497774db2f"
           style="height:300px; object-fit:contain;"/>
    </td>
  </tr>
  <tr>
    <td align="center" width="50%">
      <b>📋 심박수&공간말초혈류속도에 따른 분석지</b><br>
      <img src="https://github.com/user-attachments/assets/c6dcf4a8-bb6d-4118-85e2-b0bf29cd8456"
           style="height:300px; object-fit:contain;"/>
    </td>
    <td align="center" width="50%">
      <b>📊 측정데이터 누적</b><br>
      <img src="https://github.com/user-attachments/assets/232e57db-d87c-409d-96d3-c9f9a6595bcb"
           style="height:300px; object-fit:contain;"/>
    </td>
  </tr>
</table>

---

## 🎥 Device Demonstration Video (Click!)

<p align="center">
  <a href="https://www.youtube.com/watch?v=CaS8rED5mL0">
    <img src="https://img.youtube.com/vi/CaS8rED5mL0/maxresdefault.jpg" width="800"/>
  </a>
</p>

---

## 💥Troubleshooting
### 1️⃣ 요골동맥 PPG 센서부분 노이즈로 인한 피크 검출 오류
- **문제 상황**  
  - 요골동맥의 전압값이 손가락 모세혈관에 비해 매우 낮아 맥파의 정확한 피크 검출이 어려웠습니다.   


- **원인 분석**  
  - 살짝의 동잡음에도 맥파신호가 불안정하게 측정되었습니다.  
  - 해당 ppg 센서에 맞는 스펙과 sampling rate를 고려 하지 않았습니다.   

- **해결 방법**  
  - 해당 센서의 <DFRobot_Heartrate.h> 라이브러리 안에있는 새로운 getLastPeakTime()이라는 함수를 만들어 실시간 피크검출기능을 구현하였습니다.
  - getLastPeakTime() 함수를 적용하여 실시간 검출된 peak 시간을 배열에 저장하여 말초혈류속도 계산에 활용하였습니다.

- **🟡결과**
  - 요골동맥과 손가락 모세혈관의 맥파 peak검출 개수의 정확도 10%에서 95%로 향상되었습니다. 

- **💻핵심 코드**
<p align = "center">
  <img width="1475" height="768" alt="image" src="https://github.com/user-attachments/assets/cd74c4c8-3599-4bb5-aa47-6d7cb775fc88" />
</p>

### 2️⃣ 말초혈류 속도 계산방식의 오류 
- **문제 상황**
  - 각 부위에 검출된 peak시간 배열 데이터를 활용하여 최종 평균 말초혈류속도 계산할때 오류확률이 높았습니다.
- **원인 분석**
  - 동잡음으로 하나라도 peak배열 데이터에 이상이 있을때 결과값이 이상해졌습니다.
- **해결 방법**
  - 빠르게 변화하는 혈류속도 특성에 맞게 배열의 크기를 6개로 줄인뒤 순환버퍼를 사용하여 측정시간동안 계속해서 말초혈류속도 값을 계산하도록
    방식을 수정하였습니다.
- **🟡결과**
  - 동잡음으로 잘못측정되는 결과의 오류율 90% 이상 개선시켰습니다.
- **💻핵심 코드**
<p align = "center">
 <img width="1460" height="886" alt="image" src="https://github.com/user-attachments/assets/3e53e03a-563a-4f59-9ab7-a8db652901c7" />
</p>


---
## 🧠 Discussion

- 본 플랫폼은 **새로운 혈역학 생체정보인 공간말초혈류속도(SPBFV)를 제공함으로써**, 실시간 측정으로 비대면 진료 환경에서도 유용하게 활용될 수 있으며, 디지털 헬스케어 시대에 맞춘 혁신적인 **심뇌혈관 관리 솔루션으로 자리매김할 수 있을 것으로 보임.**



## 📄 Publication 

> 본 프로젝트는 실제 학술 논문으로 확장되어 연구 성과로 이어졌습니다.

---

### 1️⃣ Properties of Spatial Pulse Wave Velocity and Spatial Peripheral Blood Flow Velocity using Magneto-plethysmogram and Photoplethysmogram
- **자료유형** : 학술 저널 
- **저널정보**: 한국자기학회 > Journal of Magnetics > Journal of Magnetics Vol.29 No.4  ✔KCI등재  ✔SCIE
- **링크**: https://www.dbpia.co.kr/journal/articleDetail?nodeId=NODE12031245  

#### 📌 연구 내용
- PPG 센서를 활용한 말초 혈류속도 측정 시스템 설계  
- 공간말초혈류속도(SPBFV) 산출 알고리즘 제안  
- 실시간 데이터 수집 및 분석을 통한 헬스케어 적용 가능성 검증  


---

### 2️⃣ 광용적맥파계를 이용한 손목착용형 공간말초혈류속도 측정기 특성 연구
- **자료유형**: 학술저널
- **저널정보**: 한국자기학회 > 한국자기학회지 > 한국자기학회지 제35권 제2호  ✔KCI등재
- **링크**: https://www.dbpia.co.kr/journal/articleDetail?nodeId=NODE12149890  

#### 📌 연구 내용
- IoT 기반 혈류 데이터 수집 및 전송 시스템 구축  
- MQTT 통신을 활용한 실시간 데이터 처리 구조 설계  
- 사용자 인터페이스를 통한 시각화 및 모니터링 기능 구현  

---



