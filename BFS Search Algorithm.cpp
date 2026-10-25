#include <iostream>   //cin,cout
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


using namespace std;
struct mcState
{
	bool boatPresent; //true if boat is on the original side
	int mis; //number of missionaries on the original side
	int can; //number of cannibals on the original side
};
// Start = { 1,3,3 };  Goal = { 0,0,0 };

int state2id(mcState s) {
	return s.boatPresent * 100 + s.mis * 10 + s.can;
}

mcState id2state(int id) {
	bool b = bool(id / 100);
	id = id % 100;
	int m = id / 10;
	int c = id % 10;
	return { b,m,c };
}


struct mcNode    //structure of each node in the tree
{
	int stateId;
	int parent;         //the stateid of the parent node
	double costG;       //g(n), cost (1 per step) from start to present
	int action;   //1=one cannibal on the boat; 2=two cannibals; 10=one missionary; 20=two missionaries; 11=one missionary+one cannibal 
};


vector<mcNode> Expand(mcNode curr);

bool validState(mcState x, int M = 3, int C = 3);
vector<mcNode> breadth_first_search_MC();
vector<mcNode> trace(mcNode traceNode, vector<mcNode> NodesReached);

/**********Function for text display*******************************************************************************************/
void printNode(mcNode x)
{
	cout << "State: " << x.stateId << "; Parent:" << x.parent << "; Cost: " << x.costG << "; Action: " << x.action << endl;
}

void display(mcState x, int M = 3, int C = 3, int B = 2)
{
	string Sm = "MMMMMMMMMMMMMMMMMMMM", Sc = "CCCCCCCCCCCCCCCCCCC", Sb = "___________", Ss = "         ";

	if (x.boatPresent)
		cout << "\n\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "\n      " << Ss.substr(0, B);
	cout << Sm.substr(0, x.mis) << " " << Sc.substr(0, x.can) << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (!x.boatPresent)
		cout << "\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "      " << Ss.substr(0, B);
	cout << Sm.substr(0, M - x.mis) << " " << Sc.substr(0, C - x.can) << endl;

}

/******************************************************************************************************************************/


int main()
{

 	vector<mcNode> path = breadth_first_search_MC();
	int n1 = path.size();
	if (n1 > 0)
	{

		cout << "Pathsize=" << n1 << endl;
		for (int i = n1 - 1; i >= 0; i--)
		{
			system("cls");
			int z = path[i].stateId;
			mcState s = id2state(z);
			display(s);
			if (i > 0)
				cout << "\nNext step : " << path[i - 1].action << endl;
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");
	return 0;
}


bool validState(mcState s, int M, int C)
{
	int mo = M - s.mis, co = C - s.can; //numbers of the other side of the river 
	if (s.mis < 0 || s.can < 0 || mo < 0 || co < 0)  //numbers have gotten negative
		return false;
	if (co > mo && mo > 0)
		return false;
	if (s.can > s.mis && s.mis > 0)
		return false;
	return true;
}

vector<mcNode> Expand(mcNode curr)
{
	int t = curr.stateId;
	mcState s = id2state(t);
	mcState new_s; //new state

	mcNode newnode;
	vector<mcNode> children;
	newnode.parent = curr.stateId;
	newnode.costG = curr.costG + 1;
	if (s.boatPresent)
	{
		new_s.boatPresent = false;

		//1=one cannibal on the boat; 
		new_s.mis = s.mis; new_s.can = s.can - 1;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = -1;
			children.push_back(newnode);
		}
		//2=two cannibals; 
		new_s.mis = s.mis; new_s.can = s.can - 2;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = -2;
			children.push_back(newnode);
		}
		//10=one missionary; 
		new_s.mis = s.mis - 1; new_s.can = s.can;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = -10;
			children.push_back(newnode);
		}

		//20=two missionaries; 
		new_s.mis = s.mis - 2; new_s.can = s.can;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = -20;
			children.push_back(newnode);
		}

		//11=one missionary+one cannibal
		new_s.mis = s.mis - 1; new_s.can = s.can - 1;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = -11;
			children.push_back(newnode);
		}
	}
	else
	{
		new_s.boatPresent = true;

		//1=one cannibal on the boat; 
		new_s.mis = s.mis; new_s.can = s.can + 1;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = 1;
			children.push_back(newnode);
		}
		//2=two cannibals; 
		new_s.mis = s.mis; new_s.can = s.can + 2;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = 2;
			children.push_back(newnode);
		}
		//10=one missionary; 
		new_s.mis = s.mis + 1; new_s.can = s.can;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = 10;
			children.push_back(newnode);
		}

		//20=two missionaries; 
		new_s.mis = s.mis + 2; new_s.can = s.can;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = 20;
			children.push_back(newnode);
		}

		//11=one missionary+one cannibal
		new_s.mis = s.mis + 1; new_s.can = s.can + 1;
		if (validState(new_s))
		{
			newnode.stateId = state2id(new_s);
			newnode.action = 11;
			children.push_back(newnode);
		}

	}

	return children;

}

