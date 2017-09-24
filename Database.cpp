#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Database.hpp"

Database::Database()
{
	std::string line;
	std::ifstream myfile("Database.txt");
	Table temp;
	bool checkAttInMultTab = false;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			temp.tableName = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);
			while (line.find(" ") != std::string::npos)
			{
				temp.attributeNames.push_back(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);
				temp.attributeTypes.push_back(line.substr(0, line.find(" ")));
				line.erase(0, line.find(" ") + 1);
			}
			tables.push_back(temp);
			temp.tableName.clear();
			temp.attributeNames.clear();
			temp.attributeTypes.clear();
			line.clear();
		}
		myfile.close();
	}
	for (int i = 0; i < tables.size() - 1; i++)
	{
		for (int k = i + 1; k < tables.size(); k++)
		{
			for (int j = 0; j < tables[i].attributeNames.size(); j++)
			{
				for (int l = 0; l < tables[k].attributeNames.size(); l++)
				{
					if (tables[i].attributeNames[j] == tables[k].attributeNames[l])
					{
						attInMultTab.push_back(tables[i].attributeNames[j]);
					}
				}
			}
		}
	}
}

Database::~Database()
{
	tables.clear();
}

bool Database::isTable(std::string name)
{
	bool check = false;
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i].tableName == name)
		{
			check = true;
		}
		else if (tables[i].tableName == name.substr(0, name.size() - 1)
			     && name[name.size() - 1] == ',')
		{
			check = true;
		}
	}
	return check;
}

bool Database::isAttribute(std::string name)
{
	bool check = false;
	for (int i = 0; i < tables.size(); i++)
	{
		for (int k = 0; k < tables[i].attributeNames.size(); k++)
		{
			if (tables[i].attributeNames[k] == name)
			{
				check = true;
			}
		}
	}
	return check;
}

bool Database::isAttributeInTab(std::string tabName, std::string attrName)
{
	bool check = false;
	int i = 0;
	while (tables[i].tableName != tabName || i == tables.size())
	{
		i++;
	}
	for (int k = 0; k < tables[i].attributeNames.size(); k++)
	{
		if (attrName == tables[i].attributeNames[k])
		{
			check = true;
		}
	}
	return check;
}

bool Database::isAttInMultTab(std::string attrName)
{
	bool check = false;
	for (int i = 0; i < attInMultTab.size(); i++)
	{
		if (attrName == attInMultTab[i])
		{
			check = true;
		}
	}
	return check;
}

std::string Database::getAttributeType(std::string tabName, std::string attrName)
{
	int tableIt = 0;
	int attrIt = 0;
	bool foundTable = false;
	while (!foundTable && tableIt < tables.size())
	{
		if (tables[tableIt].tableName == tabName)
		{
			while (attrIt < tables[tableIt].attributeNames.size())
			{
				if (tables[tableIt].attributeNames[attrIt] == attrName)
				{
					return tables[tableIt].attributeTypes[attrIt];
				}
				attrIt++;
			}
			foundTable = true;
		}
		tableIt++;
	}
	if (foundTable == true)
	{
		std::cout << "The attribute was not in that table" << std::endl;
	}
	else
	{
		std::cout << "The table couldn't be found in the database" << std::endl;
	}
	return "No";
}

void Database::outputDatabase()
{
	for (int i = 0; i < tables.size(); i++)
	{
		std::cout << tables[i].tableName << " ";
		for (int k = 0; k < tables[i].attributeNames.size(); k++)
		{
			std::cout << tables[i].attributeNames[k] << " ";
			std::cout << tables[i].attributeTypes[k] << " ";
		}
		std::cout << std::endl;
	}
}