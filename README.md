# Smart Parking Management System

A real-time parking availability system using ESP32 microcontrollers with LED matrix displays and Firebase Realtime Database. This capstone design project displays parking slot availability across multiple 16x16 NeoPixel LED matrices, with real-time synchronization through a web dashboard.

## Features

- **Real-time Display**: 7 LED matrices (16x16 each, 256 LEDs per matrix) showing parking slot availability
- **Visual Feedback**: Green "O" for available slots, red "X" for occupied slots
- **Live Updates**: Instant synchronization between hardware displays and database
- **WiFi Connectivity**: ESP32 connects to Firebase via WiFi for real-time data streaming
- **Web Dashboard**: Monitor and manage parking slot status from any browser
- **Scalable Architecture**: Easily add more parking areas by adding ESP32 modules

## Project Structure

```
my-firebase-project/
├── esp32/
│   └── main/
│       └── main.ino          # ESP32 firmware for LED matrix control
├── firebase/
│   ├── firebase-config.json  # Firebase configuration template
│   ├── firebase-rules.json   # Realtime Database security rules
│   └── README.md             # Firebase setup guide
├── public/
│   ├── index.html            # Web dashboard HTML
│   ├── app.js                # Firebase integration & dashboard logic
│   ├── styles.css            # Dashboard styling
│   └── 404.html              # Custom 404 page
├── firebase.json             # Firebase hosting configuration
└── README.md                 # This file
```

## Prerequisites

### Hardware
- **ESP32 Microcontroller** (ESP32-DevKitC or similar)
- **WS2812B NeoPixel LED Strips** (7 matrices of 256 LEDs each, or 1,792 total LEDs)
- **Power Supply**: 5V 30A+ (to safely power all LEDs at maximum brightness)
- **Micro USB Cable** for ESP32 programming and power

### Software & Accounts
- **Arduino IDE** or **PlatformIO** for ESP32 development
- **Firebase Account** with Realtime Database enabled
- **Git** for cloning the repository
- **Node.js** (optional, for Firebase CLI local testing)

## Setup Instructions

### 1. Clone the Repository

```bash
git clone <your-github-repo-url>
cd my-firebase-project
```

### 2. Set Up Firebase Project

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Create a new project or use an existing one
3. Enable **Realtime Database** in your project
4. Navigate to **Database > Rules** and update with your security rules:

```json
{
  "rules": {
    "parkingSlots": {
      ".read": true,
      ".write": false
    }
  }
}
```

5. Create the database structure with parking slots:
```
parkingSlots/
├── slot_B1/
│   └── isAvailable: true
├── slot_B2/
│   └── isAvailable: true
└── ... (slots B3-B7)
```

6. Copy your Firebase credentials from **Project Settings > Web**

### 3. Configure ESP32 Sketch

1. Open `esp32/main/main.ino` in Arduino IDE
2. Install required libraries:
   - **FirebaseClient** (via Library Manager)
   - **Adafruit_NeoPixel** (via Library Manager)
3. Update credentials in the sketch:

```cpp
#define WIFI_SSID "your-wifi-ssid"
#define WIFI_PASSWORD "your-wifi-password"
#define DATABASE_URL "https://your-project.firebaseio.com/"
```

4. Configure hardware connections:
   - Connect WS2812B LED **DIN** to GPIO 13 of ESP32
   - Connect LED **5V** to ESP32 5V (via power supply)
   - Connect LED **GND** to ESP32 GND
5. Select Board: Tools → Board → ESP32 Dev Module
6. Select COM Port and upload the sketch

### 4. Deploy Web Dashboard

1. Install Firebase CLI:
```bash
npm install -g firebase-tools
```

2. Initialize Firebase in project:
```bash
firebase login
firebase init hosting
```

3. Deploy the public folder:
```bash
firebase deploy --only hosting
```

4. Update Firebase config in `public/app.js` with your credentials:
```javascript
const firebaseConfig = {
    apiKey: "your-api-key",
    authDomain: "your-project-id.firebaseapp.com",
    databaseURL: "https://your-project-id.firebaseio.com",
    projectId: "your-project-id",
    storageBucket: "your-project-id.appspot.com",
    messagingSenderId: "your-messaging-sender-id",
    appId: "your-app-id"
};
```

## Usage

### Hardware Operation

Once the ESP32 is powered and connected to WiFi:

1. **Initialization**: ESP32 fetches current parking slot status from Firebase
2. **Real-time Monitoring**: Listens for database changes every 5 seconds
3. **Display Update**: LED matrices instantly update to show availability
   - **Green "O"**: Parking slot is available
   - **Red "X"**: Parking slot is occupied

### Web Dashboard

Access the deployed web application to:
- View real-time parking slot status
- Monitor system connectivity
- Manually update slot availability (if authentication enabled)

## Hardware Specifications

### ESP32 Configuration
- **Operating Frequency**: 240 MHz
- **GPIO Pin 13**: WS2812B LED data pin
- **Power Draw**: ~150 mA (WiFi active)
- **Communication**: WiFi 802.11 b/g/n

### LED Matrix Display
- **Total LEDs**: 1,792 (7 matrices × 256 LEDs/matrix)
- **Resolution per Slot**: 16×16 pixel display
- **Color Scheme**: 
  - Available: Green (0, 255, 0)
  - Occupied: Red (255, 0, 0)
- **Brightness**: 50/255 (configurable in code)

## API Reference

### Firebase Database Structure

```
parkingSlots/
├── slot_B1/
│   ├── isAvailable: boolean
│   ├── lastUpdated: timestamp (optional)
│   └── location: string (optional)
├── slot_B2/
│   └── isAvailable: boolean
...
```

### Real-time Updates

The ESP32 uses Server-Sent Events (SSE) to listen for changes:
- **Path**: `/parkingSlots/{slotName}/isAvailable`
- **Event Type**: Stream
- **Polling Fallback**: Every 5 seconds

## Troubleshooting

### ESP32 Connection Issues
- **No WiFi connection**: Verify SSID and password in sketch
- **Firebase connection fails**: Check DATABASE_URL and confirm RT Database is enabled
- **Garbled LED output**: Ensure 5V power supply can handle 1,792 LEDs (max 15A @ full brightness)

### Web Dashboard Not Updating
- Verify Firebase configuration in `app.js`
- Check browser console for CORS or authentication errors
- Ensure database security rules allow read access

### LED Display Problems
- **No LEDs lighting**: Check GPIO 13 connection and power supply
- **Flickering display**: Increase power supply capacity (need 30A+)
- **Incorrect colors**: Verify NeoPixel color order is set to GRB

## Contributing

Contributions are welcome! Areas for improvement:
- Add occupancy sensor integration
- Implement predictive availability estimation
- Create mobile app version
- Add user authentication and role-based access
- Expand to support more parking areas

For contributions, please:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit changes (`git commit -am 'Add feature'`)
4. Push to branch (`git push origin feature/your-feature`)
5. Open a Pull Request

## Support

For issues, questions, or suggestions:
- Check existing [Issues](../../issues) and [Discussions](../../discussions)
- Review [Firebase Documentation](https://firebase.google.com/docs/guides)
- See [Arduino ESP32 Reference](https://docs.espressif.com/projects/arduino-esp32/en/latest/)

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) file for details.

## Maintainers

- **Matt Rindangan** - Project Lead

---

**Last Updated**: February 2026  
**Status**: Active Development
