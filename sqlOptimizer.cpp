//sqlOptimizer.cpp
//Objective: to make an SQL parser that can read input, turn that input into
//           relational algebra , turn that relational algebra into a query tree
//           and then perform optimizations on that tree

#include "stdafx.h"
#include <iostream>
#include <string>
#include "RelAlg.hpp"
#include "QueryTree.hpp"

int main()
{
	RelationalAlgebra input;
	QueryTree inputTree;
	std::vector<std::string> values;
	if (input.parseInput())
	{
		std::cout << "Relational Algebra: " << input.getEquation() << std::endl;
		if (!input.getNestedStatement().empty())
		{
			std::cout << input.getNestedStatement() << std::endl;
		}
		inputTree.makeTree(input.getEquation(), 1);
		std::cout << "Query Tree: " << std::endl;
		inputTree.printTree();
		std::cout << "Optimization 1:" << std::endl;
		inputTree.opt1(1, values);
		inputTree.printTree();
		std::cout << "Optimization 2:" << std::endl;
		inputTree.opt2(1, values);
		inputTree.printTree();
		std::cout << "Optimization 3:" << std::endl;
		inputTree.opt3(1, values);
		inputTree.printTree();
		inputTree.clearTree();
		if(!input.getNestedStatement().empty())
		{
			std::cout << "Inner Tree:" << std::endl;
			inputTree.makeTree(input.getNestedStatement(), 1);
			inputTree.printTree();
			std::cout << "Optimization 1:" << std::endl;
			inputTree.opt1(1, values);
		  inputTree.printTree();
			std::cout << "Optimization 2:" << std::endl;
		  inputTree.opt2(1, values);
			inputTree.printTree();
			std::cout << "Optimization 3:" << std::endl;
		  inputTree.opt3(1, values);
		  inputTree.printTree();
		}
		inputTree.clearTree();
	}
	else
	{
		std::cout << "That query is incorrect" << std::endl;
	}

	return 0;
}

