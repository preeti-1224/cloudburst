#include <DHT.h>//for controlling temp. & humidity sensors
#define DHTPIN 5        // DHT sensor data pin
#define DHTTYPE DHT11   // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);//dht नाम का object बनाया
//इससे Arduino को पता चलेगा कि DHT11 sensor कौन से pin पर लगा है और किस type का है।

#define rainPin 2       // Rain sensor digital pin
#define ledPin 13       // LED pin
#define buzzerPin 4     // Buzzer pin

void setup() {
  Serial.begin(9600);// Serial Monitor चालू करो (9600 baud rate)
  pinMode(rainPin, INPUT);//Rain sensor input होगा
  pinMode(ledPin, OUTPUT);// LED output होगा
  pinMode(buzzerPin, OUTPUT);
  dht.begin();//DHT11 sensor शुरू करो
}

void loop() {
  // Read sensor data
  float temp = dht.readTemperature();   // Temperature   // DHT11 से temperature पढ़ो

  float hum = dht.readHumidity();       // Humidity
  int rain = digitalRead(rainPin);      // LOW = rain detected

  // Conditions
  bool rainDetected = (rain == LOW);//rAIN DETECT
  bool lowHumidity = (hum < 40);
  bool lowTemp = (temp < 20);
  bool highHumidity = (hum > 80);
  bool highTemp = (temp > 25);

  // Print values
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" C, Humidity: "); Serial.print(hum);

  if (rainDetected) {
    Serial.println(" --> Rain Detected!");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    Serial.println(" --> No Rain");
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // Warnings
  if (lowHumidity) {
    Serial.println("Warning: Low Humidity!");
  }
  if (lowTemp) {
    Serial.println("Warning: Low Temperature!");
  }

  // 🌩 Cloudburst Condition
  if (rainDetected && highHumidity && highTemp) {
    Serial.println("⚠⚠ CLOUD BURST WARNING ⚠⚠");//TEENO CONDITION milne pr alarm activate
    // Blink LED + fast buzzer for alert
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPin, HIGH); 
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(200);
    }
  }

  delay(1000); // 1 second delay
}
