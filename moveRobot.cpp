
#include <libplayerc++/playerc++.h>

#include "moveRobot.h"
#include "robotTurn.h"

//Using PLayerCc to simplify the code slightly.
using namespace PlayerCc;

/*
 * This function is used to control the robots up and down movements, given a
 * specified distance, or more formally this function is used to give the robot
 * instructions which are then used to navgiate along its Y axis given a specified
 * distance to travel.
 *
 * The arguments for this function are the current instance of PlayerCc::PlayerClient
 * which acts as the robot, the current array on sonars, the PlayerCc::Position2dProxy
 * so you can access the getX and getY + other positioning functions
 * functions PlayerCc::RangerProxy which is used for basic collision detection
 * and finally a double which specified how far along the Y axis you want the robot to move.
 * There is a tolerance of 0.2m either side of this movement, so it is not 100% accurate.
 */

void moveDistanceAlongY(PlayerClient *robot, Position2dProxy *pp,
		RangerProxy *sp, double distance) {

	//again namespace just to simplify the prints, e.g. cout doesnt have to be writted std::cout
	using namespace std;

	//Call Read on the robot to correctly update it's readings
	robot->Read();
	//startY will be the robots current Y pos
	double startY = pp->GetYPos();
	double difference;

	double targetY;

	/*
	 * Basic conditional evaluation here, if the distance is greater than 0, then you want to
	 * go forward that amount of units, and it the distance is less than 0, then you want to
	 * in the opposite direction that amount of units.
	 *
	 * A simple way to do this is determine which way you want to go using the above logic, and
	 * and turn the robot to face that way before moving.
	 * e.g:
	 * if distance is -2 then turn the robot to face down using turnTo(-90) (-90 degrees).
	 * also check to see if the distance specified isnt too small because the robot will never move
	 * return from the function if this is the case.
	 */

	if (distance > 0.05) {
		turnTo(robot, pp, 90);
		//face up
	} else if (distance < 0) {

		turnTo(robot, pp, -90); // face down

	} else {
		return;
	}

	/* The robots target Y is the sum of the robots startY + the distance you want to move
	 * e.g:
	 * startY = 6.0000
	 * distance = -2.0000
	 * targetY = 6.0000 + (-2.0000) = 4.0000
	 *
	 */

	targetY = startY + distance;

	//simple console prints to check what is actually happening
	cout << "startY : " << startY << "\n";
	cout << "desitnation Y : " << targetY << endl;

	while (true) {

		robot->Read();
		double currentY = pp->GetYPos();
		double yDiff;

		if (targetY > currentY) {
			yDiff = targetY - currentY;
		} else {

			/*e.g if robot is at Y = 10, and wants to move left 8 units:
			 * target is when Y = 2 +/- 0.05
			 * currentY will be 10 to start, so xDiff = 10 - 2 = 8. move the robot 1 unit to the left
			 * yDiff is now (10-1)-2 = 9-7 so it is approaching the location.
			 */
			yDiff = currentY - targetY;
		}

		//after the movement check the current disatnce from the specified goal
		difference = abs(targetY - currentY);


		difference = yDiff;

		cout << "difference : yDiff: " << difference << " " << yDiff << endl;
		if (difference < 0) {
			//use std::abs to prevent problems with having a less than 0 distance reading
			difference = abs(yDiff);
		}

		//this is the amount of tolerance stop within 0.25m of the goal, this is a reasonable tolerance.
		if (difference < 0.025) {
			pp->SetSpeed(0, 0);
			return;
		}

		/* Very simple colision detection using the front and the two side sonars (0,3,7 respectively)
		 * This should be improved to use more sonars and a better colision avoidance system, but this
		 * collision detection does actually work and suit it's purpose, and since we are following a given
		 * path and not 'randomly' moving this is suffcient for this purpose.
		 *
		 */

		if (sp->GetRange(3) < 0.250) {
			//if there is an obstacle within 0.25m in front, stop the robot and move
			pp->SetSpeed(0, 0);
			return;
		} else {
			//move 0.1m per second
			pp->SetSpeed(0.1, 0);
		}

		//if there is an obstacle to the robots right hand sand and within 0.25m turn away from this object
		if(sp->GetRange(7) < 0.250){
			pp->SetSpeed(0,0.2);
		}else if(sp->GetRange(0) < 0.250){
			//if there is an obstacle to the robots left hand sand and within 0.25m turn away from this object
			pp->SetSpeed(0,-0.2);
		}

		//print sonar readings, just for fun
		cout << "Sonar 3: " << sp->GetRange(3) << endl;
		cout << "Sonar 7: " << sp->GetRange(7) << endl;
		cout << "Sonar 0: " << sp->GetRange(0) <<endl;
	}
}

