void initSensores() {
  pinMode(pinChave1, INPUT);
  pinMode(pinChave2, INPUT);
  pinMode(pinChave3, INPUT);
  pinMode(pinChave4, INPUT);
  pinMode(pinChave5, INPUT);
}

void lerSensores() {
  // Leitura do Potenciômetro (Média móvel simples)
  long somaPot = 0;
  for(int i=0; i<10; i++) somaPot += analogRead(pinPotVazao);
  int leituraPot = somaPot / 10;
  
  volumeAlvo = (leituraPot / 1023.0) * 9000.0;
  velocidade = map(leituraPot, 0, 1023, 1, 15);

  // Leitura das Chaves (Sensores)
  c1 = digitalRead(pinChave1);
  c2 = digitalRead(pinChave2);
  c3 = digitalRead(pinChave3);
  c4 = digitalRead(pinChave4);
  c5 = digitalRead(pinChave5);

  // Lógica de Limite por Sensor
  if (c5)      limiteVolume = 9000.0;
  else if (c4) limiteVolume = 8000.0;
  else if (c3) limiteVolume = 6000.0;
  else if (c2) limiteVolume = 4000.0;
  else if (c1) limiteVolume = 2000.0;
  else         limiteVolume = 0.0;    

  // Identificação de ERRO específico nos sensores
  erroChaves = false;
  sensorComDefeito = 0;
  
  if (c5 && !c4) { erroChaves = true; sensorComDefeito = 4; }
  else if ((c5 || c4) && !c3) { erroChaves = true; sensorComDefeito = 3; }
  else if ((c5 || c4 || c3) && !c2) { erroChaves = true; sensorComDefeito = 2; }
  else if ((c5 || c4 || c3 || c2) && !c1) { erroChaves = true; sensorComDefeito = 1; }
}