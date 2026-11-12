// Define the ESP32 pin connected to the MOSFET Gate (via the 100-ohm resistor)
const int FAN_PIN = 33; 

void setup() {
  // Start the Serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Set the MOSFET pin as an OUTPUT
  pinMode(FAN_PIN, OUTPUT);
  
  // Ensure the fan is explicitly turned OFF when the ESP32 boots up
  digitalWrite(FAN_PIN, LOW);
  
  Serial.println("Ceremet Blower Fan Control Initialized.");
  Serial.println("Type 'on' to start the fan, or 'off' to stop it.");
}

void loop() {
  // Check if any data has been typed into the Serial Monitor
  if (Serial.available() > 0) {
    
    // Read the input until the user presses Enter
    String input = Serial.readStringUntil('\n');
    
    // Remove any hidden whitespace, carriage returns (\r), or newline (\n) characters
    input.trim(); 
    
    // Check what the user typed (equalsIgnoreCase makes it ignore capital/lowercase letters)
    if (input.equalsIgnoreCase("on")) {
      digitalWrite(FAN_PIN, HIGH); // Send 3.3V to the MOSFET Gate
      Serial.println("Fan Status: ON (3.3V sent to Gate)");
    } 
    else if (input.equalsIgnoreCase("off")) {
      digitalWrite(FAN_PIN, LOW); // Send 0V to the MOSFET Gate
      Serial.println("Fan Status: OFF (0V sent to Gate)");
    } 
    else {
      // Catch any typos
      Serial.println("Invalid command. Please type exactly 'on' or 'off'.");
    }
  }
}