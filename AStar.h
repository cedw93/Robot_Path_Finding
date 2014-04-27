/*
 * main.h
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"

/*
 * This header file is designed to provide the necessary function protypes required in order
 * perform an A* search, give an int[x][y] representation of the problem.
 *
 * This will be used as part of the CS26410 Moudle which is taught by Aberyswyth university
 * (2014) as part of the Moudles on offer by the Computer Science Department.
 *
 * Include this head using #inclue "AStar.h" if you want to use this header and the AStar.cpp
 * files in you own projects.
 *
 */

//the argument here is a list which will contain the path
int StartSearch(std::list<Node*>& v);

//used in the child generation stage
Node* initiateStart(int m[20][20]);
Node* generateLeftChild(Node* parent, int m[20][20]);
Node* generateRightChild(Node* parent, int m[20][20]);
Node* generateAboveChild(Node* parent, int m[20][20]);
Node* generateBelowChild(Node* parent, int m[20][20]);

//these methods stop infinite loops during the search
bool checkInClosedList(std::vector<Node*>& v, int x, int y);
bool placeInOpen(std::list<Node*>& v,int x, int y);

void checkPath(Node *end, int m[20][20], std::list<Node*>&);
//heuristic cost function.
void calcManhattanDistance(Node *node, int m[20][20]);


#endif /* ASTAR_H_ */
