// Define pin numbers  
const int IR_SENSOR_PIN = 27; // Digital pin for the IR sensor  
const int LED_PIN = 22;        // Digital pin for the LED  

void setup() {  
    pinMode(IR_SENSOR_PIN, INPUT); // Set the IR sensor pin as input  
    pinMode(LED_PIN, OUTPUT);       // Set the LED pin as output  
    Serial.begin(9600);             // Start serial communication  
}  

void loop() {  
    int obstacleDetected = digitalRead(IR_SENSOR_PIN); // Read the IR sensor  

    Serial.println(obstacleDetected); // Print the raw value from the IR sensor  

    if (obstacleDetected == LOW) { // Assuming LOW means an obstacle is detected  
        digitalWrite(LED_PIN, HIGH); // Turn on the LED  
        Serial.println("Obstacle detected! LED ON");  
    } else {  
        digitalWrite(LED_PIN, LOW); // Turn off the LED  
        Serial.println("No obstacle detected. LED OFF");  
    }  

    delay(500); // Delay for readability  
}