vector<mcNode> breadth_first_search_MC()
{
	//intialize the beginning state 
	mcState initial;
	initial.boatPresent = true;
	initial.mis = 3;
	initial.can = 3;

	//intialize the goal state 
	mcState goal;
	goal.boatPresent = false;
	goal.mis = 0;
	goal.can = 0;

	//set the goal state id 
	int goalId = state2id(goal);

	//set the first node to the beginning state 
	mcNode firstNode;
	//using the state to stateId to establish a state id for the beginning node 
	firstNode.stateId = state2id(initial);
	//setting action = 0 meaning that no action is taken 
	firstNode.action = 0;
	//setting the parent Id to -1234 so that later we can recognize the node has no parent
	firstNode.parent = -1234;
	//setting first node cost to nothing to not interfere with calculations later
	firstNode.costG = 0; 
	//initialize the node variable 
	mcNode node;
	//initialize the state variable 
	int state;
	//the vector that will be returned 
	vector<mcNode> returnNodes;

	//if the node is the goal state 
	if (firstNode.stateId == goalId)
	{
		returnNodes.push_back(firstNode);
		return returnNodes;
		//return firstNode;
	}

	// build the frontier queue 
	queue<mcNode> frontier;
	frontier.push(firstNode);
	//build the reached vector of the nodes 
	vector<mcNode> reached;
	vector<int> reachedNumber;
	//put the first node into the reached vector 
	reached.push_back(firstNode);
	reachedNumber.push_back(firstNode.stateId);
	//bool for checking if somethign is in reached
	bool inReached; 
	//frontier Children stores the child nodes to evaluate before they are either the goal
	//state or are added to the frontier
	vector<mcNode> frontierChildren;

	while (!frontier.empty())
	{
		node = frontier.front();
		frontier.pop();
		//for each loop with expanding the children in the node 
		frontierChildren = Expand(node);
		for (mcNode child : frontierChildren)
		{
			state = child.stateId;
			//if the child state is the goal state 
			if (state == goalId)
			{
				//this is to trace the path back to the beginning node
				returnNodes = trace(child, reached);
				return returnNodes;
			}
			inReached = false; 
			for (int check : reachedNumber)
			{
				if (state == check)
				{
					inReached = true; 
					break; 

				}
			}

			//then putting a node in Reached depending on if the state alreadly exists in it or not
			if (inReached == false)
			{
				reached.push_back(child);
				frontier.push(child);
				reachedNumber.push_back(child.stateId);
			}

		
		}

	}
	return returnNodes;





};

//function to trace a node back to its parent id 
vector<mcNode> trace(mcNode traceNode, vector<mcNode> NodesReached)
{
	//traceNode is the final node of the path 
	//NodesReached is the reached vector in the search function 
	//finalNodes2 is what will be returned
	vector<mcNode> finalNodes; 
	mcNode node3 = traceNode;
	//helps to store a parentId to look for
	int search;
	bool go = true; 
	vector<mcNode> finalNodes2; 
	while (node3.parent != -1234)
	{
		finalNodes.push_back(node3);
		//stores the parent ID to look for the coresponding node 
		search = node3.parent;
		for (mcNode node : NodesReached)
		{
			//if the parent id is a match for a node in NodesReached 
			if (node.stateId == search)
			{
				node3 = node;
				break;
			}
		}


	}
	//there should be the last node which is the beginning node
	//that doesn't have a parent to push into finalNodes 
	finalNodes.push_back(node3);
	//flip the vector 
	reverse(finalNodes.begin(), finalNodes.end());
	finalNodes2 = finalNodes;
	if (go == true)
	{
		return finalNodes; 
	}
	return finalNodes2;
}