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
		void makeTree(const std::string& data, const int key);
		void opt1(int key, std::vector<std::string>& values);
		void opt2(int key, std::vector<std::string>& values);
		void opt3(int key, std::vector<std::string>& values);
		void printTree();
};

#endif
