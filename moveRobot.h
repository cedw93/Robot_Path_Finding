#ifndef MOVEROBOT_H_
#define  MOVEROBOT_H_

#include <libplayerc++/playerc++.h>

/* This header file simply provides the interface for the system to access the function which tell the robot to move
 * along its axis. The PlayerCc::PlayerClient is provided by an external library for use with player stage, this also
 * applies to the PlayerCc::RangerProxy. The distance argument is simply how far along the axis you wish to move.
 */

void moveDistanceAlongX(PlayerCc::PlayerClient *robot, PlayerCc::Position2dProxy *pp, PlayerCc::RangerProxy *sp, double distance);
void moveDistanceAlongY(PlayerCc::PlayerClient *robot, PlayerCc::Position2dProxy *pp, PlayerCc::RangerProxy *sp, double distance);

#endif /*  MOVEROBOT_H_ */
