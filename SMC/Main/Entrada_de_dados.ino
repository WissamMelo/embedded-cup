

void deletar_1(){
    int botao = digitalRead(in1);
  if(botao == 1 && lastbotao == 0){
    alarmes[0].horario_inicial = 0;
    alarmes[0].minutos_inicial = 0;
    alarmes[0].freq = 0;
      Serial.println("deletado alarme1");
      Serial.println("Dados = ");
      Serial.print(alarmes[0].horario_inicial );
      Serial.print(":");
      Serial.println(alarmes[0].minutos_inicial );
      Serial.println(alarmes[0].freq );
  }
  lastbotao= botao;
}
void deletar_2(){
    int botao = digitalRead(in1);
    int botao2 = digitalRead(in2);
  if(botao == 1 && lastbotao == 0){
    alarmes[1].horario_inicial = 0;
    alarmes[1].minutos_inicial = 0;
    alarmes[1].freq = 0;
      Serial.println("deletado alarme2");
  }
  lastbotao= botao;
}
void deletar_3(){
    int botao = digitalRead(in1);
    int botao2 = digitalRead(in2);
  if(botao == 1 && lastbotao == 0){
    alarmes[2].horario_inicial = 0;
    alarmes[2].minutos_inicial = 0;
    alarmes[2].freq = 0;
      Serial.println("deletado alarme3");
  }
  lastbotao= botao;
}

void deletar_4(){
    int botao = digitalRead(in1);
    int botao2 = digitalRead(in2);
  if(botao == 1 && lastbotao == 0){
    alarmes[3].horario_inicial = 0;
    alarmes[3].minutos_inicial = 0;
    alarmes[3].freq = 0;
   Serial.println("deletado alarme4");
  }
  lastbotao= botao;
}

void minuto_inicial(){
 encoder.tick();
    
  int newPos = encoder.getPosition();
      if (newPos < 0) {
        encoder.setPosition(0);
        newPos = 0;
    
      } else if (newPos > 59) {
        encoder.setPosition(59);
        newPos = 59;
      } 
    
  if (lastPos != newPos) {
    switch(Compartimento){
          case 1:
          alarmes[0].minutos_inicial = newPos;
          break; 
          case 2:
          alarmes[1].minutos_inicial = newPos;
          break;
          case 3:
          alarmes[2].minutos_inicial = newPos;
          break;
          case 4:
          alarmes[3].minutos_inicial = newPos;
         break;
       }
         Serial.print("minuto incial = ");
         Serial.println(newPos);
             lastPos = newPos;
     }
}

void horario_inicial(){
   encoder.tick();
  int newPos = encoder.getPosition();
      if (newPos < 0) {
        encoder.setPosition(0);
        newPos = 0;
    
      } else if (newPos > 24) {
        encoder.setPosition(24);
        newPos = 24;
      } 
    
  if (lastPos != newPos) {
       switch(Compartimento){
            case 1:
            alarmes[0].horario_inicial = newPos;
            break; 
            case 2:
            alarmes[1].horario_inicial = newPos;
            break;
            case 3:
            alarmes[2].horario_inicial = newPos;
            break;
            case 4:
            alarmes[3].horario_inicial = newPos;
           break;
       }
       Serial.print("horario inicial = ");
     Serial.println(newPos);
     lastPos = newPos;
     }
}

void frequencia(){
       encoder.tick();
  int newPos = encoder.getPosition();
      if (newPos < 1) {
        encoder.setPosition(1);
        newPos = 1;
    
      } else if (newPos > 168) {
        encoder.setPosition(168);
        newPos = 168;
      } 
      if (lastPos != newPos) {
        switch(Compartimento){
        case 1:
        alarmes[0].freq = newPos;
        break; 
        case 2:
        alarmes[1].freq = newPos;
        break;
        case 3:
        alarmes[2].freq = newPos;
        break;
        case 4:
        alarmes[3].freq = newPos;
       break;
      }
      Serial.print("Frequencia = ");
         Serial.println(newPos);
        lastPos = newPos;
         }   
}

void giro_compartimento(){
   encoder.tick();
  int newPos = encoder.getPosition();
      if (newPos < 1) {
        encoder.setPosition(1);
        newPos = 1;
    
      } else if (newPos > 4) {
        encoder.setPosition(4);
        newPos = 4;
      } 
  if (lastPos != newPos) {
            Compartimento = newPos;
            Serial.print("Compartimento = ");
            Serial.println(Compartimento);
            lastPos = newPos;
     }
}
