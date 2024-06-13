import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.1/firebase-app.js";
import { getDatabase, ref, set, onValue } from "https://www.gstatic.com/firebasejs/9.6.1/firebase-database.js";

// Firebase configuration
const firebaseConfig = {
    apiKey: "your-api-key", // Replace with your Firebase project's API key
    authDomain: "your-auth-domain", // Replace with your Firebase project's auth domain (e.g., project-id.firebaseapp.com)
    databaseURL: "your-database-url", // Replace with your Firebase Realtime Database URL (e.g., https://project-id.firebaseio.com)
    projectId: "your-project-id", // Replace with your Firebase project ID
    storageBucket: "your-storage-bucket", // Replace with your Firebase project's storage bucket (e.g., project-id.appspot.com)
    messagingSenderId: "your-messaging-sender-id", // Replace with your Firebase project's messaging sender ID
    appId: "your-app-id", // Replace with your Firebase project's app ID
    measurementId: "your-measurement-id" // Replace with your Firebase project's measurement ID (if applicable)
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

// DOM elements
const onOffButton = document.getElementById('onOffButton');
const toggleModeButton = document.getElementById('toggleModeButton');

// Function to set light status
function setLightStatus(status) {
    set(ref(database, 'lightStatus'), status)
        .then(() => console.log('Light status updated to:', status))
        .catch((error) => console.log('Error updating light status:', error));
}

// Update button styles and state
function updateButtonState(lightStatus) {
    if (lightStatus === 'TOGGLE') {
        toggleModeButton.checked = true;
        onOffButton.disabled = true;
    } else {
        toggleModeButton.checked = false;
        onOffButton.disabled = false;
        onOffButton.checked = (lightStatus === 'ON');
    }
}

// Read initial light status from database
const lightStatusRef = ref(database, 'lightStatus');
onValue(lightStatusRef, (snapshot) => {
    const lightStatus = snapshot.val();
    updateButtonState(lightStatus);
});

// Event listeners
onOffButton.addEventListener('change', () => {
    if (!toggleModeButton.checked) {
        setLightStatus(onOffButton.checked ? 'ON' : 'OFF');
    }
});

toggleModeButton.addEventListener('change', () => {
    setLightStatus(toggleModeButton.checked ? 'TOGGLE' : 'OFF');
});
