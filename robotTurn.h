
#ifndef ROBOTTURN_H_
#define ROBOTTURN_H_

#include <libplayerc++/playerc++.h>


/* This function prototype allows the system to use custom and persicion turns in the robots movements.
 * It takes 3 arguments, the first being the instance of the PlayerCc::PlayerClient which you want to turn,
 * the PlayerCc:Position2dProxy so you are able to get the coordinates and positions of the robot, and the
 * angle in degress in the double format which you want the robot to turn.
 */

void turnTo(PlayerCc::PlayerClient *robot, PlayerCc::Position2dProxy *pp, double angle_in_deg);

#endif /* ROBOTTURN_H_ */
