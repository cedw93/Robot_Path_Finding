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
#include <list>

#include "AStar.h"
#include "Node.h"
#include "robotTurn.h"
#include "moveRobot.h"

using namespace PlayerCc;

/*
 * The main is used to run the whole application.
 *
 * This function calls the StartSearch function defined in AStar.cpp which
 * pefroms an A* search on the current occupancy grid. The goal path is then returned
 * and iterated, and the corresponding move positions and then trasnlated into
 */

int main(int argc, char *argv[]) {

	//declare necessary elements, such as the robot and the PlayerClient
	PlayerClient robot("localhost");
	RangerProxy sp(&robot, 0);
	Position2dProxy pp(&robot, 0);

	/*
	 * Request the ability to access the position and ranger
	 * geometries to allow to collision detection
	 */

	pp.RequestGeom();
	sp.RequestGeom();
	//make sure all the sensors and components have loaded properly before progressing
	while (!sp.IsValid()) {
		robot.Read();
	}

	pp.SetMotorEnable(true);
	robot.Read();

	Node *temp;
	//this is the container for the goal path returned from the A* search
	std::list<Node*> path;
	//start the A* search, path the list<Node*> for the goal as an argument as a reference to this path is needed
	StartSearch(path);
	//print out the order of moves, simply athetic servers no real purpose to the robot itself.
	std::cout << "Order of moves needed from start to goal:" << std::endl;
	for (std::list<Node*>::iterator iter = path.begin(); iter != path.end(); ++iter){
		if((*iter)->getDirection() != 's'){
			std::cout << (*iter)->getDirection() << ", ";
		}
	}
	std::cout << std::endl;

	/*
	 * Whilst the size of the list<Node*> goalPath is no empty, get and pop the front of the list.
	 * From this Node* returned from the front of the list, get the value of the direction variable
	 * and translate that char value into a robot move, using a case switch.
	 * direction d: move robot down the Y axis, so y-1
	 * direction u: move robot up the Y axis, so y+1
	 * direction r: move robot right along the X axis, so X+1
	 * direction l: move robot left along the X axis, so X-1
	 *
	 * When the list<Node*> goalPath is empty, then the robot is at the goal location.
	 */

	while(!path.empty()){
		Node *temp = path.front();
		path.pop_front();
		char value = temp->getDirection();
		switch(value){
		case 'd':
			moveDistanceAlongY(&robot, &pp, &sp, -1);
			break;
		case 'u':
			moveDistanceAlongY(&robot, &pp, &sp, 1);
			break;
		case 'r':
			moveDistanceAlongX(&robot, &pp, &sp, 1);
			break;
		case 'l':
			moveDistanceAlongX(&robot, &pp, &sp, -1);
			break;
		case 's':
			break;
		}
	}


}



