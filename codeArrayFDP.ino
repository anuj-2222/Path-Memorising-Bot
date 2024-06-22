#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

// Motor pins
// Motor A connections
#define motor1PWM 26
#define motor1Pin1 25
#define motor1Pin2 33

// Motor B connections
#define motor2PWM 17
#define motor2Pin1 4
#define motor2Pin2 16

// WiFi settings
const char *ssid = "realme 7";
const char *password = "itsme123";

AsyncWebServer server(80);

// Stack for path memorization
char pathArray[10];
int pathIndex = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor2PWM, OUTPUT);

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup web server
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  // server.on("/memorize", handleMemorize);
  server.on("/recall", handleRecall);

  server.begin();


}

void loop()
{
}

void handleRoot(AsyncWebServerRequest *request)
{
  String htmlPage = "<html><head>";
  htmlPage += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
  htmlPage += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css'>";
  htmlPage += "</head><body>";
  htmlPage += "<div class='container'>";
  htmlPage += "<h1 class='text-center'>ESP32 Path Memorizing Robot</h1>";
  htmlPage += "<h3 class='text-center'>Available Commands:</h3>";
  htmlPage += "<ul class='list-unstyled text-center'>";
  htmlPage += "<li><a href='/forward'><i class='fas fa-arrow-up fa-5x'></i></a></li>";
  htmlPage += "<li><a href='/backward'><i class='fas fa-arrow-down fa-5x'></i></a></li>";
  htmlPage += "<li><a href='/left'><i class='fas fa-arrow-left fa-5x'></i></a></li>";
  htmlPage += "<li><a href='/right'><i class='fas fa-arrow-right fa-5x'></i></a></li>";
  htmlPage += "<li><a href='/stop'><i class='fas fa-stop-circle fa-5x'></i></a></li>";
  // htmlPage += "<li><a href='/memorize'><i class='fas fa-file-archive fa-5x'></i></a></li>";
  htmlPage += "<li><a href='/recall'><i class='fas fa-history fa-5x'></i></a></li>";
  htmlPage += "</ul>";
  htmlPage += "</div>";
  htmlPage += "</body></html>";

  request->send(200, "text/html", htmlPage);
}

void handleForward(AsyncWebServerRequest *request)
{
  moveForward();
  request->send(200, "text/plain", "Moving forward");
}

void handleBackward(AsyncWebServerRequest *request)
{
  moveBackward();
  request->send(200, "text/plain", "Moving backward");
}

void handleLeft(AsyncWebServerRequest *request)
{
  turnLeft();
  request->send(200, "text/plain", "Turning left");
}

void handleRight(AsyncWebServerRequest *request)
{
  turnRight();
  request->send(200, "text/plain", "Turning right");
}

void handleStop(AsyncWebServerRequest *request)
{
  stopRobot();
  request->send(200, "text/plain", "Stopping");
}

// void handleMemorize(AsyncWebServerRequest *request)
// {
//   memorizePath();
//   request->send(200, "text/plain", "Path memorized");
// }

void handleRecall(AsyncWebServerRequest *request)
{
  recallPath();
  request->send(200, "text/plain", "Path recalled");
}

void moveForward()
{
  // Code to move the robot forward
  digitalWrite(motor1Pin1, HIGH); // Set motor 1 pin 1 to HIGH
  digitalWrite(motor1Pin2, LOW);  // Set motor 1 pin 2 to LOW
  digitalWrite(motor2Pin1, HIGH); // Set motor 2 pin 1 to HIGH
  digitalWrite(motor2Pin2, LOW);  // Set motor 2 pin 2 to LOW

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 253); // Set motor 1 PWM to maximum speed
  analogWrite(motor2PWM, 255); // Set motor 2 PWM to maximum speed
  delay(750);
  stopRobot();

  // Memorize the movement
  pathArray[pathIndex] = 'F';
  pathIndex++;
}

void moveForward2()
{
  // Code to move the robot forward
  digitalWrite(motor1Pin1, HIGH); // Set motor 1 pin 1 to HIGH
  digitalWrite(motor1Pin2, LOW);  // Set motor 1 pin 2 to LOW
  digitalWrite(motor2Pin1, HIGH); // Set motor 2 pin 1 to HIGH
  digitalWrite(motor2Pin2, LOW);  // Set motor 2 pin 2 to LOW

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 253); // Set motor 1 PWM to maximum speed
  analogWrite(motor2PWM, 255); // Set motor 2 PWM to maximum speed
  delay(750);
  stopRobot();
}
void moveBackward()
{
  // Code to move the robot backward
  digitalWrite(motor1Pin1, LOW);  // Set motor 1 pin 1 to LOW
  digitalWrite(motor1Pin2, HIGH); // Set motor 1 pin 2 to HIGH
  // digitalWrite(motor2Pin1, LOW);  // Set motor 2 pin 1 to LOW
  digitalWrite(motor2Pin2, HIGH); // Set motor 2 pin 2 to HIGH

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 253); // Set motor 1 PWM to maximum speed
  analogWrite(motor2PWM, 255); // Set motor 2 PWM to maximum speed
  delay(750);
  stopRobot();
  // Memorize the movement
  pathArray[pathIndex] = 'B';
  pathIndex++;
}
void moveBackward2()
{
  // Code to move the robot backward
  digitalWrite(motor1Pin1, LOW);  // Set motor 1 pin 1 to LOW
  digitalWrite(motor1Pin2, HIGH); // Set motor 1 pin 2 to HIGH
  // digitalWrite(motor2Pin1, LOW);  // Set motor 2 pin 1 to LOW
  digitalWrite(motor2Pin2, HIGH); // Set motor 2 pin 2 to HIGH

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 253); // Set motor 1 PWM to maximum speed
  analogWrite(motor2PWM, 255); // Set motor 2 PWM to maximum speed
  delay(750);
  stopRobot();}

