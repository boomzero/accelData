#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;

// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS

// Robot configuration code.
inertial BrainInertial = inertial();
#pragma endregion VEXcode Generated Robot Configuration

//----------------------------------------------------------------------------
//
//    Module:       main.cpp
//    Author:       zcr
//    Created:      2023/07/06
//    Description:  accelerometer data logging utility
//
//----------------------------------------------------------------------------

#include "iq_cpp.h"

using namespace vex;
const int sr = 50;

void cal() {
  Brain.Screen.clearScreen();
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  BrainInertial.calibrate();
  wait(2, seconds);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

struct node {
  node *prev = nullptr, *next = nullptr;
  double val = 0;
};

int main() {
  cal();
  node *head = new node, *tail = head;
#define dat BrainInertial.acceleration(xaxis)
  head->val = dat;
  Brain.Screen.setPenColor(red);
  for (int i = 0; i <= 159; i++) {
    node *c = new node;
    c->val = dat;
    Brain.Screen.drawPixel(i, (c->val + 4) * 10 + 10);
    c->prev = tail; // add the newest data
    tail->next = c;
    tail = c;
    wait(sr, msec);
  }
  while (true) {
    node *c = new node;
    c->val = dat;
    c->prev = tail; // add the newest data
    tail->next = c;
    tail = c;
    node *del = head; // delete the oldest data
    head->next->prev = nullptr;
    head = head->next;
    delete del;
    Brain.Screen.clearScreen();
    c = head; // reusing c
    int i = 0;
    while (c->next != nullptr) {
      Brain.Screen.drawPixel(i, (c->val + 4) * 10 + 10);
      i++;
      c = c->next;
    }
    wait(sr, msec);
  }
}
