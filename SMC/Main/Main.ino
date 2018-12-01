//Entrada de dados
#include "RTClib.h"//Biblioteca do DS1307
#include <RotaryEncoder.h>
#include <Wire.h>//Para comunicação I2C

RotaryEncoder encoder(4, 16);
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif
RTC_DS1307 rtc, hor_X;

int qdr = 0;
int lastPos = -1;
int lastbotao;
int lastbotao2;
int Compartimento;

struct Dados {
  int horario_inicial;
  int minutos_inicial;
  int freq;
};

struct Dados alarmes[4];

//Entradas
#define B_REM_OK  12                      //Botão Confirma de remedio ligado as pino D13
#define  in1  13  //mudar pra 3
#define  in2  4

//Saidas
int Leds[4] = {26, 25, 33, 32};        //Leds dos compartimento 1,2,3 e 4 ligados aos pino D26,D25,D33,D32 respectivamentes
#define pinBuzzer 14

//Configura algumas variáveis utilizadas em Gerenciador de Alarme
int Hora_In1[2];
int Hora_In2[2];
int Hora_In3[2];
int Hora_In4[2];
int C_Leds[4] = {0, 0, 0, 0};         //Flag para ligar os LEDS
int Cfreq[4];
int Chorario_inicial[4][3];
int horario_referencia[4];
int n[4] = {0, 0, 0, 0};
int Hora_x[4];
int Minuto_x[4];
int A_1 = 0;
int A_2 = 1;
int A_3 = 2;
int A_4 = 3;
int flag_compA = 0;                      //flag_comp=1 Hora_x=Hora_Atual e Minuto_x=Minuto_Atual, flag_comp=0 CC
int flag_Des = 0;                        //flag_comp=1 Hora_x=Hora_Atual e Minuto_x=Minuto_Atual, flag_comp=0 CC
int Ac_LED[4] = {0, 0, 0, 0};           // Guardar o valor do led até o botão de confirmar o remedio ser apertado REMO_K
int LED_Des[4] = {0, 0, 0, 0};          // Guardar o valor do led para descanso
int T_Desc[4]={-1};
int T_Alar=-1;

char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

void setup() {
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  Serial.begin(9600);
  Serial.println("Encoder");
  lastbotao = digitalRead(in1);
  lastbotao2 = digitalRead(in2);
  pinMode(B_REM_OK, INPUT); //Definindo pino digital 13 como Botão de confirmação de toma de remédio
      digitalWrite(B_REM_OK, LOW);
  encoder.setPosition(0);

  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, LOW);

  pinMode(Leds[A_1], OUTPUT); //Definindo pino digital 33 como de saída.
  pinMode(Leds[A_2], OUTPUT); //Definindo pino digital 32 como de saída.
  pinMode(Leds[A_3], OUTPUT); //Definindo pino digital 35 como de saída.
  pinMode(Leds[A_4], OUTPUT); //Definindo pino digital 34 como de saída.


#ifndef ESP32
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("RTC não encontrado");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC não está funcionando!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2018, 11, 14, 11, 29, 0));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//Atualiza a data e hora
}


void loop() {
  // put your main code here, to run repeatedly:
  menu();

  //Horário atual no DS1307
  DateTime now = rtc.now();
 
  //FUNÇÕES CHAMADAS E ATIVADAS

    alarmes[0].horario_inicial=20;
    alarmes[0].minutos_inicial=44;
    alarmes[1].horario_inicial=20 ;
    alarmes[1].minutos_inicial=45;
    alarmes[2].horario_inicial=16 ;
    alarmes[2].minutos_inicial=52;
    alarmes[3].horario_inicial=16 ;
    alarmes[3].minutos_inicial=53;

  
      Hora_In1[0]=alarmes[0].horario_inicial;
      Hora_In1[1]=alarmes[0].minutos_inicial;
  GerenciadorAlarme(Hora_In1,alarmes[0].freq, A_1);
      
      Hora_In2[0]=alarmes[1].horario_inicial;
      Hora_In2[1]=alarmes[1].minutos_inicial;
  GerenciadorAlarme(Hora_In2,alarmes[1].freq, A_2);
  
      Hora_In3[0]=alarmes[2].horario_inicial;
      Hora_In3[1]=alarmes[2].minutos_inicial;
  GerenciadorAlarme(Hora_In3,alarmes[2].freq, A_3);
  
      Hora_In4[0]=alarmes[3].horario_inicial;
      Hora_In4[1]=alarmes[3].minutos_inicial;
  GerenciadorAlarme(Hora_In4,alarmes[3].freq, A_4);
  Gerenciador_LED();
  Descanso();

  //Mostrar o Serial Monitor

/*
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.print("flag= ");
  Serial.println(flag_Des);
  Serial.print("T_Alar= ");
  Serial.println(T_Alar);
  Serial.print("Descanso= ");
  Serial.println(flag_Des);

  */
  

}
