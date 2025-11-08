#include "vex.h"

using namespace vex;

competition Competition;
brain Brain;
controller Controller;

//setup auton switch variable thingy type beat
int obnoxiouslongvariableusedfortheautonswitcher = 0;

// define motors
motor leftFront = motor(PORT5, ratio18_1, true);
motor leftMiddle = motor(PORT18, ratio18_1, false);
motor leftBack = motor(PORT19, ratio18_1, true);


motor rightFront = motor(PORT9, ratio18_1, false);
motor rightMiddle = motor(PORT7, ratio18_1, true);
motor rightBack = motor(PORT3, ratio18_1, false);

motor_group left_side = motor_group(leftFront, leftMiddle, leftBack);
motor_group right_side = motor_group(rightFront, rightMiddle, rightBack);

motor leftIntake = motor(PORT20, ratio18_1, true);
motor rightIntake = motor(PORT10, ratio18_1, true);

drivetrain Drivetrain = drivetrain(left_side, right_side, 10.21, 12.5, 14, inches, 4/5);

//define pneumatics 
digital_out deloader = digital_out(Brain.ThreeWirePort.H);
digital_out wing = digital_out(Brain.ThreeWirePort.A);

void pre_auton(void) {
  Brain.Screen.print(1);
};


void autonomous(void) {
/*
  switch (obnoxiouslongvariableusedfortheautonswitcher)
  {
  case 1:
    
    break;
  
  case 2:

    break;

  case 3:

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
  right_side.stop(hold);*/
  left_side.spin(fwd, 7, volt);
  right_side.spin(fwd, 7, volt);
  wait(1, seconds);
  left_side.spin(forward, 3.5, volt);
  right_side.spin(reverse, 8, volt);
  wait(0.5, seconds);
  left_side.stop(hold);
  right_side.stop(hold);
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
     else if(Controller.ButtonL1.pressing()){ 
      rightIntake.spin(fwd, 24, volt);
    }
    //
    else if(Controller.ButtonL2.pressing()){ 
      rightIntake.spin(fwd, 24, volt);
      leftIntake.spin(fwd, 24, volt);
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
/*void switchtheautonomoustooneofthreepresetautonomousprograms(){
  obnoxiouslongvariableusedfortheautonswitcher++;
  if (obnoxiouslongvariableusedfortheautonswitcher > 3){
    obnoxiouslongvariableusedfortheautonswitcher = 0;
    Controller.Screen.clearScreen();
    Controller.Screen.print("AUTON");
    while(true)
    {
      Controller.Screen.setCursor(1,1);
      Controller.Screen.print(obnoxiouslongvariableusedfortheautonswitcher);
    }
  }
  
    

}
*/
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Controller.ButtonR2.pressed(Unload);
  Controller.ButtonX.pressed(Wing);
  //Controller.ButtonUp.pressed(switchtheautonomoustooneofthreepresetautonomousprograms);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
