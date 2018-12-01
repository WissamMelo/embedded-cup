void serial(){
  Serial.print("qdr = " );
  Serial.println(qdr);
}

void menu(){
  int botao = digitalRead(in1);
  int botao2 = digitalRead(in2);
  
  switch(qdr){
  case 0: //MENU
          if(botao == 1 && lastbotao == 0){
            qdr = 1;     
            serial();    
            delay(100); 
          }
          lastbotao= botao;
  break;
  case 1: //ALARME
          giro_2();
          if(botao == 1 && lastbotao == 0){
            qdr = 3; 
            serial();  
            delay(100); 
          } 
          if(botao2 == 1 && lastbotao2 == 0){
            qdr = 0 ;
            serial();  
            delay(100);
          }
          lastbotao = botao;
          lastbotao2 = botao2;
  break;
  case 2: //WIFI
          giro_2();
          if(botao ==1 && lastbotao == 0 ){
            qdr = 6;
            serial();  
            delay(100);
          }
          if(botao2 == 1 && lastbotao2 == 0){
            qdr = 0 ;
            serial();
            delay(100);  
          }
        lastbotao= botao;
        lastbotao2 = botao2;
  break;
  case 3: //ALARMES DEFINIDOS
        giro_3(); 
        if(botao == 1 && lastbotao == 0){
          qdr = 9;  
          serial(); 
          delay(100);
        }
        if(botao2 == 1 && lastbotao2 == 0){
            qdr = 1 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 4: //DELETAR
        giro_3();
        if(botao == 1 && lastbotao == 0){
          qdr = 13;
          serial(); 
          delay(100);
        }
        if(botao2 == 1 && lastbotao2 == 0){
            qdr = 1 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 5: //CADASTRO
        giro_3(); 
        if(botao == 1 && lastbotao == 0){
          qdr = 17;   
          serial(); 
          delay(100);     
        }
        if(botao2 == 1 && lastbotao2 == 0){
            qdr = 1 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 6: //START_AP
        giro_3();
          if(botao2 == 1 && lastbotao2 == 0){
            qdr = 2 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
  break;
  case 7: //REDES_CONHECIDAS
         giro_3();
           if(botao2 == 1 && lastbotao2 == 0){
            qdr = 2 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
  break;
  case 8: //SINAL_MANUAL
         giro_3();
           if(botao2 == 1 && lastbotao2 == 0){
            qdr = 2 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
  break;
  case 9: //ALARME1
        giro_4();
          if(botao2 == 1 && lastbotao2 == 0){
            qdr = 3 ;
            serial();
            delay(100); 
              
          }
          lastbotao2 = botao2;
  break;
  case 10:  //ALARME2
        giro_4();            
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 3 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        
  break;
  case 11:  //ALARME3
        giro_4();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 3 ;
            serial();
            delay(100);          
          }
          lastbotao2 = botao2;
  break;
  case 12:  //ALARME4
        giro_4();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 3 ;
            serial(); 
           delay(100);
          }
          lastbotao2 = botao2;
  break;
  case 13:  //ALARME1 -- OPÇÃO DE DELETAR
         giro_4();
        deletar_1();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 4 ;
            serial();
            delay(100); 
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 14:  //ALARME2 -- OPÇÃO DE DELETAR
         giro_4();
         deletar_2();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 4 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 15:  //ALARME3 -- OPÇÃO DE DELETAR
        giro_4();
        deletar_3();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 4 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 16:  //ALARME4 -- OPÇÃO DE DELETAR
        giro_4();
          deletar_4();
         if(botao2 == 1 && lastbotao2 == 0){
            qdr = 4 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
        lastbotao= botao;
  break;
  case 17:  //COMPARTIMENTO
   giro_compartimento();
    if(botao == 1 && lastbotao == 0){
      qdr = 18;
      serial(); 
      delay(100);
    }
     if(botao2 == 1 && lastbotao2 == 0){
            qdr = 5 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
          lastbotao= botao;
   break;
  case 18:  //FREQUÊNCIA(SOMENTE EM HORAS)
    frequencia();
    if(botao == 1 && lastbotao == 0){
      qdr = 19;
      serial(); 
      delay(100);
    }
    if(botao2 == 1 && lastbotao2 == 0){
            qdr = 17 ;
            serial(); 
            delay(100);
          }
    lastbotao2 = botao2;
    lastbotao= botao;
  break;
  case 19:  //HORA_INICIAL
  horario_inicial();
    if(botao == 1 && lastbotao == 0){
      qdr = 20;
      serial(); 
      delay(100);
    }
    if(botao2 == 1 && lastbotao2 == 0){
            qdr = 18 ;
            serial(); 
            delay(100);
          }
          lastbotao2 = botao2;
    lastbotao= botao;
  break;
  case 20:  //MINUTO_INICIAL
    minuto_inicial();
    if(botao == 1 && lastbotao == 0){
      qdr = 5;
      serial(); 
      delay(100);
    }
    if(botao2 == 1 && lastbotao2 == 0){
            qdr = 19 ;
            serial(); 
            delay(100);
      }
          lastbotao2 = botao2;
          lastbotao= botao;
  break;
 }
}