void turnLeft()
{
  // Code to turn the robot left
  digitalWrite(motor1Pin1, LOW); // Set motor 1 pin 1 to HIGH
  digitalWrite(motor1Pin2, HIGH);  // Set motor 1 pin 2 to LOW
  digitalWrite(motor2Pin1, HIGH);  // Set motor 2 pin 1 to LOW
  digitalWrite(motor2Pin2, LOW); // Set motor 2 pin 2 to HIGH

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 230); // Example: moderate speed
  analogWrite(motor2PWM, 230); // Example: moderate speed
  delay(750);
  stopRobot();
  // Memorize the movement
  pathArray[pathIndex] = 'L';
  pathIndex++;
}
void turnLeft2()
{
  // Code to turn the robot left
  digitalWrite(motor1Pin1, LOW); // Set motor 1 pin 1 to HIGH
  digitalWrite(motor1Pin2, HIGH);  // Set motor 1 pin 2 to LOW
  digitalWrite(motor2Pin1, HIGH);  // Set motor 2 pin 1 to LOW
  digitalWrite(motor2Pin2, LOW); // Set motor 2 pin 2 to HIGH

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 230); // Example: moderate speed
  analogWrite(motor2PWM, 230); // Example: moderate speed
  delay(750);
  stopRobot();
  // Memorize the movement
}
void turnRight()
{
  // Code to turn the robot right
  digitalWrite(motor1Pin1, HIGH);  // Set motor 1 pin 1 to LOW
  digitalWrite(motor1Pin2, LOW); // Set motor 1 pin 2 to HIGH
  digitalWrite(motor2Pin1, LOW); // Set motor 2 pin 1 to HIGH
  digitalWrite(motor2Pin2, HIGH); // Set motor 2 pin 2 to LOW

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 230); // Example: moderate speed
  analogWrite(motor2PWM, 230); // Example: moderate speed
  delay(750);
  stopRobot();
  // Memorize the movement
  pathArray[pathIndex] = 'R';
  pathIndex++;
}
void turnRight2()
{
  // Code to turn the robot right
  digitalWrite(motor1Pin1, HIGH);  // Set motor 1 pin 1 to LOW
  digitalWrite(motor1Pin2, LOW); // Set motor 1 pin 2 to HIGH
  digitalWrite(motor2Pin1, LOW); // Set motor 2 pin 1 to HIGH
  digitalWrite(motor2Pin2, HIGH); // Set motor 2 pin 2 to LOW

  // Adjust PWM for speed control
  analogWrite(motor1PWM, 230); // Example: moderate speed
  analogWrite(motor2PWM, 230); // Example: moderate speed
  delay(750);
  stopRobot();
}
void stopRobot()
{
  // Code to stop the robot
  digitalWrite(motor1Pin1, LOW);  // Set motor 1 pin 1 to LOW
  digitalWrite(motor1Pin2, LOW);  // Set motor 1 pin 2 to LOW
  digitalWrite(motor2Pin1, LOW);  // Set motor 2 pin 1 to LOW
  digitalWrite(motor2Pin2, LOW);  // Set motor 2 pin 2 to LOW

  // pathArray[pathIndex] = 'S';
  // pathIndex++;
}

const int MAX_PATH_SIZE = 50; // Maximum size of the path

// void memorizePath()
// {
//   // Code to memorize the current path
//   // Store the pathArray in non-volatile memory if needed

//   // Calculate the size of the pathArray
//   int pathSize = pathIndex;

//   // Store the pathSize at the beginning of the EEPROM
//   EEPROM.put(0, pathSize);

//   // Iterate over the pathArray and store each element in the EEPROM
//   for (int i = 0; i < pathSize; i++)
//   {
//     EEPROM.put(i + 1, pathArray[i]);
//   }

//   // Commit the changes to the EEPROM
//   EEPROM.commit();
// }

void recallPath()
{
  
  int i=10;
  Serial.println(pathArray);
  while(i>=0)
  {
    char movement = pathArray[i];
    
    if (movement == 'B')
    {
      moveForward2();
      Serial.println(pathArray[i]);
      // delay(1500);
    }
    else if (movement == 'F')
    {
      moveBackward2();
      Serial.println(pathArray[i]);
      // delay(1500);
    }
    if (movement == 'R')
    {
      turnLeft2();
      Serial.println(pathArray[i]);
      // delay(2000);
    }
    if (movement == 'L')
    {
      turnRight2();
      Serial.println(pathArray[i]);
      // delay(2000);
    }
    if (movement== 'S')
    {
      stopRobot();

    }
    else
    {
      stopRobot();
      Serial.println(pathArray[i]);
    }
    i--;
  }
}

