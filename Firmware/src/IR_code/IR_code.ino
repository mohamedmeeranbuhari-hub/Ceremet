// Define the ESP32 pin connected to the TCRT5000 D0 pin
const int IR_SENSOR_PIN = 32; 

// Variables for the non-blocking timer
unsigned long previousMillis = 0; 
const long interval = 1000; // Time between checks in milliseconds (1 second)

void setup() {
  // Start the Serial Monitor at 115200 baud
  Serial.begin(115200);
  
  // Set the IR sensor pin as an input
  pinMode(IR_SENSOR_PIN, INPUT);
  
  Serial.println("Ceremet IR Compliance Sensor Initialized.");
}

void loop() {
  // Get the current time the ESP32 has been running
  unsigned long currentMillis = millis();

  // Check if 1 second (1000ms) has passed since the last print
  if (currentMillis - previousMillis >= interval) {
    // Save the last time you read the sensor
    previousMillis = currentMillis;

    // Read the digital value from the sensor (1 or 0)
    int sensorState = digitalRead(IR_SENSOR_PIN);

    // The LM393 chip on the IR board usually outputs LOW (0V) when it detects an object.
    // It outputs HIGH (3.3V) when nothing is in front of it.
    if (sensorState == LOW) {
      Serial.println("Status: Helmet ON (Driver Detected)");
    } 
    else {
      Serial.println("Status: Helmet OFF (Empty)");
    }
  }
  
  // You can safely put other code here (like MPU6050 checks or Audio tasks)
  // and it will run continuously without being blocked!
}