// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "RelAlg.hpp"
#include "QueryTree.hpp"

int main()
{
	RelationalAlgebra input;
	QueryTree inputTree;
	if (input.parseInput())
	{
		std::cout << input.getEquation() << std::endl;
		if (!input.getNestedStatement().empty())
		{
			std::cout << input.getNestedStatement() << std::endl;
		}
		inputTree.makeTree(input.getEquation(), 1);
		inputTree.printTree();
	}
	else
	{
		std::cout << "That query is incorrect" << std::endl;
	}

	return 0;
}

