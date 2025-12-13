#include "vex.h"

using namespace vex;

competition Competition;
brain Brain;
controller Controller;

// define motors 
motor leftFront = motor(PORT18, ratio18_1, true);
motor leftMiddle = motor(PORT15, ratio18_1, false);
motor leftBack = motor(PORT19, ratio18_1, true);


motor rightFront = motor(PORT14, ratio18_1, false);
motor rightMiddle = motor(PORT16, ratio18_1, true);
motor rightBack = motor(PORT11, ratio18_1, false);

motor_group left_side = motor_group(leftFront, leftMiddle, leftBack);
motor_group right_side = motor_group(rightFront, rightMiddle, rightBack);

motor leftIntake = motor(PORT20, ratio18_1, true);
motor rightIntake = motor(PORT2, ratio18_1, true);

drivetrain Drivetrain = drivetrain(left_side, right_side, 10.21, 12.5, 14, inches, 4/5);

//define pneumatics 
digital_out deloader = digital_out(Brain.ThreeWirePort.B);
// not an actual wing lmao
digital_out wing = digital_out(Brain.ThreeWirePort.A);

void pre_auton(void) {
  Brain.Screen.print(1);
};


void autonomous(void) {
/*
  switch (obnoxiouslongvariableusedfortheautonswitcher)
  {
  case 1:
    left_side.spin(fwd, 7, volt);
    right_side.spin(fwd, 7, volt);
    wait(1, seconds);
    left_side.spin(forward, 3.5, volt);
    right_side.spin(reverse, 8, volt);
    wait(0.5, seconds);
    left_side.stop(hold);
    right_side.stop(hold);
    break;
  
  case 2:
    left_side.spin(fwd, 7, volt);
    right_side.spin(fwd, 7, volt);
    wait(1, seconds);
    right_side.spin(forward, 3.5, volt);
    left_side.spin(reverse, 8, volt);
    wait(0.5, seconds);
    left_side.stop(hold);
    right_side.stop(hold);
    break;

  case 3:
    left_side.spin(fwd, 12, volt);
    right_side.spin(fwd, 12, volt);
    wait(1, seconds);
    right_side.spin(reverse, 12, volt);
    left_side.spin(reverse, 12, volt);
    wait(0.5, seconds);
    left_side.stop(hold);
    right_side.stop(hold);
    break;
  }
*/
  // ..........................................................................
  //leftIntake.spin(fwd, 12, volt);
  //leftIntake.stop(hold);
  /*left_side.spin(fwd, 7, volt);
  right_side.spin(fwd, 7, volt);
  wait(1.5, seconds);
  left_side.stop(hold);
  right_side.stop(hold);
  left_side.spin(fwd, 7, volt);
  right_side.spin(fwd, 7, volt);
  wait(1, seconds);
  left_side.spin(forward, 3.5, volt);
  right_side.spin(reverse, 8, volt);
  wait(0.5, seconds);
  left_side.stop(hold);
  right_side.stop(hold);*/
  //drive forward for 2 seconds
  //
  // ..........................................................................
}
 
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
     
    //drive control
    left_side.spin(fwd, Controller.Axis3.position()/8.33333 + Controller.Axis1.position()/8.33333, volt);
    right_side.spin(fwd, Controller.Axis3.position()/8.33333 - Controller.Axis1.position()/8.33333, volt);

    //Intake Control
    if(Controller.ButtonR1.pressing()){
      leftIntake.spin(reverse, 24, volt);
      rightIntake.spin(fwd, 24, volt);
    }
    //
     else if(Controller.ButtonR2.pressing()){ 
      leftIntake.spin(fwd, 24, volt);
      rightIntake.spin(reverse, 24, volt);
    }
    //stop intake if no button is being pressed
    else{
      leftIntake.stop(hold);
      rightIntake.stop(hold);
    }
  }
}
void Unload(){
      if (deloader.value())
      {
        deloader.set(false);
      } else
      {
      deloader.set(true);
      }
    }
 
void Wing(){
      if (wing.value())
      {
        wing.set(false);
      } else
      {
      wing.set(true);
      }
    }
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Controller.ButtonL2.pressed(Unload);
  Controller.ButtonA.pressed(Wing);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
