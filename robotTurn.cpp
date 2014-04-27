
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

/*
 * This function is designed to turn the robot a specified amount. The amount specified
 * is in degrees not radians. The robots GetYaw returns its current angle in radians,
 * so this is converted into degrees using the rtod functions.
 *
 * This function uses a low turn speed of 0.1 to ensure that a turn is never "missed".
 * There is a tolerance of +/- 3 degress when deciding if a turn is complete or not.
 */

void turnTo(PlayerClient *robot, Position2dProxy *pp, double angle_in_deg) {
	using namespace std;
	robot->Read();
	//get the current angle in degrees
	double currentAngle = rtod(pp->GetYaw());
	double difference;

	cout << "getYaw in degrees: " << currentAngle << "\n";
	cout << "angle in r " << angle_in_deg << "\n";
	cout << "Difference between angles : " << difference << "\n";

	while (true) {
		//Read to get the current angle of the robot
		robot->Read();
		//continue updating the difference away from the angle specified
		difference = rtod(pp->GetYaw()) - angle_in_deg;

		if (difference < 0) {
			difference = abs(difference);
		}
		//tolerance of +/- 3 degrees on the turn
		if (difference < 3) {
			pp->SetSpeed(0, 0);
			return;
		}
		cout << "Difference in angles : " << difference << endl;
		//0.2 movespeed is slow, but faster move speed come at the cost of accuracy
		pp->SetSpeed(0, 0.2);


	}


}
