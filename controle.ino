void initControle() {
  pinMode(pinReleLed, OUTPUT);    
  bombaServo.attach(pinServo);
 
  EEPROM.get(0, totalAcumulado);
  EEPROM.get(10, volumeAtual);  
 
  if (isnan(totalAcumulado) || totalAcumulado < 0) totalAcumulado = 0.0;
  if (isnan(volumeAtual) || volumeAtual < 0) volumeAtual = 0.0;

  bombaServo.write(0);
}

void atualizarControle() {
  // Controle de Volume
  if (volumeAlvo > limiteVolume) volumeAlvo = limiteVolume;
 
  sensorBloqueou = (volumeAtual >= 9000);

  if (!sensorBloqueou && !erroChaves && volumeAtual < (volumeAlvo - 50)) {
    estadoBomba = true;
    volumeAtual += 100.0;  
    totalAcumulado += 100.0;
  } else if (volumeAtual > (volumeAlvo + 50)) {
    estadoBomba = false;
    volumeAtual -= 100.0;  
  } else {
    estadoBomba = false;
  }
 
  if (volumeAtual > 9000) volumeAtual = 9000;
  if (volumeAtual < 0) volumeAtual = 0;

  // Movimentação do Servo e Relé
  if (estadoBomba) {
    digitalWrite(pinReleLed, HIGH);
    posAnimacaoServo += velocidade;
    if (posAnimacaoServo > 180) posAnimacaoServo = 0;
    bombaServo.write(posAnimacaoServo);  
  } else {
    digitalWrite(pinReleLed, LOW);  
    bombaServo.write(0);
    posAnimacaoServo = 0;
  }
}

void salvarEEPROM() {
  if(millis() - ultimoTempoSave > 3000) {
    EEPROM.put(0, totalAcumulado);
    EEPROM.put(10, volumeAtual);
    ultimoTempoSave = millis();
  }
}
