#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT configuration
const char* ssid = "YOUR_SSID";            // Replace with your WiFi SSID
const char* password = "YOUR_PASSWORD";    // Replace with your WiFi password
const char* mqtt_server = "YOUR_MQTT_BROKER_IP"; // Replace with your MQTT broker IP

WiFiClient espClient;
PubSubClient client(espClient);

// Pin definitions
const int motorPin = 32;     // Pin connected to the stepper motor driver
const int sensorLeft = 34;    // Pin connected to left jaw sensor
const int sensorRight = 35;   // Pin connected to right jaw sensor

void setup() {
    Serial.begin(115200);
    pinMode(motorPin, OUTPUT);
    pinMode(sensorLeft, INPUT);
    pinMode(sensorRight, INPUT);

    // Connect to WiFi
    setup_wifi();
    
    // Set up MQTT
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Read sensor values and publish position
    int position = read_position();
    client.publish("gripper/position", String(position).c_str());
}

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Gripper")) {
            Serial.println("connected");
            client.subscribe("gripper/control");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* message, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) {
        msg += (char)message[i];
    }
    if (msg == "0") {
        open_gripper();
    } else if (msg == "1") {
        close_gripper();
    }
}

void open_gripper() {
    // Logic to open the gripper
    digitalWrite(motorPin, HIGH);
    delay(1000); // Adjust delay for motor operation as needed
    digitalWrite(motorPin, LOW);
}

void close_gripper() {
    // Logic to close the gripper
    digitalWrite(motorPin, HIGH);
    delay(1000); // Adjust delay for motor operation as needed
    digitalWrite(motorPin, LOW);
}

int read_position() {
    // Average readings from both sensors
    int leftValue = analogRead(sensorLeft);
    int rightValue = analogRead(sensorRight);
    return (leftValue + rightValue) / 2; // Return average position
}
