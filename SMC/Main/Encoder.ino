void giro_2(){
    encoder.tick();
    int newPos = encoder.getPosition();

      if (newPos < 1) {
        encoder.setPosition(1);
        newPos = 1;
    
      } else if (newPos > 2){
        encoder.setPosition(2);
        newPos = 2;
      } // if
       if (lastPos != newPos) {
     if(newPos == 1 ){
            qdr = 1;
            serial(); 
          }
        else if( newPos == 2 ){
            qdr = 2;
            serial(); 
          }
     Serial.print(newPos);
    Serial.println();
    lastPos = newPos;
    
     }
      
      
      
}

void giro_3(){
    encoder.tick();
    int newPos = encoder.getPosition();
      if (newPos < 1) {
        encoder.setPosition(1);
        newPos = 1;
    
      } else if (newPos > 3) {
        encoder.setPosition(3);
        newPos = 3;
      } 
         if (lastPos != newPos) {
           if(qdr == 3 || qdr == 4 || qdr == 5){
          switch(newPos){
          case 1:
          qdr = 3;
          serial(); 
          break;
          case 2:
          qdr = 4;
          serial(); 
          break;
          case 3:
          qdr = 5;
          serial(); 
          break;
        }
    }
    if(qdr == 6 || qdr == 7 || qdr == 8){
        switch(newPos){
          case 1:
          qdr = 6;
          serial(); 
          break;
          case 2:
          qdr = 7;
          serial(); 
          break;
          case 3:
          qdr = 8;
          serial(); 
          break;
        }
    }

    lastPos = newPos;
     }

   
}


void giro_4(){
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
        if(qdr == 9 || qdr == 10 || qdr == 11 || qdr == 12 ){
            switch(newPos){
          case 1:
          qdr = 9;
            Serial.println("Dados Alarme 1");
            Serial.print(alarmes[0].horario_inicial);
            Serial.print(":");
            Serial.println(alarmes[0].minutos_inicial );
            Serial.println(alarmes[0].freq );
          serial(); 
          break;
          case 2:
            Serial.println("Dados Alarme 2");
            Serial.print(alarmes[1].horario_inicial );
            Serial.print(":");
            Serial.println(alarmes[1].minutos_inicial );
            Serial.println(alarmes[1].freq );
          qdr = 10;
          serial(); 
          break;
          case 3:
            Serial.println("Dados Alarme 3");
            Serial.print(alarmes[2].horario_inicial );
            Serial.print(":");
            Serial.println(alarmes[2].minutos_inicial );
            Serial.println(alarmes[2].freq );
          qdr = 11;
          serial(); 
          break;
          case 4:
            Serial.println("Dados Alarme 4");
            Serial.print(alarmes[3].horario_inicial );
            Serial.print(":");
            Serial.println(alarmes[3].minutos_inicial );
            Serial.println(alarmes[3].freq );
          qdr = 12;
          serial(); 
          break;
        }
    }

    if(qdr == 13 || qdr == 14 || qdr == 15 || qdr == 16){
           switch(newPos){
          case 1:
          qdr = 13;
          serial(); 
          break;
          case 2:
          qdr = 14;
          serial(); 
          break;
          case 3:
          qdr = 15;
          serial(); 
          break;
          case 4:
          qdr = 16;
          serial(); 
          break;
        }
    }

    lastPos = newPos;
     }
  
}
