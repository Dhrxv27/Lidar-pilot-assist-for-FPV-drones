#include <SoftwareSerial.h>

// -------------------- HC-SR04 (Rear) --------------------
const int trigPin = 10;
const int echoPin = 12;

// -------------------- LiDAR (Front - TF Mini) --------------------
SoftwareSerial lidarSerial(3, 5);
uint16_t lidarDistance = 0;

// -------------------- Buzzer --------------------
const int buzzerPin = 8;

// -------------------- Thresholds (cm) --------------------
const int THRESHOLD_CRITICAL = 20;
const int THRESHOLD_WARNING  = 50;

// -------------------- Timing --------------------
unsigned long lastUltrasonicRead = 0;
unsigned long lastBuzzerToggle = 0;
bool buzzerState = false;
const unsigned long ultrasonicInterval = 100;

// -------------------- Smoothing --------------------
const int NUM_SAMPLES = 3;
int ultrasonicBuffer[NUM_SAMPLES] = {0};
uint16_t lidarBuffer[NUM_SAMPLES] = {0};
int bufferIndex = 0;

void setup() {
  Serial.begin(9600);
  lidarSerial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  Serial.println("FPV Obstacle Detection System Ready");
}

void loop() {
  // Read sensors
  int rawUltrasonic = readUltrasonic();
  uint16_t rawLidar = readTFMini();

  // Store in rolling buffer
  if (rawUltrasonic > 0) ultrasonicBuffer[bufferIndex] = rawUltrasonic;
  if (rawLidar > 0)      lidarBuffer[bufferIndex]      = rawLidar;
  bufferIndex = (bufferIndex + 1) % NUM_SAMPLES;

  // Averaged readings
  int ultrasonicDistance = average(ultrasonicBuffer, NUM_SAMPLES);
  int lidarDistanceAvg   = average(lidarBuffer, NUM_SAMPLES);

  // Determine alert level
  int minDist = minValid(ultrasonicDistance, lidarDistanceAvg);

  if (minDist > 0 && minDist <= THRESHOLD_CRITICAL) {
    // Critical — continuous buzzer
    digitalWrite(buzzerPin, HIGH);
  } else if (minDist > 0 && minDist <= THRESHOLD_WARNING) {
    // Warning — pulsed buzzer, faster as closer
    unsigned long buzzerInterval = map(minDist, 0, THRESHOLD_WARNING, 50, 300);
    if (millis() - lastBuzzerToggle >= buzzerInterval) {
      buzzerState = !buzzerState;
      digitalWrite(buzzerPin, buzzerState);
      lastBuzzerToggle = millis();
    }
  } else {
    digitalWrite(buzzerPin, LOW);
    buzzerState = false;
  }

  // Debug output
  Serial.print("Front LiDAR: ");
  Serial.print(lidarDistanceAvg);
  Serial.print(" cm | Rear Ultrasonic: ");
  Serial.print(ultrasonicDistance);
  Serial.print(" cm | Alert: ");
  Serial.println(minDist <= THRESHOLD_CRITICAL ? "CRITICAL" :
                 minDist <= THRESHOLD_WARNING  ? "WARNING"  : "CLEAR");

  delay(50);
}

// ==================== FUNCTIONS ====================

int readUltrasonic() {
  if (millis() - lastUltrasonicRead < ultrasonicInterval) return -1;
  lastUltrasonicRead = millis();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return -1;
  return duration * 0.0344 / 2;
}

uint16_t readTFMini() {
  while (lidarSerial.available() >= 9) {
    if (lidarSerial.read() == 0x59 && lidarSerial.read() == 0x59) {
      uint8_t buffer[7];
      for (int i = 0; i < 7; i++) buffer[i] = lidarSerial.read();
      return buffer[0] + buffer[1] * 256;
    }
  }
  return 0;
}

int average(int* arr, int len) {
  int sum = 0, count = 0;
  for (int i = 0; i < len; i++) {
    if (arr[i] > 0) { sum += arr[i]; count++; }
  }
  return count > 0 ? sum / count : 0;
}

int minValid(int a, int b) {
  if (a > 0 && b > 0) return min(a, b);
  if (a > 0) return a;
  if (b > 0) return b;
  return 0;
}