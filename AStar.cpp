/*
 * AStar.cpp
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <list>

#include "Node.h"
#include "AStar.h"


/*
 * This is an A* (A star) search, which uses the combined hueristic costs and
 * the path goal of each node in order to select the optimal path for a given
 * state space.
 * 
 * This code was written by me, Chris Edwards (che16@aber.ac.uk) with some help from
 * online resources, and using the knowledge gained from the Aberyswyth CS26110 Artificial
 * Inteligence module.
 * 
 * The heuristic used in this A* is currently the Manhattan distance which is:
 * 
 * given two coordinates in terms of [x1][y2] and [x2][y2] then the manhattan distance between
 * [0][1] and [2][1] is calculated using:
 * 
 * abs((x1 - x2) + (y1 - y2)) thus, 0 - 2 + 1-1   = -2 + 0 = abs(-2) = 2.
 * 
 * This is an admissable heurisic so A* will find the optimal path...
 * 
 * This A* does not currently allow diagonal movements which will obviously impact the optimal
 * of the result.
 * 
 * Some resources used for development and resolving problems can be found:
 * 
 * udefined reference error on Node*:
 * http://stackoverflow.com/questions/22382566/c-i-change-my-listand-code-so-it-now-handles-node-rather-than-node-objects
 * printing the path problems:
 * http://stackoverflow.com/questions/22361308/c-after-finding-the-path-from-an-a-search-printing-the-path-continually-prin
 * Eclpise CDT compilation problems:
 * http://stackoverflow.com/questions/22392540/c-compiling-my-code-in-eclpise-cdt-it-works-fine-but-doing-so-from-the-comman
 * 
 * All of the above, were questions asked me by under the user name Chris Edwards. The code in those
 * questions was written by me and only me.
 * 
 * The parameter to this function is a list where the Node* for the optimal path to goal
 * will be placed.
 * 
 */

int StartSearch(std::list<Node*>& path){

	/*
	 * This is a hardcoded representation of th map which will be searched
	 * as the path finding process. This could potental be loaded from a file
	 * or #define'd but in all honesty it is not of vital importance, but in terms
	 * of maintainability for future projects this should be reviewed.
	 */

	int map[20][20] = {{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,2},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,3,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}};

	using namespace std;

	//we need to store the unexplored nodes, this is also effective a 'priority queue'
	list<Node*> openList;
	//store the explored nodes, the ordering doesnt really matter here
	vector<Node*> closedList;
	//list<Node*> path;

	Node *end;
	Node *start = initiateStart(map);
	openList.push_front(start);




	cout <<"Start index: x " << start->getX() << " y " <<start->getY() << endl;

	/*
	 * The general algorithm behind this process is:
	 *
	 * Put the starting node on the open list
	 *
	 *While the open list is not empty
	 *    find the node with the lowest function cost (f = g+h)
	 *    pop the top of the open list
	 *   generate the current bests successors/children
	 * for each successor
	 *	if successor is the goal, exit and return path
	 *  child's g is equal to the parents g + 1 (each move costs 1)
	 *    child's h = mahattan distance from this point to goal
	 *    child's f = child's g + child's h
	 *   if the child's X and Y are not already in the open list,
	 *  AND
	 *   the child's X and Y are not in the closed list, add to open list
	 * put the parent on the closed list
	 *finishe return the path
	 * 
	 */

	while (!openList.empty()) {

		Node *best = openList.front();
		//pop_front doesnt return anything, so we have to get the front the pop
		openList.pop_front();
		if(!checkInClosedList(closedList, best->getX(), best->getY())){
			calcManhattanDistance(best, map);

			if(best->getValue() == 3){
				//path has been found
				end = best;
				cout <<"end index: x " << end->getX() << " y " <<end->getY() << endl;
				checkPath(end, map, path);
			}

			/*
			 * We need to check if we can move left. we can only move left
			 * is the cell in the given occupancy grid to the left of the current
			 * position is not a 1, and if the current Y value -1 is 0 or greater.
			 * 
			 * This is because a vaue of 1 for a cell signifies a wall which cant be moved to
			 * and a Y value less than 0 means we are outside the bounds of the grid
			 * 
			 */

			if(map[best->getX()][best->getY()-1] != 1 && best->getY() - 1 > -1){
				//check this X and Y is not in the open list
				if(placeInOpen(openList,best->getX(), best->getY() - 1)){
					openList.push_front(generateLeftChild(best, map));
				}
			}
			/*
			 * We need to check if we can move right. we can only move right
			 * is the cell in the given occupancy grid to the right of the current
			 * position is not a 1, and if the current Y value +1 is 19 or less.
			 * 
			 * This is because a vaue of 1 for a cell signifies a wall which cant be moved to
			 * and a Y value greater than 19 means we are outside the bounds of the grid
			 * 
			 */

			if(map[best->getX()][best->getY()+1] != 1 && best->getY() + 1 < 20){
				if(placeInOpen(openList,best->getX(), best->getY() + 1)){
					openList.push_front(generateRightChild(best, map));
				}
			}


			/*
			 * We need to check if we can move up. we can only move up
			 * is the cell in the given occupancy grid to above the current
			 * position is not a 1, and if the current X value -1 is 0 or greater.
			 * 
			 * This is because a vaue of 1 for a cell signifies a wall which cant be moved to
			 * and a Y value less than 0 means we are outside the bounds of the grid
			 * 
			 */

			if(map[best->getX()-1][best->getY()] != 1 && best->getX() - 1 > -1){
				if(placeInOpen(openList,best->getX()-1, best->getY())){
					openList.push_front(generateAboveChild(best, map));
				}
			}

			/*
			 * We need to check if we can move down. we can only move down
			 * is the cell in the given occupancy grid below the current
			 * position is not a 1, and if the current X value +1 is 19 or less.
			 * 
			 * This is because a vaue of 1 for a cell signifies a wall which cant be moved to
			 * and a Y value above 19 means we are outside the bounds of the grid
			 * 
			 */

			if(map[best->getX()+1][best->getY()] != 1 && best->getX() + 1 < 20){
				if(placeInOpen(openList,best->getX()+1, best->getY())){
					openList.push_front(generateBelowChild(best, map));
				}
			}

			//add the current best to the closed list
			closedList.push_back(best);
		}
		/* We need to sort the list now we have added new Nodes. The reason a priority
		 * queue is not used is because you cannot iterate a priority queue in C++.
		 * 
		 * I wanted to iterate through the lists to check the indexs of each Node current in
		 * the open list to prevent the duplicates arrising in the list.
		 * 
		 * I ended up using the list contatiner with a custom comparator struct for the Node
		 * Objects, which generates the effect of having an iterateable priority queue.
		 */
		openList.sort(NodeComparator());
	}

	return 0;
}

