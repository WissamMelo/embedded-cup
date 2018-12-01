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

int in1 = 3;
int in2 = 4;
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
int B_REM_OK = 13;                      //Botão Confirma de remedio ligado as pino D13
int B_Copo = 12;                       //Botão do compartimento ligado as pino D12: B_Copo=0 Compartimento Aberto, B_Copo=1 CC
const int reset = 14;                 //Botão reset para acionar o modo descanso, ligado as pino D14

//Saidas
int Leds[4] = {26, 25, 33, 32};        //Leds dos compartimento 1,2,3 e 4 ligados aos pino D26,D25,D33,D32 respectivamentes

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
int Ac_LED[4] = {0, 0, 0, 0};         // Guardar o valor do led até o botão de confirmar o remedio ser apertado REMO_K

char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
int flag_comp = 0;
int descanso;

void setup() {
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  Serial.begin(9600);
  Serial.println("Encoder");
  lastbotao = digitalRead(in1);
  lastbotao2 = digitalRead(in2);
  encoder.setPosition(0);

  pinMode(Leds[A_1], OUTPUT); //Definindo pino digital 33 como de saída.
  pinMode(Leds[A_2], OUTPUT); //Definindo pino digital 32 como de saída.
  pinMode(Leds[A_3], OUTPUT); //Definindo pino digital 35 como de saída.
  pinMode(Leds[A_4], OUTPUT); //Definindo pino digital 34 como de saída.
  pinMode(B_Copo, INPUT_PULLUP);   //Definindo pino digital 12 como de entrada.
  pinMode(B_REM_OK, INPUT_PULLUP); //Definindo pino digital 13 como de entrada.


  pinMode(reset, INPUT_PULLUP); //Pino do botão descanso de entrada

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
  //Alocando o estado que a ESP32 vai ler no botão reset e mostrar
  descanso = digitalRead(reset);

  //Horário atual no DS1307
  DateTime now = rtc.now();
 
  //FUNÇÕES CHAMADAS E ATIVADAS

  
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
  */
  

}
