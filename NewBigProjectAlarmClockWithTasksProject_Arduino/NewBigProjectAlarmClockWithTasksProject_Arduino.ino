//Name: Real time alarm clock with tasks.
//Aurthor: Adam Clarke te23a.
//Date: 2025-01-14.

//För peizo noterna.
#define BUZZER_PIN 8
//Slutet av peizo noterna

//För Peizo 



//Slutet av sektionen



#include "U8glib.h"                             //Inkluderar U8g bibiloteket
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

#include <RTClib.h>  // Inkluderar bibilotektet för klockan
#include <Wire.h>    //Inkluderar någonting

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
void loop() {
  
  
  
  int timestampfortask1[3] = {0};
  int timestampfortask2[3] = {0};
  int timestampfortask3[3] = {0};
  int timestampfortask4[3] = {0};
  int timestampfortask5[3] = {0};
  int timestampforwakeywakey[3] = {0};
  bool answer1recieved = false;
  bool answer2recieved = false;
  bool answer3recieved = false;
  bool answer4recieved = false;
  bool answer5recieved = false;
  bool clockstarted = false;
  bool alltasksdone = false;
  bool breakloop = false;
  
  String answer1;
  String answer2;
  String answer3;
  String answer4;
  String answer5;

  int number = 0;
  int iv2 = 0;
  Serial.println("Button is ready to be pressed!");
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
  int ViewTime = 1000;
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
  
  
  while (alltasksdone == false) {
    if (iv2 == 2) {
      iv2 = 0;
    }
    if (i == 0) {
      draw(0, 22, "Wakey wakey when?");
      while (i == 0) {
        if (Serial.available() != 0) {
          timeinputer(timestampforwakeywakey, iv2, i);
        }
        delay(1000);
      }
      Serial.println("Write Down A TimeStamp");
      Serial.println("Insert timestamp hour:");
      Serial.println("Insert timestamp minutes:");
    }
    if (i == 1) {
      if (Serial.available() != 0) {
        timeinputer(timestampfortask1, iv2, i);
      }
    } else if (i == 2) {
      if (Serial.available() != 0) {
        timeinputer(timestampfortask2, iv2, i);
      }
    } else if (i == 3) {
      if (Serial.available() != 0) {
        timeinputer(timestampfortask3, iv2, i);
      }
    } else if (i == 4) {
      if (Serial.available() != 0) {
        timeinputer(timestampfortask4, iv2, i);
      }
    } else {
      if (Serial.available() != 0) {
        timeinputer(timestampfortask5, iv2, i);
      }
    }
    if (i == 6) {
      alltasksdone = true;
    } else {
      DateTime now = rtc.now();
      drawlist2(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(timestampfortask1[0]) + ":" + String(timestampfortask1[1]), String(timestampfortask2[0]) + ":" + String(timestampfortask2[1]), String(timestampfortask3[0]) + ":" + String(timestampfortask3[1]), String(timestampfortask4[0]) + ":" + String(timestampfortask4[1]), String(timestampfortask5[0]) + ":" + String(timestampfortask5[1]));
    }
  }



  if (timestampforwakeywakey[0] > now.hour() || timestampforwakeywakey[1] > now.minute()) {
    int nowhour = now.hour();
    int nowminute = now.minute();
    DateTime now = rtc.now();
    while (!(timestampforwakeywakey[0] == nowhour && timestampforwakeywakey[1] == nowminute) && !digitalRead(7)) {
      DateTime now = rtc.now();
      nowhour = now.hour();
      nowminute = now.minute();
      drawlist(0, 22, "Clock will ring at:", String(timestampforwakeywakey[0]) + ":" + String(timestampforwakeywakey[1]), "Current time: ", String(now.hour()) + ":" + String(now.minute()), "Better be prepeared!");
      delay(100);
      Serial.println("Waiting for alarm to go off!");
    }
    if (timestampforwakeywakey[0] == nowhour && timestampforwakeywakey[1] == nowminute) {
      delay(1500);
      while (digitalRead(7) == false) {
        draw(0, 22, "Wakey Wakey!!!");
        delay(100);
        for (int i = 0; i < 5; i++) {
          tone(BUZZER_PIN, 1000);           // Play the note on pin 8

          int pauseBetweenNotes = 1000;       // Add pause between notes
          delay(pauseBetweenNotes);

          noTone(BUZZER_PIN); // Stop the tone playing
        }
        delay(3000);
      }
    } else {
      Serial.println("You have cancelled!");
      draw(0, 22, "You have cancelled!");
      delay(3000);
      breakloop = true;
    }
  }
  if (breakloop == true) {
    return;
  }
  
  Serial.println("Alarm has been stopped!")
  delay(1000);
  timerprocessor(timestampfortask1, answer1, answer2, answer3, answer4, answer5, timestampfortask1, timestampfortask2, timestampfortask3, timestampfortask4, timestampfortask5);
  delay(1000);

  timerprocessor(timestampfortask2, answer1, answer2, answer3, answer4, answer5, timestampfortask1, timestampfortask2, timestampfortask3, timestampfortask4, timestampfortask5);
  timerprocessor(timestampfortask3, answer1, answer2, answer3, answer4, answer5, timestampfortask1, timestampfortask2, timestampfortask3, timestampfortask4, timestampfortask5);
  timerprocessor(timestampfortask4, answer1, answer2, answer3, answer4, answer5, timestampfortask1, timestampfortask2, timestampfortask3, timestampfortask4, timestampfortask5);
  timerprocessor(timestampfortask5, answer1, answer2, answer3, answer4, answer5, timestampfortask1, timestampfortask2, timestampfortask3, timestampfortask4, timestampfortask5);
  draw(0, 22, "You Completed all tasks!");
  delay(10000);
  draw(0, 22, "Turning off");
  
  drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(answer1), String(answer2), String(answer3), String(answer4), String(answer5), String(timestampfortask1[0]) + ":" + String(timestampfortask1[1]), String(timestampfortask2[0]) + ":" + String(timestampfortask2[1]), String(timestampfortask3[0]) + ":" + String(timestampfortask3[1]), String(timestampfortask4[0]) + ":" + String(timestampfortask4[1]), String(timestampfortask5[0]) + ":" + String(timestampfortask5[1]));
}