/*
 * This is used to locate the starting Node.
 * 
 * Parse the given grid untill a cell has the value 2. When this is
 * located create a new Node with the X and Y coordinates of this value
 * on the heap and return a pointer to this memory address.
 * 
 */

Node* initiateStart(int m[20][20]){

	Node *start;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(m[i][j] == 2){
				start = new Node(i, j, m[i][j], 0, NULL, 's');
			}

		}
	}

	return start;

}

/*
 * Generate the left child of the current parent.
 * This is only called if a left move is in fact possible thus there are no checks
 * to see if a left move is valid inside this actual method itself.
 * 
 * Create a new Node on the heap with the values:
 * 
 * X = the same X as the parent
 * Y = the parents Y - 1
 * value = the value of the occupance grid at grid[X][Y]
 * g = parent g + 1
 * parent = parent
 * direction = 'l'
 * h = manhattan distance
 * 
 * return a pointer to the memory address on the heap of this new Node.
 */

Node* generateLeftChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX(), parent->getY() - 1, m[parent->getX()][parent->getY() - 1],
			parent->getGCost() + 1, parent, 'l');
	calcManhattanDistance(child, m);

	return child;

}

/*
 * Generate the right child of the current parent.
 * This is only called if a left move is in fact possible thus there are no checks
 * to see if a right move is valid inside this actual method itself.
 * 
 * Create a new Node on the heap with the values:
 * 
 * X = the same X as the parent
 * Y = the parents Y + 1
 * value = the value of the occupance grid at grid[X][Y]
 * g = parent g + 1
 * parent = parent
 * direction = 'r'
 * h = manhattan distance
 * 
 * return a pointer to the memory address on the heap of this new Node.
 */

Node* generateRightChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() , parent->getY() + 1, m[parent->getX()][parent->getY() + 1],
			parent->getGCost() + 1, parent, 'r');
	calcManhattanDistance(child, m);

	return child;

}

