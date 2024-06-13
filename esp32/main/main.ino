#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your Firebase project credentials
#define FIREBASE_HOST "projectexodus-4d033-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "hjlx3aY78wu31JtNTG9jFlvuAAImEw6HR4dcuw75"

// Firebase Data object
FirebaseData firebaseData;

// Firebase Config object
FirebaseConfig config;

// Firebase Auth object
FirebaseAuth auth;

const int relayPin = 5; // GPIO pin connected to the relay
const int soundSensorPin = 4; // Digital pin connected to the sound sensor

bool lightStatus = false; // Track the current status of the light
bool toggleMode = false; // Track if in TOGGLE mode
bool previousSoundState = LOW; // Track the previous state of the sound sensor
String firebaseStatus = ""; // Store the current status from Firebase

String ssid;
String password;

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid.c_str(), password.c_str());
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 40) { // Attempt to reconnect for 20 seconds
      Serial.println();
      Serial.println("Failed to connect to Wi-Fi. Restarting...");
      ESP.restart();
    }
  }
  Serial.println();
  Serial.print("Connected to Wi-Fi. IP address: ");
  Serial.println(WiFi.localIP());
}

void toggleLightWithSound() {
  // Read the current state of the sound sensor
  int soundValue = digitalRead(soundSensorPin);
  Serial.println(soundValue);

  // Toggle the light if the sound threshold is exceeded
  if (soundValue == HIGH && previousSoundState == LOW) {
    lightStatus = !lightStatus;
    digitalWrite(relayPin, lightStatus ? HIGH : LOW);
    Serial.print("Toggled light to: ");
    Serial.println(lightStatus ? "ON" : "OFF");
    delay(300); // Short debounce delay to avoid multiple triggers
  }
  previousSoundState = soundValue;
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(2000); // Allow time for serial monitor to open and clear buffer

  Serial.println("Starting setup...");

  // Initialize relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure the relay is off at the start

  // Initialize sound sensor pin as input
  pinMode(soundSensorPin, INPUT);

  // Prompt for WiFi credentials
  Serial.println("Enter SSID:");
  while (Serial.available() == 0) {}
  ssid = Serial.readStringUntil('\n');
  ssid.trim();
  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.println("Enter Password:");
  while (Serial.available() == 0) {}
  password = Serial.readStringUntil('\n');
  password.trim();
  Serial.print("Password: ");
  Serial.println(password);

  // Connect to Wi-Fi
  connectToWiFi();

  // Assign the Firebase credentials and host
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase connection
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Setup completed.");
}

void loop() {
  // Monitor the Firebase Realtime Database for changes in the "lightStatus" key
  if (Firebase.getString(firebaseData, "/lightStatus")) {
    if (firebaseData.dataType() == "string") {
      String newStatus = firebaseData.stringData();
      Serial.print("Firebase light status: ");
      Serial.println(newStatus);

      if (newStatus == "ON") {
        digitalWrite(relayPin, HIGH); // Turn on the light
        lightStatus = true;
        toggleMode = false; // Exit TOGGLE mode
        Serial.println("Switched to manual ON mode.");
      } else if (newStatus == "OFF") {
        digitalWrite(relayPin, LOW); // Turn off the light
        lightStatus = false;
        toggleMode = false; // Exit TOGGLE mode
        Serial.println("Switched to manual OFF mode.");
      } else if (newStatus == "TOGGLE") {
        toggleMode = true; // Enter TOGGLE mode
        Serial.println("Switched to TOGGLE mode.");
      } else {
        Serial.println("Error: unexpected string value.");
      }
      firebaseStatus = newStatus;
    } else {
      Serial.println("Error: data type is not string.");
    }
  } else {
    Serial.print("Error: ");
    Serial.println(firebaseData.errorReason());
  }

  // If in TOGGLE mode, use the sound sensor to toggle the light
  if (toggleMode) {
    toggleLightWithSound();
  }

  delay(50); // Short delay before the next check to keep the loop running
}
