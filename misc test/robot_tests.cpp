/*
 * Copyright (c) 2005, Brad Kratochvil, Toby Collett, Brian Gerkey, Andrew Howard, ...
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *           this list of conditions and the following disclaimer.
 *               * Redistributions in binary form must reproduce the above copyright notice,
 *                     this list of conditions and the following disclaimer in the documentation
 *                           and/or other materials provided with the distribution.
 *                               * Neither the name of the Player Project nor the names of its contributors
 *                                     may be used to endorse or promote products derived from this software
 *                                           without specific prior written permission.
 *
 *                                           THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *                                           ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *                                           WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *                                           DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *                                           ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *                                           (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *                                           LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *                                           ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *                                           (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *                                           SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *                                           */

#include <iostream>
#include <libplayerc++/playerc++.h>
#include <cmath>

using namespace PlayerCc;

void turnTo(PlayerClient *robot, Position2dProxy *pp, double angle_in_deg) {
    using namespace std;
    robot->Read();
    double currentAngle = rtod(pp->GetYaw());
    double difference;

    cout << "getYaw in degrees: " << currentAngle << "\n";
    cout << "angle in r " << angle_in_deg << "\n";
    cout << "Difference between angles : " << difference << "\n";

    while (true) {

        robot->Read();
        difference = rtod(pp->GetYaw()) - angle_in_deg;

        if (difference < 0) {
            difference = abs(difference);
        }

        if (difference < 2) {
            pp->SetSpeed(0, 0);
            return;
        }
        cout << "Difference in angles : " << difference << endl;

        pp->SetSpeed(0, 0.2);


    }


}


void moveDistanceAlongX(PlayerClient *robot, Position2dProxy *pp,
        double distance) {


    using namespace std;

    robot->Read();
    double startX = pp->GetXPos();
    double difference;

    double targetX;

    if (distance > 0.05) {
        turnTo(robot, pp, 0);
        //move to the right
    } else if (distance < 0) {
        turnTo(robot, pp, 180); // move left

    } else {
        return;
    }

    targetX = startX + distance;

    cout << "startX : " << startX << "\n";
    cout << "desitnation X : " << targetX << endl;

    while (true) {

        robot->Read();
        double currentX = pp->GetXPos();
        double xDiff;

        if (targetX > currentX) {
            xDiff = targetX - currentX;
        } else {

            /*e.g if robot is at X = 10, and wants to move left 8 units:
             * target is when X = 2 +/- 0.05
             * currentX will be 10 to start, so xDiff = 10 - 2 = 8. move the robot 1 unit to the left
             * xDiff is now (10-1)-2 = 9-7 so it is approaching the location.
             */
            xDiff = currentX - targetX;
        }

        difference = abs(targetX - currentX);


        difference = xDiff;

        cout << "difference : xDiff: " << difference << " " << xDiff << endl;
        if (difference < 0) {
            difference = abs(xDiff);
        }

        if (difference < 0.05) {
            pp->SetSpeed(0, 0);
            return;
        }

	else{
	pp->SetSpeed(0.1,0);
	}	

 }    
}

void moveDistanceAlongY(PlayerClient *robot, Position2dProxy *pp,
         double distance) {



    using namespace std;

    robot->Read();
    double startY = pp->GetYPos();
    double difference;

    double targetY;

    if (distance > 0.05) {
        turnTo(robot, pp, 90);
        //face up
    } else if (distance < 0) {
        turnTo(robot, pp, 270); // face down

    } else {
        return;
    }

    targetY = startY + distance;

    cout << "startX : " << startY << "\n";
    cout << "desitnation X : " << targetY << endl;

    while (true) {

        robot->Read();
        double currentY = pp->GetYPos();
        double yDiff;

        if (targetY > currentY) {
            yDiff = targetY - currentY;
        } else {

            /*e.g if robot is at X = 10, and wants to move left 8 units:
             * target is when X = 2 +/- 0.05
             * currentX will be 10 to start, so xDiff = 10 - 2 = 8. move the robot 1 unit to the left
             * xDiff is now (10-1)-2 = 9-7 so it is approaching the location.
             */
            yDiff = currentY - targetY;
        }

        difference = abs(targetY - currentY);


        difference = yDiff;

        cout << "difference : xDiff: " << difference << " " << yDiff << endl;
        if (difference < 0) {
            difference = abs(yDiff);
        }

        if (difference < 0.05) {
            pp->SetSpeed(0, 0);
            return;
        }
else{
pp->SetSpeed(0.1,0);
}

   }    
}

void drawSquare(PlayerClient *robot, Position2dProxy *pp) {

    moveDistanceAlongX(robot, pp,  -1);
    moveDistanceAlongY(robot, pp,  -1);
    moveDistanceAlongX(robot, pp,  1);
    moveDistanceAlongY(robot, pp, 1);

}

int main(int argc, char *argv[]) {


    PlayerClient robot("192.168.226.18");
    SonarProxy sp(&robot, 0);
    Position2dProxy pp(&robot, 0);

    /*
     * Request the ability to access the position and ranger
     * geometries to allow to collision detection
     */

    pp.SetMotorEnable(true);
    robot.Read();

	//turnTo(&robot, &pp, 180);
	while(true){	
	robot.Read();
	std:: cout << "sonar 3 : " << sp << "\r" << std::endl;
	if(sp[3] < 0.500 || sp[4] <0.500){
	pp.SetSpeed(0,0);
	turnTo(&robot, &pp, 180);
	}
	else if(sp[11] < 0.500 || sp[12] <0.500){
	pp.SetSpeed(0,0);
	turnTo(&robot, &pp, 45);
	}
	else if((sp[3] > 0.500 || sp[4] > 0.500) && (sp[11] < 0.500 || sp[12] <0.500)){
	turnTo(&robot, &pp, 0);
	pp.SetSpeed(0.1, 0);


	}
	else if(sp[0] < 0.500){
	pp.SetSpeed(0,0);
	turnTo(&robot, &pp, 90);
	}
	else if(sp[7] < 0.500){
	pp.SetSpeed(0,0);
	turnTo(&robot, &pp, 90);
	}
	else{
	pp.SetSpeed(0.1,0);
	}
}
   }





