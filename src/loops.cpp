
#include "settings.h"

// variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne = 1;

extern void verificaddisparo();
extern void sendSensorAndBateryValues();

void sendSensorAndBatery(void *pvParameters);
void gasbloqueado(void *pvParameters);
void verificagas(void *pvParameters);
void timer(void *pvParameters);

void timerOff(void *pvParameters);

void setLoops()
{
  Serial.println("start loops");
  xTaskCreatePinnedToCore(
      sendSensorAndBatery,   /* função que implementa a tarefa */
      "sendSensorAndBatery", /* nome da tarefa */
      10000,                 /* número de palavras a serem alocadas para uso com a pilha da tarefa */
      NULL,                  /* parâmetro de entrada para a tarefa (pode ser NULL) */
      0,                     /* prioridade da tarefa (0 a N) */
      NULL,                  /* referência para a tarefa (pode ser NULL) */
      taskCoreZero);         /* Núcleo que executará a tarefa */
  delay(2000);               // tempo para a tarefa iniciar

  Serial.println("start loops2");
  xTaskCreatePinnedToCore(verificagas, "verificagas", 10000, NULL, 1, NULL, taskCoreZero);
  delay(2000);

  Serial.println("start loops3");
  xTaskCreatePinnedToCore(gasbloqueado, "gasbloqueado", 1000, NULL, 1, NULL, taskCoreOne);
  delay(2000);

  Serial.println("start loops4");
  xTaskCreatePinnedToCore(timer, "timer", 1000, NULL, 1, NULL, taskCoreOne);
  delay(2000);
  Serial.println("start loops5");

  xTaskCreatePinnedToCore(timerOff, "timerOff", 1000, NULL, 1, NULL, taskCoreOne);
  delay(2000);
}

// --------------------- loops --------------

void timer(void *pvParameters)
{
  while (true)
  {
    timerr += 1;
    // Serial.println(timerr);
    delay(1000);
  }
}
void verificagas(void *pvParameters)
{
  while (true)
  {
    verificaddisparo();
    delay(500);
  }
}
void sendSensorAndBatery(void *pvParameters)
{
  while (true)
  {
    sendSensorAndBateryValues();
  }
}
void gasbloqueado(void *pvParameters)
{
  while (true)
  {
    if (gasblok == true && bloqueado == false)
    {
      // digitalWrite(ledFogo, HIGH);
      // digitalWrite(solenoide, sHIGH);
      delay(500);
      // digitalWrite(solenoide, sLOW);
      bloqueado = true;
      timerr = 0;
    }
    else if (bloqueado == true && timerr == 15)
    {
      // digitalWrite(ledFogo, HIGH);
      // digitalWrite(solenoide, sHIGH);
      delay(500);
      // digitalWrite(solenoide, sLOW);
      timerr = 0;
    }
    else if (gasblok == false && bloqueado == true)
    {
      bloqueado = false;
      // digitalWrite(ledFogo, LOW);
    }
  }
}

void timerOff(void *pvParameters)
{
  while (true)
  {
    if (offline)
    {
      if (timerOffline == 30 * 60)
      {
        gasblok = true;
      }
      timerOffline++;
      delay(1000);
    }
    else if (timerOffline != 0)
    {
      timerOffline = 0;
    }
  }
}
