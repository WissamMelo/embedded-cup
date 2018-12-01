

//Compara Horas e minutos (A FUNÇÃO ALARME UTILIZA PARA FUNCIONAR)
int comparaA(int Hora_x, int Min_x) {
  DateTime now = rtc.now();
  if (Hora_x == now.hour() && Min_x == now.minute() && now.second()<=1) {
    flag_compA = 1;
  }
  return flag_compA;
}

//Gerenciados de Alarme
void GerenciadorAlarme(int horario_inicial[2], int freq, int A) {

  //Verificar se a data inicial < data atual < data final
  DateTime now = rtc.now();

    //Verificar se o alarme foi modificado
    if ((freq != Cfreq[A]) || (Chorario_inicial[A][0] != horario_inicial[0]) || (Chorario_inicial[A][1] != horario_inicial[1])) {
      n[A] = 0;
      Cfreq[A] = freq;
      horario_referencia[A] = horario_inicial[0];
      Minuto_x[A] = horario_inicial[1];
      for (int i = 0; i < 2; i++) {
       Chorario_inicial[A][i] = horario_inicial[i];
      }
    }
    //Serial.println(n[A]);
    Hora_x[A] = horario_referencia[A] + freq * n[A];

    if (Hora_x[A] >= 24) {
      Hora_x[A] = Hora_x[A] - 24;
      horario_referencia[A] = Hora_x[A];
      n[A] = 0;
    }

    if (comparaA(Hora_x[A], Minuto_x[A])) {
      n[A] = n[A] + 1;
      C_Leds[A] = 1;
      flag_compA = 0;
    } else {
      flag_compA = 0;
      C_Leds[A] = 0;
    }

  }

void Gerenciador_LED(void) {
  for (int i = 0; i <= 3; i++) {
    if (C_Leds[i]) {
      Ac_LED[i] = 1;
    }
  }

  if (digitalRead(B_Copo) == HIGH) {
    for (int i = 0; i <= 3; i++) {
      if (Ac_LED[i]) {
        digitalWrite(Leds[i], HIGH);
      } else {
        digitalWrite(Leds[i], LOW);
      }
    }
    if (digitalRead(B_REM_OK) == LOW) {
      for (int i = 0; i <= 3; i++) {
        Ac_LED[i] = 0;
        digitalWrite(Leds[i], LOW);
      }
    }
  } else {
    for (int i = 0; i <= 3; i++) {
      digitalWrite(Leds[i], LOW);
    }
  }
}
