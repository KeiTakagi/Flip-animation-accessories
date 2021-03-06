/*

   @file Flip_animation_accessories.ino
   @brief 8 x 8 LED Matrix animation using Arduino.
   @author Kei Takagi
   @date 2016.5.1

   8 x 8 Led Matrix ... 2-17 pin
   Button Input     ... A4 pin
   VCC              ... A5 pin

   Copyright (c) 2016 Kei dTakagi
   Revfleased under the MIT license
   http://opensource.org/licenses/mit-license.php

*/

#include <MsTimer2.h>
#define FallVelocity 80
#define AnimeMax 8

// 8 x 8 matrix LED
// ROW side cathode , COLOMN side of the anode
byte pins[17] = /*Arduino*/ { -1, 9, 8, 7, 6, 5, 4, 3, 2, 17, 16, 15, 14, 13, 12, 11, 10};
const static byte cols[8] = {pins[13], pins[ 3], pins[ 4], pins[10], pins[ 6], pins[11], pins[15], pins[16]};
const static byte rows[8] = {pins[ 9], pins[14], pins[ 8], pins[12], pins[ 1], pins[ 7], pins[ 2], pins[ 5]};

int anime_no = 0;
int button = 0;
int anime_frame = 0;
int cat = 0;
int ano = 0;
unsigned long time;
byte *layer;

byte anime[8][6][AnimeMax] = {{{
      0b00000000,
      0b00000000,
      0b00100100,
      0b00111100,
      0b00111100,
      0b00011000,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b01100110,
      0b01111110,
      0b01111110,
      0b01111110,
      0b00111100,
      0b00011000,
      0b00000000,
    }, {
      0b01100110,
      0b11111111,
      0b11111111,
      0b11111111,
      0b11111111,
      0b01111110,
      0b00111100,
      0b00011000,
    }, {
      0b00000000,
      0b01100110,
      0b01111110,
      0b01111110,
      0b01111110,
      0b00111100,
      0b00011000,
      0b00000000,
    }, {
      0b00000000,
      0b00000000,
      0b00100100,
      0b00111100,
      0b00111100,
      0b00011000,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00011000,
      0b00011000,
      0b00000000,
      0b00000000,
      0b00000000,
    }
  }, {{
      0b00011000,
      0b00011000,
      0b00010000,
      0b11011011,
      0b11111111,
      0b00001000,
      0b00011000,
      0b00011000,
    }, {
      0b00001100,
      0b00001100,
      0b11001000,
      0b11111000,
      0b00011111,
      0b00010011,
      0b00110000,
      0b00110000,
    }, {
      0b00000110,
      0b11000110,
      0b11100100,
      0b00011000,
      0b00011000,
      0b00100111,
      0b01100011,
      0b01100000,
    }, {
      0b11000011,
      0b11000011,
      0b00100100,
      0b00011000,
      0b00011000,
      0b00100100,
      0b11000011,
      0b11000011,
    }, {
      0b01100000,
      0b01100011,
      0b00100111,
      0b00011000,
      0b00011000,
      0b11100100,
      0b11000110,
      0b00000110,
    }, {
      0b00110000,
      0b00110000,
      0b00010011,
      0b00011111,
      0b11111000,
      0b11001000,
      0b00001100,
      0b00001100,
    }
  }, {{
      0b00000001,
      0b00000001,
      0b00000011,
      0b00000010,
      0b11111100,
      0b00000000,
      0b00000000,
      0b00000000,
    }, {
      0b00000100,
      0b00000100,
      0b00001100,
      0b00001010,
      0b11110010,
      0b00000010,
      0b00000001,
      0b00000001,
    }, {
      0b00010000,
      0b00010000,
      0b00110000,
      0b00101000,
      0b11001001,
      0b00001010,
      0b00000100,
      0b00000100,
    }, {
      0b01000000,
      0b01000000,
      0b11000000,
      0b10100000,
      0b00100111,
      0b00101000,
      0b00010000,
      0b00010000,
    }, {
      0b00000000,
      0b00000000,
      0b00000000,
      0b10000000,
      0b10011111,
      0b10100000,
      0b01000000,
      0b01000000,
    }, {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b01111111,
      0b10000000,
      0b00000000,
      0b00000000,
    }
  }, {{
      0b00000000,
      0b01100110,
      0b01100110,
      0b00000000,
      0b01111110,
      0b01000010,
      0b01000010,
      0b00111100,
    }, {
      0b00000000,
      0b00100100,
      0b01100110,
      0b00000000,
      0b00111100,
      0b01000010,
      0b00111100,
      0b00000000,
    }, {
      0b00000000,
      0b01100110,
      0b01100110,
      0b00000000,
      0b00111100,
      0b01000010,
      0b00111100,
      0b00000000,
    }, {
      0b00000000,
      0b01100110,
      0b01100110,
      0b00011000,
      0b00100100,
      0b00100100,
      0b00100100,
      0b00011000,
    }, {
      0b00000000,
      0b01100110,
      0b01100110,
      0b00000000,
      0b00000000,
      0b00011000,
      0b00100100,
      0b00011000,
    }, {
      0b00000000,
      0b01100110,
      0b01100110,
      0b00000000,
      0b00000000,
      0b01111110,
      0b00000000,
      0b00000000,
    }
  }, {{
      0b00101000,
      0b00010010,
      0b10010000,
      0b00011001,
      0b10011000,
      0b00000001,
      0b01000000,
      0b00010100,
    }, {
      0b00010100,
      0b01000000,
      0b01000001,
      0b10111000,
      0b00011001,
      0b10000000,
      0b00000010,
      0b00101000,
    }, {
      0b00101000,
      0b00000010,
      0b10000000,
      0b00011001,
      0b10011000,
      0b00100001,
      0b01100000,
      0b00010100,
    }, {
      0b00010100,
      0b01000000,
      0b00000001,
      0b10011000,
      0b00011001,
      0b10001000,
      0b0000110,
      0b00101000,
    }, {
      0b00101000,
      0b00000010,
      0b10000000,
      0b00011001,
      0b10011000,
      0b00000111,
      0b01000000,
      0b00010100,
    }, {
      0b00010100,
      0b01000000,
      0b00000011,
      0b10011100,
      0b00011001,
      0b10000000,
      0b0000010,
      0b00101000,
    }
  }, {{
      0b00000000,
      0b00000000,
      0b00000000,
      0b00011000,
      0b00011000,
      0b00000000,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b00000000,
      0b00011000,
      0b00100100,
      0b00100100,
      0b00011000,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b00011000,
      0b00100100,
      0b01000010,
      0b01000010,
      0b00100100,
      0b00011000,
      0b00000000,
    }, {
      0b00111100,
      0b01000010,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b01000010,
      0b00111100,
    }, {
      0b10000001,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b10000001,
    }, {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
    }
  }, {{
      0b11111111,
      0b10000001,
      0b10000001,
      0b10011001,
      0b10011001,
      0b10000001,
      0b10000001,
      0b11111111,
    }, {
      0b00000000,
      0b00000000,
      0b00111100,
      0b00100100,
      0b00100100,
      0b00111100,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b01111110,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01111110,
      0b00000000,
    }, {
      0b11111111,
      0b10000001,
      0b10000001,
      0b10011001,
      0b10011001,
      0b10000001,
      0b10000001,
      0b11111111,
    }, {
      0b00000000,
      0b00000000,
      0b00111100,
      0b00100100,
      0b00100100,
      0b00111100,
      0b00000000,
      0b00000000,
    }, {
      0b00000000,
      0b01111110,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01111110,
      0b00000000,
    }
  }, {{
      0b01010110,
      0b10101001,
      0b10101001,
      0b01100110,
      0b01100110,
      0b10011001,
      0b10011001,
      0b01100110,
    }, {
      0b01101001,
      0b01101001,
      0b10010110,
      0b10010110,
      0b01101001,
      0b01101001,
      0b10010110,
      0b10010110,
    }, {
      0b10011001,
      0b01100110,
      0b01100110,
      0b10011001,
      0b10011001,
      0b01100110,
      0b01100110,
      0b10011001,
    }, {
      0b10010110,
      0b10010110,
      0b01101001,
      0b01101001,
      0b10010110,
      0b10010110,
      0b01101001,
      0b01101001,
    }, {
      0b11111111,
      0b10011001,
      0b10011001,
      0b11100111,
      0b11100111,
      0b10011001,
      0b10011001,
      0b11111111,
    }, {
      0b11111111,
      0b11000011,
      0b10100101,
      0b10011001,
      0b10011001,
      0b10100101,
      0b11000011,
      0b11111111,
    }
  }
};

