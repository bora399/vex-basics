#include "vex.h"
using namespace vex;


vex::brain              Brain;
vex::competition        Competition;
vex::motor              RightMotor = vex::motor(vex::PORT1);
vex::motor              LeftMotor = vex::motor(vex:PORT2 true);
vex::motor              ArmLiftMotor = vex::motor(vex::PORT3);

vex::motor              RightSpinMotor = vex::motor(vex::PORT4); 
vex::motor              LeftSpinMotor = vex::motor(vex::PORT5 true);

vex::controller         Controller1 = vex::controller(//if you want to specify that you can write : vex::PORT3);

void pre_auton(void){
    //all activities that occur before the competition starts

}

void autonomus(void){

    //move forward
    LeftMotor.startRotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);
    RightMotor.rotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);
    //turn left

    //move forward
    LeftMotor.startRotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);
    RightMotor.rotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);
    //turn left
    
    //move forward
    LeftMotor.startRotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);
    RightMotor.rotateFor(vex::directionType::fwd,1000,vex::rotationUnits::deg);




}

void usercontrol(void){

    int ArmSpeedPercent = 100;
    while(1){
        
        //drive program
        RightMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
        LeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);

        //arm control
        if(Controller1.ButtonR1.pressing()){
            RightSpinMotor.spin(vex::directionType::fwd,ArmSpeedPercent,vex::velocityUnits::pct);
            LeftSpinMotor.spin(vex::directionType::fwd,ArmSpeedPercent,vex::velocityUnits::pct);
        }
        else if(Controller2.ButtonR2.pressing()){
            RightSpinMotor.spin(vex::directionType::rev,ArmSpeedPercent,vex::velocityUnits::pct);
            LeftSpinMotor.spin(vex::directionType::rev,ArmSpeedPercent,vex::velocityUnits::pct);
        }
        else{
            RightSpinMotor.stop(vex::brakeType::brake);
            LeftSpinMotor.stop(vex::brakeType::brake);
        }
        RightMotor.spin(vex::directionType::fwd, Controller1.ButtonR1.pressing(), vex::velocityUnits::pct);
        LeftMotor.spin(vex::directionType::fwd, Controller1.ButtonR2.pressing(), vex::velocityUnits::pct);


        vex::task::sleep(20);
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