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
    
//These are my functions to make it easier to write an autonomous process.
void goFWD(int speedPct, int taskSleep){
    RightMotor.spin(forward,speedPct,pct);
    LeftMotor.spin(reverse,speedPct,pct);
    task::sleep(taskSleep);
    RightMotor.stop(brakeType::brake);
    LeftMotor.stop(brakeType::brake);
}
void goREV(int speedPct, int taskSleep){
    RightMotor.spin(reverse,speedPct,pct);
    LeftMotor.spin(forward,speedPct,pct);
    task::sleep(taskSleep);
    RightMotor.stop(brakeType::brake);
    LeftMotor.stop(brakeType::brake);
}
void turnL(int deg){
    LeftMotor.spinFor(directionType::forward,deg,rotationUnits::degrees);
}
void turnR(int deg){
    RightMotor.spinFor(directionType::forward,deg,rotationUnits::degrees);    
}
//These are my functions to make it easier to write an autonomous process.

void autonomus(void){
    goFWD(60,1500);
    turnR(700);
    goFWD(60,2000);
    ArmLiftMotor.spin(forward,50,velocityUnits::pct);
    task::sleep(1000);
    ArmLiftMotor.stop(brakeType::hold);
    goREV(30,1500);
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
