#include "vex.h"
using namespace vex;


vex::brain              Brain;
vex::competition        Competition;
vex::motor              RightMotor = vex::motor(vex::PORT1);
vex::motor              LeftMotor = vex::motor(vex:PORT2);
vex::motor              ArmLiftMotor = vex::motor(vex::PORT3);

vex::motor              RightSpinMotor = vex::motor(vex::PORT4); 
vex::motor              LeftSpinMotor = vex::motor(vex::PORT5);

vex::controller         Controller1 = vex::controller(//if you want to specify that you can write : vex::PORT3);

void pre_auton(void){
    //all activities that occur before the competition starts

}

void autonomus(void){
   //object tracking vision sensor code 
   while(true){
        Brain.Screen.clearLine();
        VisionSensor.takeSnapshot(SIG_RED);

        if(VisionSensor.largestObject.exists){
            if(VisionSensor.largestObject.centerX > 100){
                RightMotor.spinFor(directionType::forward,700,rotationUnits::degrees);
            }
            if(VisionSensor.largestObject.centerX < 60){
                LeftMotor.spinFor(directionType::forward,700,rotationUnits::degrees);
            }
            if(VisionSensor.largestObject.centerX > 60 && VisionSensor.largestObject.centerX < 100){
                if(VisionSensor.largestObject.width < 125){
                    RightMotor.spin(reverse,20,pct);
                    LeftMotor.spin(forward,20,pct);            
                }
                else{
                    RightMotor.stop(brakeType::brake);
                    LeftMotor.stop(brakeType::brake);
                }
            }
        }
    }
   //object tracking vision sensor code 
}

void usercontrol(void){
    while(1){
        //drive control
        if(Controller1.Axis3.position(pct) != 0){
            LeftWheel.spin(forward,Controller1.Axis3.position(),pct);
            RightWheel.spin(forward,Controller1.Axis3.position(),pct);
        }
        else if(Controller1.Axis1.position(pct) != 0){
            LeftWheel.spin(forward,Controller1.Axis1.position(),pct);
            RightWheel.spin(reverse,Controller1.Axis1.position(),pct);
        }
        else{
            LeftWheel.stop(brake);
            RightWheel.stop(brake);
        }
    }
}

int main(){
    Competition.autonomus(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while(1){
        vex::task::sleep(100);
    }
}
