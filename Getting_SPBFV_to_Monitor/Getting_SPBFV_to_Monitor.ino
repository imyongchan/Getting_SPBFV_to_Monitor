#include <Arduino.h>
#include <DFRobot_Heartrate.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define BUFFER_SIZE 6

// WiFi 설정
const char* ssid = "Sangji-wifi_free";
//const char* ssid = "CJWiFi_B3AE";
//const char* password = "7001009107";
const char* mqtt_server = "118.44.127.45";
//const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic_start = "start";
const char* mqtt_topic_hand_length = "hand_length";
const char* mqtt_topic_results_bpm1 = "measurement_results/bpm1";
const char* mqtt_topic_results_bpm2 = "measurement_results/bpm2";
const char* mqtt_topic_results_pbfv = "measurement_results/PBFV";
const char* mqtt_topic_finish = "measurement_results/Finish";

const char* clientID = "ESP32Client_1";

WiFiClient espClient;
PubSubClient client(espClient);

// 센서 핀 설정
const int heartRatePin1 = 4; // 손목
const int heartRatePin2 = 3; // 손가락
const int ledPin = 8; // LED 핀 설정

DFRobot_Heartrate wristSensor(ANALOG_MODE); // 손목 센서용 객체 생성
DFRobot_Heartrate fingerSensor(ANALOG_MODE); // 손가락 센서용 객체 생성

float peakTimes1[BUFFER_SIZE] = {0}; // 손목 피크 시간 저장
float peakTimes2[BUFFER_SIZE] = {0}; // 손가락 피크 시간 저장
int peakIndex1 = 0; // 손목 피크 배열의 현재 인덱스
int peakIndex2 = 0; // 손가락 피크 배열의 현재 인덱스
int peakCount1 = 0; // 손목 피크의 총 개수
int peakCount2 = 0; // 손가락 피크의 총 개수


unsigned long startTime;
bool measurementCompleted = false;
bool startMeasurement = false;
unsigned long lastReconnectAttempt = 0;
const long reconnectInterval = 5000; // 5초마다 재연결 시도

float HandLength = 0.0;  
float PBFV_sum = 0.0;  
int PBFV_count = 0; 
float PBFV_average = 0.0;   
int bpm1_sum = 0;
int bpm2_sum = 0;
int bpm_count1 = 0;
int bpm_count2 = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  //WiFi.begin(ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (strcmp(topic, mqtt_topic_start) == 0) {
    if (message == "start" && HandLength > 0.0) {
      resetMeasurement();
      startMeasurement = true;
      startTime = millis();
      Serial.println("Measurement started");
    }
  } else if (strcmp(topic, mqtt_topic_hand_length) == 0) {
    HandLength = message.toFloat();
    Serial.printf("Updated Hand Length: %.2f cm\n", HandLength);
  }
}

boolean reconnect() {
  if (client.connect(clientID)) {
    Serial.println("Mqtt connected");
    client.subscribe(mqtt_topic_start);
    client.subscribe(mqtt_topic_hand_length);
    digitalWrite(ledPin, HIGH); // MQTT 연결되면 LED 켜기
    return true;
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    return false;
  }
}


void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(ledPin, OUTPUT); // LED 핀을 출력 모드로 설정 (필수)
  digitalWrite(ledPin, LOW); // 초기 상태는 꺼짐으로 설정
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
}


float calculateAverage(float *data, int size) {
  if (size == 0) return 0.0;
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += data[i];
  }
  return sum / size;
}

void resetMeasurement() {
  // 모든 변수 및 상태 초기화
  memset(peakTimes1, 0, sizeof(peakTimes1));
  memset(peakTimes2, 0, sizeof(peakTimes2));
  peakIndex1 = 0;
  peakIndex2 = 0;
  peakCount1 = 0;
  peakCount2 = 0;
  PBFV_sum = 0.0;
  PBFV_count = 0;
  PBFV_average = 0.0;
  bpm1_sum = 0;
  bpm2_sum = 0;
  bpm_count1 = 0;
  bpm_count2 = 0;
  startMeasurement = false;
  measurementCompleted = false;
  startTime = 0;
}


