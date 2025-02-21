//Name: Real time alarm clock with tasks.
//Aurthor: Adam Clarke te23a.
//Date: 2025-01-14.

#include "U8glib.h"                             //Inkluderar U8g bibiloteket
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

#include <RTClib.h>  // Inkluderar bibilotektet för klockan
#include <Wire.h>    //Inkluderar någonting

RTC_DS3231 rtc;

void setup() {
  u8g.setFont(u8g_font_unifont);
  Serial.begin(9600);
  
  
  
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
void loop() {
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  unsigned long currenttime = millis();
  int savedmillistime;
  int timestampfortask1[3] = {0};
  int timestampfortask2 = 0;
  int timestampfortask3 = 0;
  int timestampfortask4 = 0;
  int timestampfortask5 = 0;
  bool answer1recieved = false;
  bool answer2recieved = false;
  bool answer3recieved = false;
  bool answer4recieved = false;
  bool answer5recieved = false;
  bool clockstarted = false;
  bool alltasksdone = false;
  String answer1;
  String answer2;
  String answer3;
  String answer4;
  String answer5;
  int number = 0;
  int iv2 = 0;

  while (clockstarted == false) {

    if (digitalRead(7) == HIGH) {
      clockstarted = true;
      Serial.println("Button has been pressed");
    }
  }
  delay(1000);
  while (digitalRead(7) == false) {
    int ycord = 22;
    int xcord = 0;
    int UpdateCooldownForLoop = 100;
    while (digitalRead(7) == false) {
      for (int i = 1; i <= 20; i++) {
        ycord++;
        draw(xcord, ycord, "Press Any Button To Start");
        delay(UpdateCooldownForLoop);
      }
      for (int i = 1; i <= 20; i++) {
        ycord--;
        draw(xcord, ycord, "Press Any Button To Start");
        delay(UpdateCooldownForLoop);
      }
    }
  }
  delay(1000);
  int ViewTime = 2000;
  while (answer1recieved == false || answer2recieved == false || answer3recieved == false || answer4recieved == false || answer5recieved == false) {
    while (answer1recieved == false) {
      if (Serial.available() > 0) {
        answer1 = Serial.readString();
        drawlist(0, 10, String(answer1), "Insert Second Task Name", "Insert Third Task Name", "Insert Fourth Task Name", "Insert Fith Task Name");
        answer1recieved = true;
        
      } else {
        drawlist(0, 10, "Insert First Task Name", "Insert Second Task Name", "Insert Third Task Name", "Insert Fourth Task Name", "Insert Fith Task Name");
      }
    }
    delay(ViewTime);
    while (answer2recieved == false) {
      if (Serial.available() > 0) {
        answer2 = Serial.readString();
        drawlist(0, 10, String(answer1), String(answer2), "Insert Third Task Name", "Insert Fourth Task Name", "Insert Fith Task Name");
        delay(ViewTime);
        answer2recieved = true;
      } else {
        drawlist(0, 10, String(answer1), "Insert Second Task Name", "Insert Third Task Name", "Insert Fourth Task Name", "Insert Fith Task Name");
      }
    }
    while (answer3recieved == false) {
      if (Serial.available() > 0) {
        answer3 = Serial.readString();
        drawlist(0, 10, String(answer1), String(answer2), String(answer3), "Insert Fourth Task Name", "Insert Fith Task Name");
        delay(ViewTime);
        answer3recieved = true;
      } else {
        drawlist(0, 10, String(answer1), String(answer2), "Insert Third Task Name", "Insert Fourth Task Name", "Insert Fith Task Name");
      }
    }
    while (answer4recieved == false) {
      if (Serial.available() > 0) {
        answer4 = Serial.readString();
        drawlist(0, 10, String(answer1), String(answer2), String(answer3), String(answer4), "Insert Fith Task Name");
        delay(ViewTime);
        answer4recieved = true;
      } else {
        drawlist(0, 10, String(answer1), String(answer2), String(answer3), "Insert Fourth Task Name", "Insert Fith Task Name");
      }
    }
    while (answer5recieved == false) {
      if (Serial.available() > 0) {
        answer5 = Serial.readString();
        drawlist(0, 10, String(answer1), String(answer2), String(answer3), String(answer4), String(answer5));
        delay(ViewTime);
        answer5recieved = true;
      } else {
        drawlist(0, 10, String(answer1), String(answer2), String(answer3), String(answer4), "Insert Fith Task Name");
      }
    }
  }
  DateTime now = rtc.now();
  Serial.println("Time is now: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));  //Beskriver vad som ska printas ut i serial monitorn
  draw(0, 22, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
  delay(3000);
  int i = 0;
  
  Serial.println("Write Down A TimeStamp");
  while (alltasksdone == false) {
    if (iv2 == 2) {
      iv2 = 0;
    }
    if (i == 0) {
      if (Serial.available() > 0) {
        timeinputer(timestampfortask1, iv2, i);
      }
    } else if (i == 1) {
      if (Serial.available() > 0) {
        timeinputer(timestampfortask2, iv2, i);
      }
    } else if (i == 2) {
      if (Serial.available() > 0) {
        timeinputer(timestampfortask3, iv2, i);
      }
    } else if (i == 3) {
      if (Serial.available() > 0) {
        timeinputer(timestampfortask4, iv2, i);
      }
    } else {
      if (Serial.available() > 0) {
        timeinputer(timestampfortask5, iv2, i);
      }
    }
    if (i == 4) {
      alltasksdone = true;
    } else {
      drawlist2(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), (String(timestampfortask1[0]) + ":" + (String(timestampfortask1[1])), (String(timestampfortask2[0]) + ":" + String(timestampfortask2[1])), (String(timestampfortask3[0]) + ":" + String(timestampfortask3[1])), (String(timestampfortask4[0]) + ":" + String(timestampfortask4[1])), (String(timestampfortask5[0]) + ":" + String(timestampfortask5[1]));
    }
  }
  bool coderunning = false;

  savedmillistime = millis();
  int savedtimestamp = ((timestampfortask1 * 1000) + millis());
  Serial.println(savedtimestamp);
  delay(1000);
  while (timestampfortask1 > 0 && digitalRead(7) == false) {
    coderunning = true;
    
    timestampfortask1 = (savedtimestamp - millis());
    Serial.println(timestampfortask1);
    drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
  }
  if (timestampfortask1 == 0 && coderunning == true) {
    draw(0, 22, "You ran out of time!");
  } else {
    timestampfortask2 = (timestampfortask2 + timestampfortask1);
  }
  delay(3000);
  savedmillistime = currenttime;
  savedtimestamp = (timestampfortask2 + savedmillistime);
  while (timestampfortask2 > 0 && digitalRead(7) == false) {
    timestampfortask2 = (savedtimestamp - currenttime);
    drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
    Serial.println(timestampfortask2);
  }
  if (timestampfortask2 == 0 && coderunning == false) {
    draw(0, 22, "You ran out of time!");
  } else {
    timestampfortask3 = (timestampfortask3 + timestampfortask2);
  }
  delay(3000);
  savedmillistime = currenttime;
  savedtimestamp = (timestampfortask3 + savedmillistime);
  while (timestampfortask3 > 0 && digitalRead(7) == false) {
    timestampfortask3 = (savedtimestamp - currenttime);
    drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
    Serial.println(timestampfortask3);
  }
  if (timestampfortask3 == 0 && coderunning == false) {
    draw(0, 22, "You ran out of time!");
  } else {
    timestampfortask4 = (timestampfortask4 + timestampfortask3);
  }
  delay(3000);
  savedmillistime = currenttime;
  savedtimestamp = (timestampfortask4 + savedmillistime);
  while (timestampfortask4 > 0 && digitalRead(7) == false) {
    timestampfortask4 = (savedtimestamp - currenttime);
    drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
  }
  if (timestampfortask4 == 0 && coderunning == false) {
    draw(0, 22, "You ran out of time!");
  } else {
    timestampfortask5 = (timestampfortask5 + timestampfortask4);
  }
  delay(3000);
  savedmillistime = currenttime;
  savedtimestamp = (timestampfortask5 + savedmillistime);
  while (timestampfortask5 > 0 && digitalRead(7) == false) {
    timestampfortask5 = (savedtimestamp - currenttime);
    drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
  }
  if (timestampfortask5 == 0 && coderunning == false) {
    draw(0, 22, "You ran out of time!");
  } else {
    draw(0, 22, "You Completed all of your tasks!!!");
  }
  delay(10000);
  draw(0, 22, "Turning off");
  
  drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1), String(timestampfortask2), String(timestampfortask3), String(timestampfortask4), String(timestampfortask5));
}

void timeinputer(int timestampfortask, int iv2var, int ivar) {
  if (iv2var == 0) {
    Serial.println("Insert timestamp hour:");
    timestampfortask[0] = Serial.read();
    iv2var++;
  } else {
    Serial.println("Insert timestamp minutes")
    timestampfortask[1] = Serial.read();
    ivar++;
    iv2var++;
  }
    

}



void draw(int x, int y, String text) {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.setFont(u8g_font_osb21);
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text.c_str());
  } while (u8g.nextPage());
}

