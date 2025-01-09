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

#define MAXBRIGHT 240
#define DELAY 50
#define STEPS 16
#define ARMS 5
#define FADE (MAXBRIGHT / STEPS)
#define SPINREPEAT 4
#define GLOWREPEAT 4

int pins[] = {3, 5, 6, 9, 10};
uint8_t value[] = {0, 0, 0, 0, 0};
uint8_t target[] = {0, 0, 0, 0, 0};

// the setup routine runs once when you press reset:
void setup()
{
}

uint8_t converge(uint8_t v, uint8_t t) {
  if (v > t) {
    if (v - t > FADE) {
      return v - FADE;
    } else {
      return t;
    }
  } else {
    if (t - v > FADE) {
      return v + FADE;
    } else {
      return t;
    }
  }
}

void show() {
  for (int a = 0; a < ARMS; a++) {
    if (value[a] != target[a]) {
      value[a] = converge(value[a], target[a]);
      analogWrite(pins[a], value[a]);
    }
  }
}

void spin() {
  for (int rep = 0; rep < SPINREPEAT; rep++)
  {
    for (int rise = 0; rise < ARMS; rise++)
    {
      target[rise] = MAXBRIGHT;
      int fall = (rise + ARMS - 2) % ARMS;
      target[fall] = 0;
      for (int s = 0; s <= STEPS/8; s++)
      {
        show();
        delay(DELAY);
      }
    }
  }

}

void pulse() {
  for (int rep = 0; rep < GLOWREPEAT; rep++)
  {
    uint8_t val = 0;
    for (int s = 0; s <= STEPS; s++)
    {
      for (int a = 0; a < ARMS; a++)
      {

        target[a] = val;
      }
      show();
      val += FADE;
      delay(DELAY);
    }
    for (int s = 0; s <= STEPS; s++)
    {
      for (int a = 0; a < ARMS; a++)
      {

        target[a] = val;
      }
      show();
      val -= FADE;
      delay(DELAY);
    }
  }

}

void bounce() {
  for (int rep=0; rep < GLOWREPEAT; rep++) {
    for (int a=0; a<ARMS; a++) {
      value[a]=MAXBRIGHT;
      target[a]=MAXBRIGHT;
      analogWrite(pins[a], value[a]);
      show();
      delay(DELAY);
      show();
      delay(DELAY);
      target[a]=0;
    }
    for (int a=ARMS-1; a>-1; a--) {
      value[a]=MAXBRIGHT;
      target[a]=MAXBRIGHT;
      analogWrite(pins[a], value[a]);
      for (int s=0; s<STEPS/4; s++) {
        show();
        delay(DELAY);
      }
      target[a]=0;
    }
  }
}


// the loop routine runs over and over again forever:
void loop()
{
  spin();
  pulse();
  bounce();
}
