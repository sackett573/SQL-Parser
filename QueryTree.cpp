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

void QueryTree::opt1(int key, std::vector<std::string>& values)
{
	
	std::string holder;
	std::string holder2;
	holder = unionSymbol;
	holder2 = interSymbol;
	if(Tree.at(key) == holder || Tree.at(key) == "-" || Tree.at(key) == holder2)
	{
		opt1((key * 2), values);
		opt1(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find(pi, 0) != std::string::npos ||
	        Tree.at(key).find("Sort", 0) != std::string::npos)
	{
		opt1(((key * 2) + 1), values);	
	}
	else if(Tree.at(key).find(sigma, 0) != std::string::npos)
	{
		if(Tree.at((key * 2) + 1).find("Sort", 0) != std::string::npos)
		{
			opt1(((key * 2) + 1), values);
		}
		else
		{
			int pos;
			int pos2;
			holder = Tree.at(key).substr(1, Tree.at(key).size());
			bool isCartesian = false;
			while(holder.find("^", 0) != std::string::npos)
			{
				holder2 = holder.substr(0, holder.find("^", 0));
				if(holder2.find("=", 0) != std::string::npos)
				{
					pos = holder2.find("=", 0);
					if(!isalpha(holder2[pos + 1]))
					{
						values.push_back(holder2);
					}
					else
					{
						isCartesian = true;
					}
				}
				else
				{
					values.push_back(holder2);
				}
				holder = holder.substr(holder.find("^", 0) + 1, holder.size());
			}
			if(holder.find("=", 0) != std::string::npos)
			{
				pos = holder.find("=", 0);
				if(!isalpha(holder[pos + 1]))
				{
					values.push_back(holder);
				}
				else
				{
					isCartesian = true;
				}
			}
			if(isCartesian == false)
			{
				values.clear();
			}
			for(int i = 0; i < values.size(); i++)
			{
				pos = Tree.at(key).find(values[i], 0);
				pos2 = Tree.at(key).rfind('^', pos);
				if(pos2 != std::string::npos)
				{
					Tree.at(key).erase(pos - 1, values[i].size() + 1);
				}
				else if(Tree.at(key).find('^', pos) != std::string::npos)
				{
					Tree.at(key).erase(pos, values[i].size());
				}
			}
			opt1(((key * 2) + 1), values);
		}
	}
	else if(Tree.at(key) == "X")
	{
		opt1((key * 2), values);
		opt1(((key * 2) + 1), values);
	}
	else
	{
		std::vector<std::string> holder3;
		for(int i = 0; i < values.size(); i++)
		{
			int pos;
			pos = values[i].find('.', 0);
			if(Tree.at(key) == values[i].substr(0, pos))
			{
				holder3.push_back(values[i]);
			}
		}
		if(holder3.size() > 0)
		{
			Tree.insert(std::pair<int, std::string> (((key * 2) + 1), Tree.at(key)));
			Tree[key] = sigma;
			for(int i = 0; i < holder3.size(); i++)
			{
				Tree[key] += holder3[i];
				for(int j = 0; j < values.size(); j++)
				{
					if(holder3[i] == values[j])
					{
						values.erase(values.begin() + j);
						break;
					}
				}
			}
		}
	}
}

void QueryTree::opt2(int key, std::vector<std::string>& values)
{
	int nextKey = key;
	int holder;
	std::string strHolder;
	std::string strHolder2;
	std::vector<int> remove;
  strHolder = unionSymbol;
	strHolder2 = interSymbol;
	if(Tree.at(key) == strHolder || Tree.at(key) == strHolder2 ||
	   Tree.at(key) == "-")
	{
		opt2((key * 2), values);
		opt2(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find(pi, 0) != std::string::npos ||
	        Tree.at(key).find("Sort", 0) != std::string::npos)
	{
		opt2(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find(sigma, 0) != std::string::npos)
	{
		nextKey = (2 * nextKey) + 1;
		if(Tree.at(nextKey) == "X")
		{
			holder = (2 * nextKey) + 1;
			if(Tree.at(holder) == "X")
			{
				strHolder2 = Tree.at(key).substr(1, strHolder2.find("^", 0));
				while(strHolder2.find("^", 0) != std::string::npos)
				{
					values.push_back(strHolder2.substr(0, strHolder2.find("^", 0)));
					strHolder2 = strHolder2.substr(strHolder2.find("^", 0) + 1, strHolder2.size());
				}
				values.push_back(strHolder2);
				Tree[key] = "|X|";
				holder = 2 * nextKey;
				if(Tree.at(holder).find(sigma, 0) != std::string::npos)
				{
					Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
					holder = (2 * holder) + 1;
					for(int i = 0; i < values.size(); i++)
					{
						if(Tree.at(holder) == values[i].substr(0, values[i].find(".", 0)) ||
						   Tree.at(holder) == values[i].substr(values[i].find("=", 0) + 1,
							 values[i].rfind(".", values[i].size())))
						{
							Tree.at(key) += values[i];
							remove.push_back(i);
						}
					}
					int adjustment = 0;
					for(int i = 0; i < remove.size(); i++)
					{
						values.erase(values.begin() + remove[i] + adjustment);
						adjustment--;
					}
					Tree.insert(std::pair<int, std::string> (2 * (nextKey - 1) + 1, Tree.at(holder)));
					Tree.erase(holder);
					holder = (holder - 1) / 2;
					Tree.erase(holder);
					holder = (2 * nextKey) + 1;
					for(int i = 0; i < values.size(); i++)
					{
						if(Tree.at(holder) == values[i].substr(0, values[i].find(".", 0)) ||
						   Tree.at(holder) == values[i].substr(values[i].find("=", 0) + 1,
							 values[i].rfind(".", values[i].size())))
						{
							Tree.at(key) += values[i];
							remove.push_back(i);
						}
					}
					Tree[nextKey] = "|X|";
					for(int i = 0; i < values.size(); i++)
					{
						Tree.at(nextKey) += values[i];
					}
					nextKey = (2 * nextKey) + 1;
					holder = 2 * nextKey;
					if(Tree.at(holder).find(sigma, 0) != std::string::npos)
					{
						Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
						holder = (2 * holder) + 1;
						Tree.insert(std::pair<int, std::string> (2 * (nextKey - 1) + 1, Tree.at(holder)));
						Tree.erase(holder);
						holder = (holder - 1) / 2;
						Tree.erase(holder);
						holder = 2 *nextKey + 1;
					}
					else
					{
						Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
						Tree.erase(holder);
					}
					holder = (2 * nextKey) + 1;
					if(Tree.at(holder).find(sigma, 0) != std::string::npos)
					{
						Tree[nextKey] = Tree.at(holder);
						holder = (2 * holder) + 1;
						Tree[2*(nextKey) + 1] = Tree.at(holder);
						Tree.erase(holder);
						holder = (holder - 1) / 2;
						Tree.erase(holder);
					}
					else
					{
						Tree[nextKey] = Tree.at(holder);
						Tree.erase(holder);
					}
					values.clear();
				}
				else
				{
					Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
					for(int i = 0; i < values.size(); i++)
					{
						if(Tree.at(holder) == values[i].substr(0, values[i].find(".", 0)) ||
						   Tree.at(holder) == values[i].substr(values[i].find("=", 0) + 1,
							 values[i].rfind(".", values[i].size())))
						{
							Tree.at(key) += values[i];
							remove.push_back(i);
						}
					}
					int adjustment = 0;
					for(int i = 0; i < remove.size(); i++)
					{
						values.erase(values.begin() + remove[i] + adjustment);
						adjustment--;
					}
					Tree.erase(holder);
					holder = (2 * nextKey) + 1;
					for(int i = 0; i < values.size(); i++)
					{
						if(Tree.at(holder) == values[i].substr(0, values[i].find(".", 0)) ||
						   Tree.at(holder) == values[i].substr(values[i].find("=", 0) + 1,
							 values[i].rfind(".", values[i].size())))
					  {
							Tree.at(key) += values[i];
							remove.push_back(i);
						}
					}
					Tree[nextKey] = "|X|";
					for(int i = 0; i < values.size(); i++)
					{
						Tree.at(nextKey) += values[i];
					}
					nextKey = (2 * nextKey) + 1;
					holder = 2 * nextKey;
					if(Tree.at(holder).find(sigma, 0) != std::string::npos)
					{
						Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
						holder = (2 * holder) + 1;
						Tree.insert(std::pair<int, std::string> (2 * (nextKey - 1) + 1, Tree.at(holder)));
						Tree.erase(holder);
						holder = (holder - 1) / 2;
						Tree.erase(holder);
						holder = (2 * nextKey) + 1;
					}
					else
					{
						Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
						Tree.erase(holder);
					}
					holder = (2 * nextKey) + 1;
					if(Tree.at(holder).find(sigma, 0) != std::string::npos)
				  {
						Tree[nextKey] = Tree.at(holder);
						holder = (2 * holder) + 1;
						Tree[(2 * nextKey) + 1] = Tree.at(holder);
						Tree.erase(holder);
						holder = (holder - 1) / 2;
						Tree.erase(holder);
					}
					else
					{
						Tree[nextKey] = Tree.at(holder);
						Tree.erase(holder);
					}
					values.clear();
				}
			}
			else
			{
				strHolder = Tree.at(key).substr(1, Tree.at(key).size());
				Tree[key] = "|X|";
				Tree.at(key) += strHolder;
				holder = 2 * nextKey;
				if(Tree.at(holder).find(sigma, 0) != std::string::npos)
				{
					Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
					holder = (2 * holder) + 1;
					Tree.insert(std::pair<int, std::string> (2 * (nextKey - 1) + 1, Tree.at(holder)));
					Tree.erase(holder);
					holder = (holder - 1) / 2;
					Tree.erase(holder);
					holder = (2 * nextKey) + 1;
				}
				else
				{
					Tree.insert(std::pair<int, std::string> (nextKey - 1, Tree.at(holder)));
					Tree.erase(holder);
				}
				holder = (2 * nextKey) + 1;
				if(Tree.at(holder).find(sigma, 0) != std::string::npos)
				{
					Tree[nextKey] = Tree.at(holder);
					holder = (2 * holder) + 1;
					Tree[(2 * nextKey) + 1] = Tree.at(holder);
					Tree.erase(holder);
					holder = (holder - 1) / 2;
					Tree.erase(holder);
				}
				else
				{
					Tree[nextKey] = Tree.at(holder);
					Tree.erase(holder);
				}
			}
		}
		else
		{
			opt2(((key * 2) + 1), values);
		}
	}
	return;
}

void QueryTree::opt3(int key, std::vector<std::string>& values)
{
	std::string holder;
	std::string strHolder2;
	int nextKey = key;
	int holder2;
	bool alreadyIn = false;
	holder = unionSymbol;
	strHolder2 = interSymbol;
  if(Tree.at(key) == holder || Tree.at(key) == strHolder2 ||
	   Tree.at(key) == "-")
	{
		opt3((key * 2), values);
		opt3(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find("Sort", 0) != std::string::npos)
	{
		opt3(((key * 2) + 1), values);
	}
	else if((Tree.at(key).find(sigma, 0) != std::string::npos))
	{
		holder = Tree.at(key).substr(1, Tree.at(key).size());
		for(int i = 0; i < values.size(); i++)
		{
			if(values[i] == holder.substr(0, holder.find("=", 0)))
			{
				alreadyIn = true;
			}
		}
		if(!alreadyIn && holder.find("Count", 0) == std::string::npos)
		{
			values.push_back(holder.substr(0, holder.find("=", 0)));
		}
		else
		{
			alreadyIn = false;
		}
		opt3(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find(pi, 0) != std::string::npos)
	{
		holder = Tree.at(key).substr(1, Tree.at(key).size());
		while(holder.find(',', 0) != std::string::npos)
		{
			values.push_back(holder.substr(0, holder.find(",", 0)));
			holder = holder.substr(holder.find(",", 0) + 1, holder.size());
		}
		if(holder != "reservationcount" && holder != "average")
		{
			values.push_back(holder);
		}
		opt3(((key * 2) + 1), values);
	}
	else if(Tree.at(key).find("|X|", 0) != std::string::npos)
	{
		holder = Tree.at(key).substr(3, Tree.at(key).size());
		for(int i = 0; i < values.size(); i++)
		{
			if(values[i] == holder.substr(0, holder.find("=", 0)))
			{
				alreadyIn = true;
			}
		}
		if(!alreadyIn)
		{
			values.push_back(holder.substr(0, holder.find("=", 0)));
		}
		else
		{
			alreadyIn = false;
		}
		holder = holder.substr(holder.find("=", 0) + 1,holder.size());
		for(int i = 0; i < values.size(); i++)
		{
			if(values[i] == holder)
			{
				alreadyIn = true;
			}
		}
		if(!alreadyIn)
		{
			values.push_back(holder);
		}
		else
	  {
			alreadyIn = false;
		}
		nextKey = 2 * nextKey;
		if(Tree.at(nextKey).find(sigma, 0) != std::string::npos)
		{
			holder2 = (nextKey * 2) + 1;
			Tree.insert(std::pair<int, std::string> ((2 * holder2) + 1, Tree.at(holder2)));
			Tree[holder2] = Tree.at(nextKey);
			Tree[nextKey] = pi;
			for(int i = 0; i < values.size(); i++)
			{
				if(Tree.at((2 * holder2) + 1) == values[i].substr(0, values[i].find(".", 0)))
				{
					if(Tree.at(nextKey).size() != 1)
					{
						Tree.at(nextKey) += ",";
					}
					Tree.at(nextKey) += values[i];
				}
			}
		}
		else
		{
			holder2 = (nextKey * 2) + 1;
			Tree.insert(std::pair<int, std::string> (holder2, Tree.at(nextKey)));
			Tree[nextKey] = pi;
			for(int i = 0; i < values.size(); i++)
			{
				if(Tree.at(holder2) == values[i].substr(0, values[i].find(".", 0)))
				{
					if(Tree.at(nextKey).size() != 1)
					{
						Tree.at(nextKey) += ",";
					}
					Tree.at(nextKey) += values[i];
				}
				if(values[i] == "sname" && Tree.at(holder2) == "Sailors")
				{
					Tree.at(nextKey) += values[i];
				}
			}
		}
		nextKey = nextKey + 1;
		if(Tree.at(nextKey).find("|X|", 0) != std::string::npos)
		{
			holder = Tree.at(nextKey).substr(3, Tree.at(nextKey).size());
			values.push_back(holder.substr(0, holder.find("=")));
			holder = holder.substr(holder.find("=", 0) + 1, holder.size());
			values.push_back(holder);
			nextKey = 2 * nextKey;
			if(Tree.at(nextKey).find(sigma, 0) != std::string::npos)
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> ((2 * holder2) + 1, Tree.at(holder2)));
				Tree[holder2] = Tree.at(nextKey);
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at((2 * holder2) + 1) == values[i].substr(0, values[i].find(".", 0)))
					{
						if(Tree.at(nextKey).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}
				}
			}
			else
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> (holder2, Tree.at(nextKey)));
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at(holder2) == values[i].substr(0, values[i].find(".", 0)))
					{
						if(Tree.at(nextKey).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}
				}
			}
			nextKey = nextKey + 1;
			if(Tree.at(nextKey).find(sigma, 0) != std::string::npos)
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> ((2 * holder2) + 1, Tree.at(holder2)));
				Tree[holder2] = Tree.at(nextKey);
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at((2 * holder2) + 1) == values[i].substr(0, values[i].find(".", 0)))
					{
						if(Tree.at(nextKey).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}
				}
			}
			else
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> (holder2, Tree.at(nextKey)));
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at(holder2) == values[i].substr(0, values[i].find(".", 0)))
          {
						if(Tree.at(holder2).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}						
				}
			}
		}
		else
		{
			if(Tree.at(nextKey).find(sigma, 0) != std::string::npos)
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> ((2 * holder2) + 1, Tree.at(holder2)));
				Tree[holder2] = Tree.at(nextKey);
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at((2 * holder2) + 1) == values[i].substr(0, values[i].find(".", 0)))
					{
						if(Tree.at(nextKey).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}
				}
			}
			else
			{
				holder2 = (nextKey * 2) + 1;
				Tree.insert(std::pair<int, std::string> (holder2, Tree.at(nextKey)));
				Tree[nextKey] = pi;
				for(int i = 0; i < values.size(); i++)
				{
					if(Tree.at(holder2) == values[i].substr(0, values[i].find(".", 0)))
					{
						if(Tree.at(nextKey).size() != 1)
						{
							Tree.at(nextKey) += ",";
						}
						Tree.at(nextKey) += values[i];
					}
				}
			}
		}
		values.clear();
	}
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
	space = 160 - (Tree.at(1).size() / 2);
	for (int i = 0; i < space; i++)
	{
		words[0] += " ";
	}
	words[0] += Tree.at(1);
	if (Tree.at(1).find(pi, 0) != std::string::npos)
	{
		for (int i = 0; i < 160; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "|";
		for (int i = 161; i < 320; i++)
		{
			connections[0] += " ";
		}
	}
	else
	{
		for (int i = 0; i < 80; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "/";
		for (int i = 81; i < 240; i++)
		{
			connections[0] += " ";
		}
		connections[0] += "|";
		for (int i = 241; i < 320; i++)
		{
			connections[0] += " ";
		}
	}
	std::cout << words[0] << std::endl;
	std::cout << connections[0] << std::endl;
	for (int i = 1; i < depth; i++)
	{
		if (i == 1)
		{
			space = 80;
		}
		if (i == 2)
		{
			space = 40;
		}
		if (i == 3)
		{
			space = 20;
		}
		if (i == 4)
		{
			space = 10;
		}
		if(i == 5 || i == 6)
		{
			space = 5;
		}
		pos = space;
		while (pos < 320 && pos < connections[i - 1].size())
		{
			if (connections[i - 1][pos] == '/' || connections[i - 1][pos] == '|')
			{
				if(key < maxKey)
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
			}
			pos = pos + space;
		}
		std::cout << words[i] << std::endl;
		if (i < depth - 1)
		{
			std::cout << connections[i] << std::endl;
		}
	}
	return;
}

void QueryTree::clearTree()
{
	Tree.clear();
	return;
}