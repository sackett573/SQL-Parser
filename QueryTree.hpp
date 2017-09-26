//QueryTree.hpp
//Objective: contains the QueryTree class which takes relational algebra,
//           converts it into a query tree and then performs optimizations on that
//           tree

#ifndef QUERYTREE_HPP
#define QUERYTREE_HPP

#include <map>
#include <vector>
#include <string>

class QueryTree
{
	private :
		std::map<int, std::string> Tree;
    public :
		QueryTree();
		~QueryTree();
		//Purpose: makes a query tree out of relational algebra
		//Precondition: must have valid relational algebra
		//Postcondition: stores relational algebra into Tree member variable as query tree
		void makeTree(const std::string& data, const int key);
		//Purpose: performs the first optimization by moving select down
		//Precondition: must have valid tree
		//Postcondition: moves select statements further down treee
		void opt1(int key, std::vector<std::string>& values);
		//Purpose: performs the second optimization by merging select and cartesian product
		//Precondition: must have performed first optimization
		//Postcondition: merges select statements with cartesian products in Tree
		void opt2(int key, std::vector<std::string>& values);
		//Purpose: performs the third optimization by projecting only the necessary attributes
		//Precondition: must have performed second optimization
		//Postcondition: adds project only necessary attributes into the tree
		void opt3(int key, std::vector<std::string>& values);
		//Purpose: prints the query tree
		//Precondition: Tree is a valid query Tree
		//Postcondition: outputs the tree to the screen
		void printTree();
		//clears of the tree of data
		void clearTree();
};

#endif