void loop() {
   if (!client.connected()) {
    unsigned long currentTime = millis();
    if (currentTime - lastReconnectAttempt > reconnectInterval) {
      lastReconnectAttempt = currentTime;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
  }

  if (!startMeasurement) {
    // 측정 중이 아니면 아무 것도 하지 않고 대기
    return;
  }

  if (startMeasurement) {
    unsigned long currentTime = millis();
    float time = (currentTime - startTime) / 1000.0;


    if (time <= 20 && !measurementCompleted) {
      

      // 손목 및 손가락 BPM 계산
      uint16_t sensorValue1 = wristSensor.getValue(heartRatePin1); // 센서 값 읽기
      uint16_t sensorValue2 = fingerSensor.getValue(heartRatePin2); // 센서 값 읽기

      //DFRobot_Heartrate.h 라이브러리 bpm 측정 
      int bpm1 = wristSensor.getRate(); 
      int bpm2 = fingerSensor.getRate();

      // bpm 측정 라이브러리의 피크검출부분 =>손목 피크 저장 
      if (bpm1 > 0) {
        peakTimes1[peakIndex1] = wristSensor.getLastPeakTime() / 1000.0;  // 피크 시간을 초 단위로 기록
        peakIndex1 = (peakIndex1 + 1) % BUFFER_SIZE;  // 인덱스 업데이트
        if (peakCount1 < BUFFER_SIZE) {
          peakCount1++;
        }
        String bpm1Message = String(bpm1);
        client.publish("bpm1", bpm1Message.c_str());
        bpm1_sum += bpm1;
        bpm_count1++;
        
      }
        
      /// bpm 측정 라이브러리의 피크검출부분 =>손가락 피크 저장 
      if (bpm2 > 0) {
        peakTimes2[peakIndex2] = fingerSensor.getLastPeakTime() / 1000.0;  // 피크 시간을 초 단위로 기록
        peakIndex2 = (peakIndex2 + 1) % BUFFER_SIZE;  // 인덱스 업데이트
        if (peakCount2 < BUFFER_SIZE) {
          peakCount2++;
        }
        String bpm2Message = String(bpm2);
        client.publish("bpm2", bpm2Message.c_str());
        bpm2_sum += bpm2;
        bpm_count2++;
      }
      
      delay(20);

      // PBFT 계산 (6개의 피크가 쌓이면 계산)
      if (peakCount1 >= 6 && peakCount2 >= 6) {
        float peak_time_diffs[5];

        for (int i = 0; i < 5; i++) {
          int wristIndex = (peakIndex1 + BUFFER_SIZE - 5 + i) % BUFFER_SIZE;  // 손목 피크의 순차적인 위치
          int fingerIndex = (peakIndex2 + BUFFER_SIZE - 5 + (i + 1)) % BUFFER_SIZE;  // 손가락 피크의 순차적인 위치

          // 손목 피크가 감지된 이후의 손가락 피크와의 시간 차이를 계산
          float wristTime = peakTimes1[wristIndex];
          float fingerTime = peakTimes2[fingerIndex];

          // 손가락 피크가 손목 피크 이후에 발생했는지 확인
          if (fingerTime > wristTime) {
            peak_time_diffs[i] = abs(fingerTime - wristTime);
          } else {
            peak_time_diffs[i] = 0;  // 손가락 피크가 손목 피크보다 먼저 발생했을 경우, 차이를 0으로 설정
          }
        }
        // 피크 시간 차이 평균 계산
        float PBFT = calculateAverage(peak_time_diffs, 5);
        
        // PBFT 속도 계산 (손길이 / 피크 시간 차이 평균)
        if (PBFT > 0) { 
          float PBFV = HandLength / PBFT;
          
          if (PBFV >= 10.0 && PBFV <= 60.0) {
            PBFV_sum += PBFV;
            PBFV_count++;
            String PBFVMessage = String(PBFV);
            client.publish("PBFV", PBFVMessage.c_str());
          }
        }
      }

    } else if (!measurementCompleted) {
      // 데이터 수집 완료
      measurementCompleted = true;
      startMeasurement = false;

    
      if (PBFV_count > 0) {
        PBFV_average = PBFV_sum / PBFV_count;
        client.publish(mqtt_topic_results_pbfv, String(PBFV_average).c_str());
      }
      
      int bpm1_average = (bpm_count1 > 0) ? (bpm1_sum / bpm_count1) : 0;
      int bpm2_average = (bpm_count2 > 0) ? (bpm2_sum / bpm_count2) : 0;
      client.publish(mqtt_topic_results_bpm1, String(bpm1_average).c_str());
      client.publish(mqtt_topic_results_bpm2, String(bpm2_average).c_str());
      // 측정 완료 후 완료 메시지 전송
      client.publish(mqtt_topic_finish, "Finish");
      // 측정 완료 후 LED 끄기
      digitalWrite(ledPin, LOW);
      

      
      // 측정 완료 후 변수 초기화
      resetMeasurement();
      Serial.println("Measurement completed and sent");
    }
  }
}
