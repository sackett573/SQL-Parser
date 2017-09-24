#include "stdafx.h"
#include "QueryTree.hpp"
#include "RelAlg.hpp"
#include <iostream>

QueryTree::QueryTree()
{

}

QueryTree::~QueryTree()
{
	Tree.clear();
}

void QueryTree::makeTree(const std::string& data, const int key)
{
	int posFront;
	int posBack;
	std::string holder;
	if (data.find(unionSymbol, 0) != std::string::npos)
	{
		holder += unionSymbol;
		Tree.insert(std::pair<int, std::string>(key, holder));
		makeTree(data.substr(0, data.find(holder, 0)), key * 2);
		makeTree(data.substr(data.find(holder, 0) + 1, data.size()), (key * 2) + 1);
	}
	else if (data.find("-", 0) != std::string::npos)
	{
		Tree.insert(std::pair<int, std::string>(key, "-"));
		makeTree(data.substr(0, data.find("-", 0)), key * 2);
		makeTree(data.substr(data.find("-", 0) + 1, data.size()), (key * 2) + 1);
	}
	else if (data.find(interSymbol, 0) != std::string::npos)
	{
		holder += interSymbol;
		Tree.insert(std::pair<int, std::string>(key, holder));
		makeTree(data.substr(0, data.find(holder, 0)), key * 2);
		makeTree(data.substr(data.find(holder, 0) + 1, data.size()), (key * 2) + 1);
	}
	else if (data.find(pi, 0) != std::string::npos)
	{
		posFront = data.find("(", 0);
		if (data[posFront - 1] == 'X')
		{
			posFront = data.substr(posFront + 1, data.size() - posFront - 2).find("(", 0) + posFront + 1;
			std::cout << data.substr(posFront + 1, data.size() - posFront - 2).find("(", 0) + posFront + 1 << std::endl;
		}
		Tree.insert(std::pair<int, std::string>(key, data.substr(0, posFront)));
		makeTree(data.substr(posFront + 1, data.size() - posFront - 2), (key * 2) + 1);
	}
	else if (data.find("Sort", 0) != std::string::npos)
	{
		if (data.find(sigma, 0) != std::string::npos && data.find(sigma, 0) <
			data.find("Sort", 0))
		{
			posFront = data.find("(", 0);
			if (data[posFront - 1] == 't')
			{
				if (data[posFront - 2] == 'n')
				{
					if (data[posFront - 3] == 'u')
					{
						if (data[posFront - 4] == 'o')
						{
							if (data[posFront - 5] == 'C')
							{
								posFront = data.substr(posFront + 1, data.size() - posFront - 2).find("(", 0) + posFront + 1;
							}
						}
					}
				}
			}
			Tree.insert(std::pair<int, std::string> (key, data.substr(0, posFront)));
			holder = data.substr(posFront + 1, data.size());
			Tree.insert(std::pair<int, std::string>((key * 2) + 1, holder.substr(0, holder.find("(", 0))));
			makeTree(holder.substr(holder.find("(", 0) + 1, holder.size()), ((((key * 2) + 1) * 2) + 1));
		}
		else
		{
			Tree.insert(std::pair<int, std::string>(key, data.substr(0, data.find("("))));
			makeTree(data.substr(data.find("(", 0) + 1, data.size() - data.find("(", 0) - 2), ((key * 2) + 1));
		}
	}
	else if (data.find(sigma, 0) != std::string::npos)
	{
		posFront = data.find('(', 0);
		Tree.insert(std::pair<int, std::string>(key, data.substr(0, posFront)));
		makeTree(data.substr(posFront + 1, data.size() - posFront - 2), (key * 2) + 1);
	}
	else if (data.find('X', 0) != std::string::npos)
	{
		Tree.insert(std::pair<int, std::string>(key, "X"));
		makeTree(data.substr(0, data.find('X', 0)), key * 2);
		makeTree(data.substr(data.find('X', 0) + 1, data.size()), (key * 2) + 1);
	}
	else
	{
		if (data[0] == '(')
		{
			Tree.insert(std::pair<int, std::string>(key, data.substr(1, data.size() - 1)));
		}
		else if (data.find(')', 0))
		{
			Tree.insert(std::pair<int, std::string>(key, data.substr(0, data.find(')', 0))));
		}
		else
		{
			Tree.insert(std::pair<int, std::string>(key, data));
		}
	}
	return;
}

void QueryTree::printTree()
{
	int maxKey;
	int key = 1;
	int pos;
	int depth = 0;
	int i = 1;
	int space = 40;
	bool second = false;
	int checkSecond = 0;
	std::vector<std::string> words;
	std::vector<std::string> connections;
	for (std::map<int, std::string>::iterator ii = Tree.begin(); ii != Tree.end(); ++ii)
	{
		maxKey = (*ii).first;
	}
	while (maxKey > i)
	{
		i = i * 2;
		depth++;
	}
	words.resize(depth);
	connections.resize(depth - 1);
	space = 80 - (Tree.at(1).size() / 2);
	for (int i = 0; i < space; i++)
	{
		words[0] += " ";
	}
	words[0] += Tree.at(1);
	if (Tree.at(1).find(pi, 0) != std::string::npos)
	{
		for (int i = 0; i < 80; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "|";
		for (int i = 81; i < 160; i++)
		{
			connections[0] += " ";
		}
	}
	else
	{
		for (int i = 0; i < 40; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "/";
		for (int i = 41; i < 120; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "|";
		for (int i = 121; i < 160; i++)
		{
			connections[i] += " ";
		}
	}
	std::cout << words[0] << std::endl;
	std::cout << connections[0] << std::endl;
	for (int i = 1; i < depth; i++)
	{
		if (i == 1)
		{
			space = 40;
		}
		if (i == 2)
		{
			space = 20;
		}
		if (i == 3)
		{
			space = 10;
		}
		if (i == 4 || i == 5 || i == 6)
		{
			space = 5;
		}
		pos = space;
		while (pos < 160)
		{
			if (connections[i - 1][pos] == '/' || connections[i - 1][pos] == '|')
			{
				key = Tree.upper_bound(key)->first;
				for (int k = words[i].size(); k < pos - (Tree.at(key).size() / 2); k++)
				{
					words[i] += " ";
				}
				words[i] += Tree.at(key);
				if (Tree.at(key).find("X", 0) != std::string::npos ||
					Tree.at(key).find("|X|", 0) != std::string::npos)
				{
					if (i < depth - 1)
					{
						for (int k = connections[i].size(); k < pos - space / 2; k++)
						{
							connections[i] += " ";
						}
						connections[i] += "/";
						for (int k = connections[i].size(); k < pos + space / 2; k++)
						{
							connections[i] += " ";
						}
						connections[i] += "|";
					}
				}
				else if (Tree.at(key).find(pi, 0) != std::string::npos ||
					     Tree.at(key).find("Sort", 0) != std::string::npos ||
					     Tree.at(key).find(sigma, 0) != std::string::npos)
				{
					if (i < depth - 1)
					{
						for (int k = connections[i].size(); k < pos; k++)
						{
							connections[i] += " ";
						}
						connections[i] += "|";
					}
				}
			}
			pos = pos + space;
		}
		std::cout << words[i] << std::endl;
		if (i < depth - 1)
		{
			std::cout << connections[i] << std::endl;
		}
	}
}