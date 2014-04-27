/*
 * Node.h
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#ifndef NODE_H_
#define NODE_H_

/*
 * The Node class is used to model a particular state in the state space for
 * the current A* search.
 *
 * A Node has an X and a Y coordinate as well as a value which can be used to check move validity.
 *
 * As is the case with an A* search, every state must have a cost and a parent, This Node class
 * handles the parent which is simply a pointer to another Node (Node*) and the costs are defined
 * as follows:
 * fCost = the total cost (gCost + hCost)
 * gCost = the current path cost: How much has it cost to get here?
 * hCost = the heuristic cost: this is calculated using the Manhattan distance from this Node to the goal
 */

class Node{

private:

	int xCoord;
	int yCoord;
	int value;
	double fCost;
	double gCost;
	double hCost;
	Node* parent;
	char direction;

public:

	Node();
	Node(int x, int y, int value, int cost, Node* parent, char direction);
	void setParent(Node* parent);
	int getX();
	int getY();
	int getValue();
	char getDirection();
	double getHCost();
	double getFCost();
	double getGCost();
	Node* getParent();
	void setHCost(double hCost);
	~Node();
};


/*
 * This is used to sort the std::list<Node*>. You must write a custome comparator in order
 * to specify how the actual list will be sorted. In this instance the list will be sorted
 * in terms of fCost and the lower the fCost the higher presidence (lower index) the Node
 * will be in the list.
 *
 * This effective allows the use of a priority queue which is what A* uses without having the
 * hassle of not being able to iterate the priority queue provided by the C++ libriaries.
 *
 * To sort a list of Node* based on this comparator siply call std::list.sort(NodeComparator())
 *
 * The general premise for this was adapted from: http://stackoverflow.com/a/16507656/2942536
 */

struct NodeComparator {
	bool operator()(Node* first, Node* second) {

		return (first->getFCost() < second->getFCost());

	}
};

#endif /* NODE_H_ */
