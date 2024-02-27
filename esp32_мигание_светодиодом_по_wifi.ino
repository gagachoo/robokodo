  #include <WiFi.h>
  #include <WebServer.h>
  const char* ssid = "ROBOKODO";
  const char* password = "12345678";
  IPAddress local_ip(192,168,1,1);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  WebServer server(80);
  int a = 0;

  void handle_led1off() {
  a = 1;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led2off() {
  a = 2;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led3off() {
  a = 3;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led4off() {
  a = 4;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led5off() {
  a = 5;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led6off() {
  a = 6;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led7off() {
  a = 7;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led8off() {
  a = 8;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led9off() {
  a = 9;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led10off() {
  a = 10;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_NotFound(){
    server.send(404, "text/plain", "Not found 404");
  }
  void handle_OnConnect() {
    server.send(200, "text/html", SendHTML(false,0));
  }
   String SendHTML(uint8_t led1stat,uint8_t led2stat){
    String ptr = "<!DOCTYPE html> <html>";
    ptr +="<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
    ptr +="<title>РОБОКОДО</title>";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}";
    ptr +=".button {display: block;width: 80px;background-color: #ffffff;border: none;color: #777777 ;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border: 1px solid #777777;}";
    ptr +=".button-off {background-color: #ffffff;}";
    ptr +=".button-off:active {background-color: #ffffff;}";
    ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}";
    ptr +="</style>";
    ptr +="<script>        ";
    ptr +="function send(led_sts)      ";
    ptr +="{        ";
    ptr +="  var xhttp = new XMLHttpRequest();     ";
    ptr +="  xhttp.onreadystatechange = function() {      ";
    ptr +="    if (this.readyState == 4 && this.status == 200) {      ";
    ptr +="      document.getElementById(\"state\").innerHTML = this.responseText;    ";
    ptr +="    }        ";
    ptr +="  };        ";
    ptr +="  xhttp.open(\"GET\", \"led\"+led_sts, true);   ";
    ptr +="  xhttp.send();        ";
    ptr +=" } ";
    ptr +="setInterval(function()       ";
    ptr +="{        ";
    ptr +="  getData();    ";
    ptr +="}, 2000);       ";
    ptr +="function getData() {   ";
    ptr +="  var xhttp = new XMLHttpRequest();       ";
    ptr +="  xhttp.onreadystatechange = function() {        ";
    ptr +="    if (this.readyState == 4 && this.status == 200) {        ";
    ptr +="      document.getElementById(\"adc_val\").innerHTML = this.responseText;    ";
    ptr +="    }        ";
    ptr +="  };        ";
    ptr +="  xhttp.open(\"GET\", \"adcread\", true);    ";
    ptr +="  xhttp.send();     ";
    ptr +="}        ";
    ptr +="</script>   ";
    ptr +="</head>";
    ptr +="<body>";
     ptr +="<a class=\"button button-off\"  onclick=\"send(1)\">ON</a>";
     if (a == 1) {
        pinMode(2, OUTPUT);
     digitalWrite(2, 1);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(2)\">OFF</a>";
     if (a == 2) {
        pinMode(2, OUTPUT);
     digitalWrite(2, 0);

     }
        ptr +="</body>";
    ptr +="</html>";
    return ptr;
  }


void setup() {

    Serial.begin(9600);
    delay(100);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
   server.on("/", handle_OnConnect);
    server.on("/led1", handle_led1off);
    server.on("/led2", handle_led2off);
    server.on("/led3", handle_led3off);
    server.on("/led4", handle_led4off);
    server.on("/led5", handle_led5off);
    server.on("/led6", handle_led6off);
    server.on("/led7", handle_led7off);
    server.on("/led8", handle_led8off);
    server.on("/led9", handle_led9off);
    server.on("/led10", handle_led10off);

    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP server started");


}

void loop() {
    server.handleClient();

}