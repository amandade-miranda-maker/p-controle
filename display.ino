void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void atualizarDisplay() {
  if (millis() - ultimoTempoLCD > 250) {
    ultimoTempoLCD = millis();

    if (erroChaves) {
      lcd.setCursor(0, 0);
      lcd.print("ERRO SENSORES!  ");
      lcd.setCursor(0, 1);
      lcd.print("VERIF. SENSOR ");
      lcd.print(sensorComDefeito);
      estavaEmErro = true;
    }
    else {
      if (estavaEmErro) { lcd.clear(); estavaEmErro = false; }

      int porcentagem = 0;
      if (c5) porcentagem = 90; else if (c4) porcentagem = 80;
      else if (c3) porcentagem = 50; else if (c2) porcentagem = 30;
      else if (c1) porcentagem = 10;

      lcd.setCursor(0, 0);
      lcd.print("S:");
      if (c5) lcd.print("5"); else if (c4) lcd.print("4"); else if (c3) lcd.print("3");
      else if (c2) lcd.print("2"); else if (c1) lcd.print("1"); else lcd.print("0");
     
      lcd.print(" V:"); lcd.print((long)volumeAtual);
      lcd.print("    ");
      lcd.setCursor(12, 0);
      lcd.print(porcentagem); lcd.print("% ");

      lcd.setCursor(0, 1);
      lcd.print("A:"); lcd.print((long)totalAcumulado);
      lcd.print(" B:");
      if (volumeAtual >= 9000) lcd.print("BLQ");
      else lcd.print(estadoBomba ? "ON " : "OFF");
    }
  }
}