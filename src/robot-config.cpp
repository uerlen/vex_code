#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Cont = controller(primary);
motor Motor = motor(PORT19, ratio18_1, false);
motor MotorLF = motor(PORT1, ratio18_1, false);
motor MotorLM = motor(PORT22, ratio18_1, false);
motor MotorLB = motor(PORT6, ratio18_1, false);
motor MotorRF = motor(PORT7, ratio18_1, false);
motor MotorRM = motor(PORT22, ratio18_1, false);
motor MotorRB = motor(PORT18, ratio18_1, false);
// motor MotorGet1 = motor(PORT8,ratio18_1, false);
motor MotorGet2 = motor(PORT10, ratio18_1, false);
motor MotorShot1 = motor(PORT8, ratio18_1, true);
motor MotorShot2 = motor(PORT9, ratio18_1, false);
motor MOtorFire = motor(PORT11, ratio18_1, false);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
vision Vis = vision (PORT15, 50);
/*vex-vision-config:end*/
inertial Ine = inertial(PORT5);

gps GPS = gps(PORT5, 1.00, 2.00, mm, 180);
digital_out Pne = digital_out(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}