void setup()
{
  for ( int cat = 0; cat < 8; cat++ ) {
    pinMode( rows[cat], OUTPUT );
    digitalWrite( rows[cat], HIGH );
  }
  for ( int ano = 0; ano < 8; ano++ ) {
    pinMode( cols[ano], OUTPUT );
    digitalWrite( cols[ano], LOW );
  }

  pinMode(A4, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);

  MsTimer2::set(1, display);
  MsTimer2::start();

  time = millis() +  FallVelocity;

}

void loop()
{
  if (time < millis()) {
    time = millis() +  FallVelocity;
    if (digitalRead(A4) == 0) {
      button < 13 ? button++ : button = 0;
      anime_frame = 0;
    }
    switch (button) {
      case 0:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 0;
        break;
      case 1:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 1;
        break;
      case 2:
        anime_frame > 0 ? anime_frame-- : anime_frame = 5;
        anime_no = 1;
        break;
      case 3:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 2;
        break;
      case 4:
        anime_frame > 0 ? anime_frame-- : anime_frame = 5;
        anime_no = 2;
        break;
      case 5:
        anime_frame = random(0, 6);
        anime_no = 3;
        break;
      case 6:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 4;
        break;
      case 7:
        anime_frame > 0 ? anime_frame-- : anime_frame = 5;
        anime_no = 4;
        break;
      case 8:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 5;
        break;
      case 9:
        anime_frame > 0 ? anime_frame-- : anime_frame = 5;
        anime_no = 5;
        break;
      case 10:
        anime_frame < 5 ? anime_frame++ : anime_frame = 0;
        anime_no = 6;
        break;
      case 11:
        anime_frame > 0 ? anime_frame-- : anime_frame = 5;
        anime_no = 6;
        break;
      case 12:
        anime_frame < 3 ? anime_frame++ : anime_frame = 0;
        anime_no = 7;
        break;
      case 13:
        anime_frame > 0 ? anime_frame-- : anime_frame = 3;
        anime_no = 7;
        break;
    }
    layer = anime[anime_no % AnimeMax][anime_frame];
  }
}

void display()
{
  cat < 7 ? cat++ :  cat = 0;
  digitalWrite( *(rows + cat), LOW );
  for ( ano = 0; ano < 8; ano++ ) {
    digitalWrite( *(cols + ano) , (*(layer + cat) >> ano ) & 0x01 );
    delayMicroseconds(50);
    digitalWrite( *(cols + ano), LOW );
  }
  digitalWrite( *(rows + cat), HIGH );
}

