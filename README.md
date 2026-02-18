# 🩺 스마트 혈류속도 측정기 (Smart Blood Flow Meter)
## 📌 Introduction

- 고혈압, 동맥경화, 당뇨병, 비만 등 다양한 요인으로 인한 심뇌혈관 질환은 고령화와 함께 환자 수가 꾸준히 증가.
- 초기에 이상 증상이 나타나지 않아 **조기 발견과 지속적인 모니터링이 매우 중요하며**, 이를 위해 말초 동맥 압력, 맥파 속도, 말초 혈류 속도 등 **다양한 혈역학적 생체 정보 측정이 필요.**
- 누구나 시간과 장소 제약 없이 사용 가능하도록 PPG 센서(광용적맥파 측정 센서)와 소형 아두이노를 활용한 **손목 착용형 스마트 혈류속도 측정기**를 개발하여 심뇌혈관 건강 관리를 위한 새로운 플랫폼을 제공.

## 🔍 Method
<img width="750" height="350" alt="image" src="https://github.com/user-attachments/assets/d2553506-a4c4-4ac7-8c67-78f3a46319d2" /><br>

- (a) **공간말초혈류속도(SPBFV)**: 손목의 요골동맥에 위치한 PPG-1과 손가락 모세혈관에 위치한 PPG-2로부터 동시에 측정된 두 맥파의 피크시간 차이(△τ)를 손길이(LH)로 나누어 정의.
- (b)(c) PPG-1 첫 번째 피크와 PPG-2 두 번째 피크의 시간 차이(△τ1i)를 정의하며, i는 5번까지 연속 카운트를 나타냄 △τ의 평균값(△τave)을 계산하여 손길이(LH)로 나눔으로써 SPBFV 도출.

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

### 📡 System Workflow
<img width="1200" height="450" alt="image" src="https://github.com/user-attachments/assets/7beef9fc-d2a1-455c-8f2d-9d59612b3694" /> <br>
-  스마트 혈류속도 측정기로 손목과 손가락 데이터의 피크지점을 검출하여 심박수 측정하고 공간말초혈류속도(SPBFV)는 계산 알고리즘을 통해 산출.
-  실시간 심박수와 공간말초혈류속도는 Wifi를 통해 mqtt통신으로 라즈베리파이5 서버에 전송되고 스마트폰/PC에서 기기측정 및 결과획인 가능.    


## ⭐ Result 

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

<table>
  <tr>
    <td align="center" width="50%">
      <b>👤 사용자 정보 입력 및 측정시작 화면</b><br>
      <img src="https://github.com/user-attachments/assets/0642e4c4-36bf-49a5-8490-d7835b21bcb6" width="500"/>
    </td>
    <td align="center" width="50%">
      <b>📈 실시간 심박수 공간말초혈류도 측정 화면</b><br>
      <img src="https://github.com/user-attachments/assets/be5cc483-cda7-4095-86cb-c1497774db2f" width="500"/>
    </td>
  </tr>
  <tr>
    <td align="center" width="50%">
      <b>📋 심박수&공간말초혈류속도에따른 분석지</b><br>
      <img src="https://github.com/user-attachments/assets/c6dcf4a8-bb6d-4118-85e2-b0bf29cd8456" width="500"/>
    </td>
    <td align="center" width="50%">
      <b>📊 측정데이터 누적 </b><br>
      <img src="https://github.com/user-attachments/assets/232e57db-d87c-409d-96d3-c9f9a6595bcb" width="500"/>
    </td>
  </tr>
</table>



