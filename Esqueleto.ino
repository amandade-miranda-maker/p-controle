#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Servo.h>

// Objetos globais
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo bombaServo;

// Pinos
const int pinServo = 9;
const int pinReleLed = 12;
const int pinPotVazao = A0;
const int pinChave1 = 2;
const int pinChave2 = 3;
const int pinChave3 = 4;
const int pinChave4 = 5;
const int pinChave5 = 6;

// Variáveis de Estado Global (Compartilhadas entre os módulos)
float volumeAtual = 0.0;
bool estadoBomba = false;
bool sensorBloqueou = false;
float totalAcumulado = 0.0;
unsigned long ultimoTempoSave = 0;
unsigned long ultimoTempoLCD = 0;
bool estavaEmErro = false;
int posAnimacaoServo = 0;

// Variáveis de Comunicação entre módulos
float volumeAlvo = 0.0;
int velocidade = 0;
float limiteVolume = 0.0;
bool erroChaves = false;
int sensorComDefeito = 0;
bool c1, c2, c3, c4, c5; // Estado atual das chaves

void setup() {
  initDisplay();   // Inicializa o LCD (Pessoa 3)
  initSensores();  // Inicializa os Pinos de Entrada (Pessoa 1)
  initControle();  // Inicializa Servo, Relé e EEPROM (Pessoa 2)
}

void loop() {
  lerSensores();       // Lida com Inputs (Pessoa 1)
  atualizarControle(); // Lida com a Lógica da Bomba (Pessoa 2)
  salvarEEPROM();      // Lida com a Memória (Pessoa 2)
  atualizarDisplay();  // Atualiza o LCD (Pessoa 3)
  
  delay(30);
}