/*
 * This function is used to control the robots up and down movements, given a
 * specified distance, or more formally this function is used to give the robot
 * instructions which are then used to navgiate along its X axis given a specified
 * distance to travel.
 *
 * The arguments for this function are the current instance of PlayerCc::PlayerClient
 * which acts as the robot, the current array on sonars, the PlayerCc::Position2dProxy
 * so you can access the getX and getY + other positioning functions
 * functions PlayerCc::RangerProxy which is used for basic collision detection
 * and finally a double which specified how far along the X axis you want the robot to move.
 * There is a tolerance of 0.2m either side of this movement, so it is not 100% accurate.
 */

void moveDistanceAlongX(PlayerClient *robot, Position2dProxy *pp,
		RangerProxy *sp, double distance) {

	//again namespace just to simplify the prints, e.g. cout doesnt have to be writted std::cout
	using namespace std;

	//Call Read on the robot to correctly update it's readings
	robot->Read();
	//startY will be the robots current Y pos
	double startX = pp->GetXPos();
	double difference;

	double targetX;

	/*
	 * Basic conditional evaluation here, if the distance is greater than 0, then you want to
	 * go forward that amount of units, and it the distance is less than 0, then you want to
	 * in the opposite direction that amount of units.
	 *
	 * A simple way to do this is determine which way you want to go using the above logic, and
	 * and turn the robot to face that way before moving.
	 * e.g:
	 * if distance is -2 then turn the robot to face down using turnTo(-90) (-90 degrees).
	 * also check to see if the distance specified isnt too small because the robot will never move
	 * return from the function if this is the case.
	 */

	if (distance > 0.05) {
		turnTo(robot, pp, 0);
		//move to the right
	} else if (distance < 0) {
		turnTo(robot, pp, 180); // move left

	} else {
		return;
	}

	/* The robots target Y is the sum of the robots startY + the distance you want to move
	 * e.g:
	 * startY = 6.0000
	 * distance = -2.0000
	 * targetY = 6.0000 + (-2.0000) = 4.0000
	 *
	 */

	targetX = startX + distance;

	//simple console prints to check what is actually happening
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


		//after the movement check the current disatnce from the specified goal
		difference = abs(targetX - currentX);


		difference = xDiff;

		cout << "difference : xDiff: " << difference << " " << xDiff << endl;
		if (difference < 0) {
			//use std::abs to prevent problems with having a less than 0 distance reading
			difference = abs(xDiff);
		}

		//this is the amount of tolerance stop within 0.25m of the goal, this is a reasonable tolerance.
		if (difference < 0.025) {
			pp->SetSpeed(0, 0);
			return;
		}


		/* Very simple colision detection using the front and the two side sonars (0,3,7 respectively)
		 * This should be improved to use more sonars and a better colision avoidance system, but this
		 * collision detection does actually work and suit it's purpose, and since we are following a given
		 * path and not 'randomly' moving this is suffcient for this purpose.
		 *
		 */
		if (sp->GetRange(3) < 0.250) {

			pp->SetSpeed(0, 0);
			return;
		} else {
			pp->SetSpeed(0.1, 0);
		}


		//if there is an obstacle to the robots right hand sand and within 0.25m turn away from this object
		if(sp->GetRange(7) < 0.250){
			pp->SetSpeed(0,0.2);
		} else if(sp->GetRange(0) < 0.250){
			//if there is an obstacle to the robots left hand sand and within 0.25m turn away from this object
			pp->SetSpeed(0,-0.2);
		}

		cout << "Sonar 3: " << sp->GetRange(3) << endl;
		cout << "Sonar 7: " << sp->GetRange(7) << endl;
		cout << "Sonar 0: " << sp->GetRange(0) <<endl;
	}

}