void drawlist(int x, int y, String text, String text2, String text3, String text4, String text5) {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.setFont(u8g_font_osb21);
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text.c_str());
    u8g.drawStr(x, (y + 10), text2.c_str());
    u8g.drawStr(x, (y + 20), text3.c_str());
    u8g.drawStr(x, (y + 30), text4.c_str());
    u8g.drawStr(x, (y + 40), text5.c_str());
  } while (u8g.nextPage());
}

void drawlist2(int x, int y, String text, String text2, String text3, String text4, String text5, String text6) {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.setFont(u8g_font_osb21);
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text.c_str());
    u8g.drawStr(x, (y + 10), text2.c_str());
    u8g.drawStr(x, (y + 20), text3.c_str());
    u8g.drawStr(x, (y + 30), text4.c_str());
    u8g.drawStr(x, (y + 40), text5.c_str());
    u8g.drawStr(x, (y + 50), text6.c_str());
  } while (u8g.nextPage());
}

void drawlist3(int x, int y, String text, String text2, String text3, String text4, String text5, String text6, String timer1, String timer2, String timer3, String timer4, String timer5) {
  // graphic commands to redraw the complete screen should be placed here
  //u8g.setFont(u8g_font_osb21);
  u8g.firstPage();
  do {
    
    u8g.drawStr(x, y, text.c_str());
    u8g.drawStr(x, (y + 10), String(text2 + ":" + timer1).c_str());
    u8g.drawStr(x, (y + 20), String(text3 + ":" + timer2).c_str());
    u8g.drawStr(x, (y + 30), String(text4 + ":" + timer3).c_str());
    u8g.drawStr(x, (y + 40), String(text5 + ":" + timer4).c_str());
    u8g.drawStr(x, (y + 50), String(text6 + ":" + timer5).c_str());
  } while (u8g.nextPage());
}
