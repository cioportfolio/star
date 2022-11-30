/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

#define MAXBRIGHT 128
#define DELAY 50
#define STEPS 16
#define ARMS 5
#define FADE (MAXBRIGHT / STEPS)
#define SPINREPEAT 4
#define GLOWREPEAT 4

int pins[] = {3, 5, 6, 9, 10};
uint8_t value[] = {0, 0, 0, 0, 0};

// the setup routine runs once when you press reset:
void setup()
{
}

// the loop routine runs over and over again forever:
void loop()
{
  for (int rep = 0; rep < SPINREPEAT; rep++)
  {
    for (int rise = 0; rise < ARMS; rise++)
    {
      value[rise] = 0;
      int fall = (rise + ARMS - 2) % ARMS;
      value[fall] = MAXBRIGHT;
      for (int s = 0; s <= STEPS; s++)
      {
        analogWrite(pins[rise], value[rise]);
        analogWrite(pins[fall], value[fall]);
        value[rise] += FADE;
        value[fall] -= FADE;
        delay(DELAY);
      }
    }
  }
  for (int rep = 0; rep < GLOWREPEAT; rep++)
  {
    uint8_t val = 0;
    for (int s = 0; s <= STEPS; s++)
    {
      for (int a = 0; a < ARMS; a++)
      {

        analogWrite(pins[a], val);
      }
      val += FADE;
      delay(DELAY);
    }
    for (int s = 0; s <= STEPS; s++)
    {
      for (int a = 0; a < ARMS; a++)
      {

        analogWrite(pins[a], val);
      }
      val -= FADE;
      delay(DELAY);
    }
  }
}
