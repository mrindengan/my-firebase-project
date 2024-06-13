
### Firebase `README.md`

```markdown
# Firebase Configuration

This directory contains configuration files for setting up Firebase for the Lightbulb Control Project.

## Files

- `firebase-config.json`: Contains Firebase project configuration details.
- `firebase-rules.json`: Defines the security rules for Firebase Realtime Database.

## Setup Instructions

### 1. Create a Firebase Project

1. Go to the [Firebase Console](https://console.firebase.google.com/).
2. Click on "Add project" and follow the prompts to create a new Firebase project.

### 2. Add a Web App to Your Firebase Project

1. In the Firebase project overview page, click on the web icon (`</>`) to create a new web app.
2. Register the app and copy the Firebase configuration details.
3. Paste the configuration details into `public/app.js` and `firebase/firebase-config.json`.

### 3. Update Firebase Realtime Database Rules

1. In the Firebase Console, go to the Realtime Database section.
2. Click on the "Rules" tab and update the rules to match those in `firebase/firebase-rules.json`:

```json
{
  "rules": {
    ".read": "auth != null",
    ".write": "auth != null"
  }
}
