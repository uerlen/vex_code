#include "vex.h"
#include "tfiles.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*
IIIIIIIIIIIIIIII
     I    I
     I    I
     I    I
     I    I
     I    I
     I    I
IIIIIIIIIIIIIIII
底盘
*/
using namespace af;
void move(float r,float l){
  MotorLF.spin(forward,l,pct);
  MotorLB.spin(forward,l,pct);
  MotorRF.spin(forward,r,pct);
  MotorRB.spin(forward,r,pct);
}

void Stop(){
  MotorLF.stop();
  MotorLB.stop();
  MotorRF.stop();
  MotorRB.stop();
}
void Stop(bool flag){
  if (flag == true ){
    MotorLF.stop(hold);
    MotorLB.stop(hold);
    MotorRF.stop(hold);
    MotorRB.stop(hold);
    return;
  }
  else {
    MotorLF.stop();
    MotorLB.stop();
    MotorRF.stop();
    MotorRB.stop();
    return;
  }
}

void reset(){
  MotorLF.resetPosition();
  MotorLB.resetPosition();
  MotorRF.resetPosition();
  MotorRB.resetPosition();
}


void walk_con(){
  float a1 = Controller1.Axis1.position();
  float a2 = Controller1.Axis2.position();
  float a3 = Controller1.Axis3.position();
  float a4 = Controller1.Axis4.position();
  maxmin(a1);
  maxmin(a2);
  maxmin(a3);
  maxmin(a4);

  af::move(a2,a3);
}

/*
IIIIIIIIIIIIIIIIIIIII
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
IIIIIIIIIIIIIIIIIIIIII
功能项
*/

/*
R2 ---  shot
R1 ---  pne
L2 ---  get _ down
L1 ---  get _ up
Y  ---  walk mode
^  ---  shot speed up
\/ ---  shot speed down
change(float min_,float max_,float d_,int cd_)
*/

on_off pne(600,0) , shot(200,0) ;
change shotspeed(70,100,10,50) ;

void check(){
  pne.button(Controller1.ButtonR1.pressing());
  shot.button(Controller1.ButtonR2.pressing());

  shotspeed.button(Controller1.ButtonUp.pressing(),Controller1.ButtonDown.pressing());
}

void work(){
  if (pne.op() == 1){
    pne.button(true,true);
    Pne.set(true);
    wait(500,msec);
    pne.button(true,true);
  }
  if (shot.op() == 1){
    MotorShot1.spin(forward,shotspeed.num(),pct);
    MotorShot2.spin(forward,shotspeed.num(),pct);
  }
  if (shot.op() == 0){
    MotorShot1.stop();
    MotorShot2.stop();
  }
  int getspeed = 0;
  if (Controller1.ButtonL1.pressing()){
    getspeed += 100;
  }
  if (Controller1.ButtonL2.pressing()){
    getspeed -= 100;
  }
  MotorGet1.spin(forward,getspeed,pct);
  MotorGet2.spin(forward,getspeed,pct);
}

/*
IIIIIIIIII           I
    I     I         I
    I      I       I
    I       I     I
    I        I   I
    I         I I
IIIIIIIII      I
自动 auton
void pre(int g,float pkin,float ikin,float dkin,float imaxin)
bool check(int input,float& move)
pid(int g,int j,float pkin,float ikin,float dkin)
*/

void gofordegree(int goal){
  pids go ;
  go.pre(goal,0.7,0.3,0.3,goal*0.1);
  float movement;
  MotorLB.resetPosition();
  while ( go.check(MotorLB.position(degrees) , movement) ) af::move(movement,movement);
}

void turnfordegree(int goal){
  pids go ;
  go.pre(goal,0.7,0.3,0.3,goal*0.1);
  float movement = 50;
  Ine.calibrate();
  while ( Ine.heading(degrees) , movement)  af::move(movement,-movement);
}

/*
    I           I
     I         I
      I       I
       I     I
        I   I
         I I
          I
主函数区 pre  auton  usercontrol
*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  af::reset();
  MotorGet1.resetPosition();
  MotorGet2.resetPosition();
  MotorShot1.resetPosition();
  MotorShot2.resetPosition();

  Ine.calibrate();

  Pne.set(0);

  Brain.Timer.reset();

  Controller1.Screen.print("Ready!");
}

void autonomous(void) {
  

  
}
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    check();
    walk_con();
    work();

    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}