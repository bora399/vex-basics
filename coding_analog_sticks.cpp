#include "vex.h"
using namespace vex;


vex::brain              Brain;
vex::competition        Competition;
vex::motor              RightMotor = vex::motor(vex::PORT1);
vex::motor              LeftMotor = vex::motor(vex:PORT2 true);

vex::controller         Controller1 = vex::controller(//if you want to specify that you can write : vex::PORT3);

void pre_auton(void){
    //all activities that occur before the competition starts

}

void autonomus(void){
    //autonomus code
}

void usercontrol(void){
    while(1){
        //tank mode
        //RightMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
        //LeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        
        //normal analog sticks mode with if-else statements (actually i always prefer this :) )
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
