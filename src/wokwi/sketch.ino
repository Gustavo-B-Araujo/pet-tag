#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

#define SS_PIN 5
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);

#define LED_VERDE 25
#define LED_AZUL 26
#define LED_VERMELHO 27

const char* ssid = "Wokwi-GUEST";
const char* senha = "";

const char* API = "https://iot-pet.onrender.com";

String ultimoUID = "";

void setup() {

  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("Conectando WiFi...");

  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");

  digitalWrite(LED_AZUL, HIGH);

  SPI.begin();

  rfid.PCD_Init();

  Serial.println("RFID iniciado");
  Serial.println("Aproxime uma tag...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      uid += "0";
    }

    uid += String(
      rfid.uid.uidByte[i],
      HEX
    );
  }

  uid.toUpperCase();

  if (uid == ultimoUID) {
    rfid.PICC_HaltA();
    return;
  }

  ultimoUID = uid;

  Serial.println();
  Serial.print("UID lido: ");
  Serial.println(uid);

  buscarPet(uid);

  rfid.PICC_HaltA();

  delay(2000);
}

void buscarPet(String uid){

  HTTPClient http;

  String url = String(API) + "/pets/" + uid;

  Serial.println(url);

  http.begin(url);

  int codigo = http.GET();

  if(codigo == 200){

    digitalWrite(
      LED_VERMELHO,
      LOW
    );

    String resposta =
    http.getString();

    DynamicJsonDocument doc(
      1024
    );

    deserializeJson(
      doc,
      resposta
    );

    Serial.println("Pet encontrado:");

    Serial.print("Nome: ");
    Serial.println(
      doc["nome"].as<String>()
    );

    Serial.print("Espécie: ");
    Serial.println(
      doc["especie"].as<String>()
    );

    Serial.print("Idade: ");
    Serial.println(
      doc["idade"].as<String>()
    );

    Serial.print("Tutor: ");
    Serial.println(
      doc["responsavel"].as<String>()
    );

    enviarDashboard(
      resposta
    );

  }

  else {

    Serial.println(
      "Pet não encontrado"
    );

    digitalWrite(
      LED_VERMELHO,
      HIGH
    );

    String erroJson = R"(
    {
      "erro": true,
      "mensagem":"Pet não encontrado",
      "uid":")" + uid + R"("
    })";

    enviarDashboard(
      erroJson
    );
  }

}

void enviarDashboard(String json){

  HTTPClient http;

  String url = String(API) + "/ultima-leitura";

  Serial.println("Enviando para dashboard...");
  Serial.println(url);

  http.begin(url);

  http.addHeader(
    "Content-Type",
    "application/json"
  );

  int codigo = http.POST(json);

  Serial.print("Código POST: ");
  Serial.println(codigo);

  if(codigo > 0){

    String respostaServidor =
      http.getString();

    Serial.println("Resposta:");

    Serial.println(
      respostaServidor
    );

    Serial.println(
      "Dashboard atualizado"
    );

  }
  else{

    Serial.println(
      "Falha ao enviar"
    );

  }

  http.end();
}