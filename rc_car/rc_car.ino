#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

#define FORMAT_SPIFFS_IF_FAILED true

// Replace with your network credentials
const char* ssid = "*********";
const char* password =  "***********";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// motor driver pins
int FM1 = 12;
int FM2 = 13;
int FM3 = 14;
int FM4 = 15;

int BM1 = 5;
int BM2 = 18;
int BM3 = 19;
int BM4 = 21;

// movement controller functions
void TL();
void TR();
void RL();
void RR();
void UP();
void DOWN();
void STOP();


const char index_html[] PROGMEM = R"rawliteral(
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RC Car</title>
    <style>
        html,
        body {
            box-sizing: border-box;
            padding: 0;
            margin: 0;
        }

        .main {
            width: 100vw;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            text-align: center;
            justify-content: center;
        }

        h3 {
            font-family: monospace;
        }

        .row {
            display: flex;
            flex-direction: row;
            text-align: center;
            justify-content: center;
        }

        .col {
            min-width: 25vw;
            min-height: 25vw;
            margin: 5vw;
        }

        button {
            width: 100%;
            height: 100%;
            background: transparent;
            border: none;
            outline: none;
        }

        img {
            width: 24vw;
        }
    </style>
</head>

<body>

    <div class="main">
        <h3>RC car V1.0</h3>
        <div class="row">
            <div class="col"><button onclick="movement(1)"><img src="up"></button></div>
        </div>
        <div class="row">
            <div class="col"><button onclick="movement(3)"><img src="left"></button></div>
            <div class="col"><button onclick="movement(0)"><img src="stop"></button></div>
            <div class="col"><button onclick="movement(4)"><img src="right"></button></div>
        </div>
        <div class="row">
            <div class="col"><button onclick="movement(2)"><img src="down"></button></div>
        </div>
    </div>

    <script>
        /*
         * Direction
         * 0 - Stop
         * 1 - Up
         * 2 - Down
         * 3 - Left
         * 4 - Right
         */

        function movement(direction) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    //console.log(this.responseText);
                }
            };
            xhttp.open("GET", "/move?state=" + direction, true);
            xhttp.send();
        }

    </script>
</body>

</html>
)rawliteral";


void setup(){

    // Serial port for debugging purposes
  Serial.begin(115200);
  
  pinMode(FM1, OUTPUT);
  pinMode(FM2, OUTPUT);
  pinMode(FM3, OUTPUT);
  pinMode(FM4, OUTPUT);
  pinMode(BM1, OUTPUT);
  pinMode(BM2, OUTPUT);
  pinMode(BM3, OUTPUT);
  pinMode(BM4, OUTPUT);

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/up", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/up.png", "image/png");
  });

   server.on("/down", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/down.png", "image/png");
  });
  
  server.on("/left", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/left.png", "image/png");
  });
  
  server.on("/right", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/right.png", "image/png");
  });
  
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/stop.png", "image/png");
  });
server.on("/move", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String state;
  if (request->hasParam("state")) {
    state = request->getParam("state")->value();
        /*
         * Direction
         * 0 - Stop
         * 1 - Up
         * 2 - Down
         * 3 - Left
         * 4 - Right
         */
    int move_state = state.toInt();
    if(move_state == 0)
      STOP();
    if(move_state == 1)
      UP();
    if(move_state == 2)
      DOWN();
    if(move_state == 3)
      TL();
    if(move_state == 4)
      TR();
    Serial.println(move_state);
  }
  request->send(200, "text/plain", "OK");
  
});

  // Start server
  server.begin();
}

void loop() {

}