void timeinputer(int timestampfortask[], int &iv2var, int &ivar) {
  if (iv2var == 0) {
    timestampfortask[0] = Serial.parseInt();
    delay(1000);
    iv2var++;
    Serial.read();
    Serial.println(iv2var);
  } else {
    Serial.println(Serial.available());
    timestampfortask[1] = Serial.parseInt();
    delay(1000);
    ivar++;
    iv2var++;
    Serial.println(iv2var);
    Serial.read();
  }
}

void timerprocessor(int timestampfortaskthing[], String ans1, String ans2, String ans3, String ans4, String ans5, int timestamptask1[], int timestamptask2[], int timestamptask3[], int timestamptask4[], int timestamptask5[]) { 
  DateTime now = rtc.now();
  if (timestampfortaskthing[0] > now.hour() || timestampfortaskthing[1] > now.minute()) {
    DateTime now = rtc.now();
    int nowhour = now.hour();
    int nowminute = now.minute();
    while (timestampfortaskthing[0] > now.hour() || timestampfortaskthing[1] > now.minute() && digitalRead(7) == false) { //Buggy part
      DateTime now = rtc.now();
      nowhour = now.hour();
      nowminute = now.minute();
      drawlist3(0, 10, String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()), String(ans1), String(ans2), String(ans3), String(ans4), String(ans5), String(timestamptask1[0]) + ":" + String(timestamptask1[1]), String(timestamptask2[0]) + ":" + String(timestamptask2[1]), String(timestamptask3[0]) + ":" + String(timestamptask3[1]), String(timestamptask4[0]) + ":" + String(timestamptask4[1]), String(timestamptask5[0]) + ":" + String(timestamptask5[1]));
      delay(100);
    }
    if (timestampfortaskthing[0] == nowhour && timestampfortaskthing[1] != nowminute) {
      draw(0, 22, "You ran out of time!");
      delay(3000);
    } else {
      int amountofsavedhours = (timestampfortaskthing[0] - nowhour);
      int amountofsavedminutes = ((amountofsavedhours * 60) + (timestampfortaskthing[1] - nowminute));
      draw(0, 22, "you saved: " + String(amountofsavedminutes) + "minutes!");
      delay(3000);
    }
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
    u8g.drawStr(x, (y + 12), String(text2 + ":" + timer1).c_str());
    u8g.drawStr(x, (y + 22), String(text3 + ":" + timer2).c_str());
    u8g.drawStr(x, (y + 32), String(text4 + ":" + timer3).c_str());
    u8g.drawStr(x, (y + 42), String(text5 + ":" + timer4).c_str());
    u8g.drawStr(x, (y + 52), String(text6 + ":" + timer5).c_str());
  } while (u8g.nextPage());
}