/*
 * Generate the above child of the current parent.
 * This is only called if an above move is in fact possible thus there are no checks
 * to see if an above move is valid inside this actual method itself.
 * 
 * Create a new Node on the heap with the values:
 * 
 * X = the same X - 1 as the parent
 * Y = the parents Y
 * value = the value of the occupance grid at grid[X][Y]
 * g = parent g + 1
 * parent = parent
 * direction = 'u'
 * h = manhattan distance
 * 
 * return a pointer to the memory address on the heap of this new Node.
 */

Node* generateAboveChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() - 1, parent->getY(), m[parent->getX() - 1][parent->getY()],
			parent->getGCost() + 1, parent, 'u');

	calcManhattanDistance(child, m);

	return child;

}

/*
 * Generate the below child of the current parent.
 * This is only called if a below move is in fact possible thus there are no checks
 * to see if a below move is valid inside this actual method itself.
 * 
 * Create a new Node on the heap with the values:
 * 
 * X = the same X + 1 as the parent
 * Y = the parents Y
 * value = the value of the occupance grid at grid[X][Y]
 * g = parent g + 1
 * parent = parent
 * direction = 'u'
 * h = manhattan distance
 * 
 * return a pointer to the memory address on the heap of this new Node.
 */

Node* generateBelowChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() + 1, parent->getY(), m[parent->getX() + 1][parent->getY()],
			parent->getGCost() + 1, parent, 'd');

	calcManhattanDistance(child, m);

	return child;

}

/*
 * This is the heruitic function for this A* search algorithm.
 * 
 * It uses the mahattan distance which is defined as:
 * 
 * definition from: http://xlinux.nist.gov/dads/HTML/manhattanDistance.html
 * 
 * "The distance between two points measured along axes at right angles. 
 * In a plane with p1 at (x1, y1) and p2 at (x2, y2), it is |x1 - x2| + |y1 - y2|."
 * 
 * This herutitic is admissible because it does not overestimate the cost to the goal, so an
 * optimal solution will always be found.
 * 
 */

void calcManhattanDistance(Node *node, int m[20][20]){

	int tempX;
	int tempY;
	double manhattanDistance;
	int differenceX;
	int differenceY;

	//std::cout << "node x: " << node->getX() << " node y: " << node->getY() << std::endl;

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(m[i][j] == 3){
				tempX = i;
				tempY = j;
			}
		}
	}


	//sum of term difference, none of these can be negative hense the std::abs
	differenceX = tempX - node->getX();
	differenceY = tempY - node->getY();

	manhattanDistance = std::abs(differenceX) + std::abs(differenceY);

	//std::cout << "Manhattan distance: " << manhattanDistance << std::endl;

	node->setHCost(manhattanDistance);

}

/*
 * This function returns a boolean value which is directly related to the contents of
 * the current closed list vector.
 * 
 * Iterate through the members of the closed list and check the values of the
 * current Node* and it's X and Y against the X argument and Y argument of the function.
 * 
 * If the current Node* X and Y values are identical to the argument X and Y, then return true.
 * If there is no matched values for BOTH X and Y, then return false.
 */

bool checkInClosedList(std::vector<Node*>& v,int x, int y){

	for (std::vector<Node*>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		if((*iter)->getX() == x && (*iter)->getY() == y){
			return true;
		}
	}

	return false;

}

/*
 * This function returns a boolean value which is directly related to the contents of
 * the current open list container.
 * 
 * Iterate through the members of the open list and check the values of the
 * current Node* and it's X and Y against the X argument and Y argument of the function.
 * 
 * If the current Node* X and Y values are identical to the argument X and Y, then return true.
 * If there is no matched values for BOTH X and Y, then return false.
 *
 * The list<Node*> argument is simply a reference to the current openList and its elements.
 */

bool placeInOpen(std::list<Node*>& v,int x, int y){

	for (std::list<Node*>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		if((*iter)->getX() == x && (*iter)->getY() == y){
			return false;
		}
	}
	return true;

}

/*
 * This function is used to check the route returned from the A* search algorithm.
 * Also this function is used to populate a list which contains a list of Node* which
 * represent the goal state. This can then be used and transvered in order to pass the
 * required movements from start to goal to the robot or another medium.
 *
 * The passed in arguments are the a Node* which points to the goal node, the current occupancy grid
 * which is of type int[20][20] and the list<Node*> where to path will be stored.
 */

void checkPath(Node *end, int m[20][20], std::list<Node*>& path){
	int tempX, tempY;
	Node *temp = end;
	while(temp != NULL){
		path.push_front(temp);
		tempX = temp->getX();
		tempY = temp->getY();
		m[tempX][tempY] = 4;
		temp = temp->getParent();
	}

}


