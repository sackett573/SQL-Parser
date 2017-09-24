#include "stdafx.h"
#include <iostream>
#include "RelAlg.hpp"
#include "Database.hpp"
Database currentDatabase;

RelationalAlgebra::RelationalAlgebra()
{
	inSelectStatement = false;
	ifCombine = false;
	ifInStatement = false;
	ifGroupBy = false;
	ifHaving = false;
}

RelationalAlgebra::~RelationalAlgebra()
{
	usedAttributes.clear();
	usedTables.clear();
	usedNicknames.clear();
}

bool RelationalAlgebra::parseInput()
{
	if (isSelect())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isKeyword()
{
	if (currentWord == "SELECT" || currentWord == "FROM" || currentWord == "WHERE"
		|| currentWord == "HAVING" || currentWord == "AS" || currentWord == "AND"
		|| currentWord == "OR" || currentWord == "UNION" || currentWord == "SUM"
		|| currentWord == "INTERSECT" || currentWord == "Ave" || currentWord == "IN"
		|| currentWord == "GROUP" || currentWord == "Count" || currentWord == "MAX"
		|| currentWord == "MIN" || currentWord == "EXCEPT")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isSelect()
{
	if (std::cin >> currentWord)
	{
		if (currentWord == "SELECT")
		{
			equation += pi;
			inSelectStatement = true;
			if (isSelectStatement())
			{
				equation += ")";
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			std::cout << "Select keyword not used" << std::endl;
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isSelectStatement()
{
	if (std::cin >> currentWord)
	{
		if (isKeyword())
		{
			if (isAggregate())
			{
				return true;
			}
			else
			{
				std::cout << "Keywords cannot be attributes" << std::endl;
				return false;
			}
		}
		if (currentWord[currentWord.size() - 1] == ',')
		{
			usedAttributes.push_back(currentWord.substr(0, currentWord.size() - 1));
			equation += currentWord;
			if (currentWord.size() > 1 && isSelectStatement())
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			usedAttributes.push_back(currentWord);
			equation += currentWord;
			if (std::cin >> currentWord)
			{
				if (isFrom())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				std::cout << "Need From Statement" << std::endl;
				return false;
			}
		}
	}
	else
	{
		std::cout << "Need attributes for Select statement" << std::endl;
		return false;
	}
}

bool RelationalAlgebra::isFrom()
{
	equation += "(";
	inSelectStatement = false;
	if (currentWord == "FROM")
	{
		if (isValidFromStatement())
		{
			if (areValidAttributes())
			{
				if (currentWord == "WHERE")
				{
					if (isWhere())
					{
						equation += "(";
						equation += usedNicknames[0];
						if (usedNicknames.size() > 1)
						{
							usedNicknames.erase(usedNicknames.begin());
							while (usedNicknames.size() > 1)
							{
								equation += "X(";
								equation += usedNicknames[0];
								usedNicknames.erase(usedNicknames.begin());
							}
							equation += "X";
							equation += usedNicknames[0];
							equation += ")";
						}
						if (!ifCombine)
						{
							equation += ")";
						}
						else if (ifGroupBy)
						{
							equation += ")";
							ifGroupBy = false;
						}
						if (ifHaving)
						{
							equation += ")";
							ifHaving = false;
						}
						if (currentWord == "UNION")
						{
							equation += ")";
							equation += unionSymbol;
							ifCombine = true;
							usedAttributes.clear();
							usedTables.clear();
							usedNicknames.clear();
							if (isSelect())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (currentWord == "INTERSECT")
						{
							equation += ")";
							equation += interSymbol;
							ifCombine = true;
							usedAttributes.clear();
							usedTables.clear();
							usedNicknames.clear();
							if (isSelect())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (currentWord == "EXCEPT")
						{
							equation += ")";
							equation += "-";
							ifCombine = true;
							usedAttributes.clear();
							usedTables.clear();
							usedNicknames.clear();
							if (isSelect())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						ifCombine = false;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (currentWord == "Done")
				{
					equation += usedNicknames[0];
					if (usedNicknames.size() > 1)
					{
						usedNicknames.erase(usedNicknames.begin());
						while (usedNicknames.size() > 1)
						{
							equation += "X(";
							equation += usedNicknames[0];
							usedNicknames.erase(usedNicknames.begin());
						}
						equation += "X";
						equation += usedNicknames[0];
						//equation += ")";
					}
					if (!ifCombine)
					{
						/*equation += ")";*/
					}
					ifCombine = false;
					return true;
				}
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		std::cout << "Need From Statement" << std::endl;
		return false;
	}
}

bool RelationalAlgebra::isValidFromStatement()
{
	std::string tabName;
	if (std::cin >> currentWord)
	{
		if (isKeyword())
		{
			return false;
		}
		if (!currentDatabase.isTable(currentWord))
		{
			if (currentWord[currentWord.size() - 1] == ',')
			{
				currentWord = currentWord.substr(0, currentWord.size() - 1);
			}
			std::cout << currentWord << " is not a table in the database." << std::endl;
			return false;
		}
		if (currentWord[currentWord.size() - 1] == ',')
		{
			usedTables.push_back(currentWord.substr(0, currentWord.size() - 1));
			usedNicknames.push_back(currentWord.substr(0, currentWord.size() - 1));
			if (currentWord.size() > 1 && isValidFromStatement())
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			tabName = currentWord;
			if (std::cin >> currentWord)
			{
				if (currentWord == "AS")
				{
					if (std::cin >> currentWord)
					{
						if (currentWord[currentWord.size() - 1] == ',')
						{
							usedTables.push_back(tabName);
							usedNicknames.push_back(currentWord.substr(0, currentWord.size() - 1));
							if (currentWord.size() > 1 && isValidFromStatement())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							usedTables.push_back(tabName);
							usedNicknames.push_back(currentWord);
							if (std::cin >> currentWord)
							{
								if (currentWord == "WHERE")
								{
									return true;
								}
								else
									return false;
							}
							currentWord = "Done";
							return true;
						}
					}
					else
					    return false;
				}
				else if (currentWord == "WHERE")
				{
					usedTables.push_back(tabName);
					usedNicknames.push_back(tabName);
					return true;
				}
				else
				{
					if (currentWord[currentWord.size() - 1] == ',')
					{
						usedTables.push_back(tabName);
						usedNicknames.push_back(currentWord.substr(0, currentWord.size() - 1));
						if (currentWord.size() > 1 && isValidFromStatement())
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						usedTables.push_back(tabName);
						usedNicknames.push_back(currentWord);
						if (std::cin >> currentWord)
						{
							if (currentWord == "WHERE")
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						currentWord = "Done";
						return true;
					}
				}
			}
			else
			{
				usedTables.push_back(tabName);
				usedNicknames.push_back(tabName);
				currentWord = "Done";
				return true;
			}
		}
	}
	else
		return false;
}

bool RelationalAlgebra::isWhere()
{
	if (currentWord == "WHERE")
	{
		equation += sigma;
		if (isWhereClause())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

bool RelationalAlgebra::isWhereClause()
{
	std::string whereEquation;
	std::string inCheckHolder;
	bool haveCheckEq = false;

	if (std::cin >> currentWord)
	{
		if (isKeyword())
		{
			std::cout << currentWord << std::endl;
			if (!isAggregate())
			{
				return false;
			}
		}
		whereEquation = currentWord;
		if (std::cin >> currentWord)
		{
			if (currentWord == "=" || currentWord == "<" || currentWord == ">")
			{
				whereEquation += currentWord;
				if (std::cin >> currentWord)
				{
					if (currentWord == "(SELECT")
					{
						equation += whereEquation;
						equation += inSymbol;
						nestedStatement = equation;
						equation.clear();
						ifInStatement = true;
						equation += pi;
						usedTables.clear();
						usedNicknames.clear();
						usedAttributes.clear();
						if (isSelectStatement())
						{
							equation += ")";
							whereEquation = nestedStatement;
							nestedStatement = equation;
							equation = whereEquation;
							return true;
						}
					}
					whereEquation += currentWord;
					if (!ifInStatement)
					{
						if (!isExpression(whereEquation))
						{
							return false;
						}
						else
						{
							haveCheckEq = true;
							if (std::cin >> currentWord)
							{
							}
							else
							{
								return true;
							}
						}
					}
					else
					{
						if (whereEquation[whereEquation.size() - 1] == ')')
						{
							if (!isExpression(whereEquation.substr(0, whereEquation.size() - 1)))
							{
								return false;
							}
							else
							{
								if (std::cin >> currentWord)
								{

								}
								else
								{
									return true;
								}
							}
						}
						else
						{
							if (!isExpression(whereEquation))
							{
								return false;
							}
							else
							{
								if (std::cin >> currentWord)
								{

								}
								else
								{
									return true;
								}
							}
						}
					}
				}
				else
				{
					return false;
				}
			}
			if (currentWord == "AND")
			{
				if (!haveCheckEq)
				{
					if (!isExpression(whereEquation))
					{
						return false;
					}
				}
				equation += andSymbol;
				if (isWhereClause())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (whereEquation == "NOT")
			{
				std::cout << "This is not a valid expression NOT" << std::endl;
				return false;
			}
			else if (currentWord == "IN")
			{
				ifInStatement = true;
				equation += pi;
				equation += whereEquation;
				equation += "(";
				equation += whereEquation.substr(0, whereEquation.find('.', 0));
				std::cout << "Not done" << std::endl;
				return false;
			}
			else if (currentWord == "UNION" || currentWord == "INTERSECT" ||
				currentWord == "EXCEPT")
			{
				if (!haveCheckEq)
				{
					if (!isExpression(whereEquation))
					{
						return false;
					}
				}
				return true;
			}
			else if (currentWord == "GROUP")
			{
				if (!haveCheckEq)
				{
					if (!isExpression(whereEquation))
					{
						return false;
					}
				}
				if (isGroupby())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (currentWord == ")" && ifInStatement)
		{
			return true;
		}
		else if (currentWord[currentWord.size() - 1] == ')' && ifInStatement)
		{
			if (isExpression(currentWord.substr(0, currentWord.size() - 1)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (isExpression(currentWord))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isGroupby()
{
	int sortPos;
	std::string tempEquation;
	if (std::cin >> currentWord)
	{
		if (currentWord == "BY")
		{
			ifGroupBy = true;
			sortPos = equation.find(sigma, 0);
			tempEquation = equation.substr(sortPos, equation.size());
			equation.erase(sortPos, std::string::npos);
			equation += "Sort";
			if (isGBClause())
			{
				equation += "(";
				equation += tempEquation;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isGBClause()
{
	if (std::cin >> currentWord)
	{
		if (isKeyword())
		{
			return false;
		}
		else if (!isValidAttribute(currentWord.substr(0, currentWord.size()))
			&& !isValidAttribute(currentWord.substr(0, currentWord.size() - 1)))
		{
			return false;
		}
		else if (currentWord[currentWord.size() - 1] == ',')
		{
			equation += currentWord.substr(0, currentWord.size() - 1);
			if (currentWord.size() > 1 && isGBClause())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			equation += currentWord;
			if (!isHaving())
			{
				return false;
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isHaving()
{
	std::string tempEquation;
	int havingPos;
	if (std::cin >> currentWord)
	{
		if (currentWord == "HAVING")
		{
			ifHaving = true;
			havingPos = equation.find("(", 0) + 1;
			tempEquation = equation.substr(havingPos, equation.size());
			equation.erase(havingPos, std::string::npos);
			equation += sigma;
			if (isHavingClause())
			{
				equation += "(";
				equation += tempEquation;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool RelationalAlgebra::isHavingClause()
{
	std::string havingEquation;
	if (std::cin >> currentWord)
	{
		if (isKeyword())
		{
			if (isAggregate())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		havingEquation = currentWord;
		if (std::cin >> currentWord)
		{
			if (currentWord == "=" || currentWord == "<" || currentWord == ">")
			{
				havingEquation += currentWord;
				if (std::cin >> currentWord)
				{
					havingEquation += currentWord;
					currentWord = havingEquation;
				}
				else
				{
					return false;
				}
			}
		}
		if (currentWord[currentWord.size() - 1] == ',')
		{
			if (isExpression(currentWord.substr(0, currentWord.size() - 1)))
			{
				equation += currentWord.substr(0, currentWord.size() - 1);
				if (currentWord.size() > 1 && isHavingClause())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			if (isExpression(currentWord))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

bool RelationalAlgebra::isAggregate()
{
	std::string attributeName;
	std::string aggregateName;

	if (currentWord == "SUM" || currentWord == "MAX"
		|| currentWord == "MIN" || currentWord == "Ave")
	{
		aggregateName += currentWord;
		if (std::cin >> currentWord)
		{
			aggregateName += currentWord;
			if (currentWord[0] == '(' && currentWord[currentWord.size() - 1] == ')')
			{
				attributeName = currentWord.substr(1, currentWord.size() - 2);
				if (std::cin >> currentWord)
				{
					if (currentWord == "AS")
					{
						if (std::cin >> currentWord)
						{
							equation += currentWord;
						}
						if (isKeyword())
						{
							return false;
						}
						if (std::cin >> currentWord)
						{
							if (isFrom())
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
							return false;
					}
					else if (currentWord == "FROM")
					{
						equation += aggregateName;
						usedAttributes.push_back(attributeName);
						if (isFrom())
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				return true;
			}
			else
				return false;
		}
		else
		{
			std::cout << "Aggregate functions need parameters" << std::endl;
			return false;
		}
	}
	else if (currentWord == "Count")
	{
		if (std::cin >> currentWord)
		{
			if (currentWord[0] == '(' && currentWord[currentWord.size() - 1] == ')')
			{
				attributeName = currentWord.substr(1, currentWord.size() - 2);
				if (attributeName == "*")
				{
					if (std::cin >> currentWord)
					{
						if (currentWord == "AS")
						{
							if (std::cin >> currentWord)
							{
								if (isKeyword())
								{
									return false;
								}
								equation += currentWord;
								if (std::cin >> currentWord)
								{
									if (isFrom())
									{
										return true;
									}
									else
										return false;
								}
								else
									return false;
							}
							else
								return false;
						}
						else if (currentWord == "<" || currentWord == ">")
						{
							equation += "Count(*)";
							equation += currentWord;
							if (std::cin >> currentWord)
							{
								if (isInteger(currentWord) == "integer" || 
									isReal(currentWord) == "real" || isReal(currentWord) == "realInt")
								{
									equation += currentWord;
									return true;
								}
								else
									return false;
							}
							else
								return false;
						}
						else if (currentWord == "=")
						{
							if (std::cin >> currentWord)
							{
								if (isAttributeType(currentWord) == "integer" &&
									isInteger(currentWord) == "integer")
								{
									return true;
								}
								else
									return false;
							}
							else
								return false;
						}
						else
						{
							if (isFrom())
							{
								return true;
							}
							else
								return false;
						}
					}
					else if (inSelectStatement)
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool RelationalAlgebra::areValidAttributes()
{
	bool allAtt = true;
	if (usedTables.size() == 1)
	{
		for (int i = 0; i < usedAttributes.size(); i++)
		{
			if (!currentDatabase.isAttributeInTab(usedTables[0], usedAttributes[i])
				&& !currentDatabase.isAttributeInTab(usedTables[0], 
				usedAttributes[i].substr(usedAttributes[i].find('.') + 1, usedAttributes[i].size())))
			{
				std::cout << usedAttributes[i] << " is not in table " << usedTables[0] << "." << std::endl;
				allAtt = false;
			}
		}
		if (allAtt == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	allAtt = true;
	for (int i = 0; i < usedAttributes.size(); i++)
	{
		if (currentDatabase.isAttInMultTab(usedAttributes[i]))
		{
			allAtt = false;
		}
	}
	if (allAtt == true)
	{
		return true;
	}
	for (int i = 0; i < usedAttributes.size(); i++)
	{
		if (!isValidAttribute(usedAttributes[i]))
		{
			std::cout << "This is not a valid attribute " << usedAttributes[i] << std::endl;
			return false;
		}
	}
	return true;
}

bool RelationalAlgebra::isValidAttribute(const std::string& attrName)
{
	int pos = attrName.find('.', 0);
	std::string temp;
	bool validAtt = false;
	if (pos != std::string::npos)
	{
		temp = attrName.substr(0, pos);
		for (int i = 0; i < usedNicknames.size(); i++)
		{
			if (temp == usedNicknames[i])
			{
				temp = attrName.substr(pos + 1, attrName.size());
				if (currentDatabase.isAttributeInTab(usedTables[i], temp))
				{
					validAtt = true;
				}
			}
		}
	}
	return validAtt;
}

bool RelationalAlgebra::isExpression(const std::string& whereEquation)
{
	int pos = -1;
	int posEq = whereEquation.find('=', 0);
	int posGT = whereEquation.find('>', 0);
	int posLT = whereEquation.find('<', 0);
	std::string firstHalf;
	std::string secondHalf;
	std::string holder;

	if (posEq != std::string::npos)
	{
		firstHalf = whereEquation.substr(0, posEq);
		if (isValidAttribute(firstHalf))
		{
			secondHalf = whereEquation.substr(posEq + 1, whereEquation.size());
			if (isValidAttribute(secondHalf))
			{
				if (isAttributeType(firstHalf) == isAttributeType(secondHalf))
				{
					equation += whereEquation;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (isAttributeType(firstHalf) == isDate(secondHalf))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isString(secondHalf))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isReal(secondHalf) ||
				(isAttributeType(firstHalf) == "real" &&
				isReal(secondHalf) == "realInt"))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isReal(secondHalf) ||
				(isAttributeType(firstHalf) == "integer" &&
					isReal(secondHalf) == "realInt"))
			{
				equation += whereEquation;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			std::cout << "Error: This is not a valid attribute " << firstHalf << std::endl;
			return false;
		}
	}
	else if (posLT != std::string::npos)
	{
		pos = posLT;
	}
	else if (posGT != std::string::npos)
	{
		pos = posGT;
	}
	if (pos != -1)
	{
		firstHalf = whereEquation.substr(0, pos);
		if (isValidAttribute(firstHalf))
		{
			secondHalf = whereEquation.substr(pos + 1, whereEquation.size());
			if (isValidAttribute(secondHalf))
			{
				if (isAttributeType(firstHalf) == isAttributeType(secondHalf))
				{
					equation += whereEquation;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (isAttributeType(firstHalf) == isDate(secondHalf))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isString(secondHalf))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isReal(secondHalf) || 
				    (isAttributeType(firstHalf) == "real" || isReal(secondHalf) == "realInt"))
			{
				equation += whereEquation;
				return true;
			}
			else if (isAttributeType(firstHalf) == isInteger(secondHalf) ||
				     (isAttributeType(firstHalf) == "integer" && isReal(secondHalf) == "realInt"))
			{
				equation += whereEquation;
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			std::cout << "Error: This is not a valid attribute " << firstHalf << std::endl;
			return false;
		}
	}
	return false;
}

const std::string RelationalAlgebra::isInteger(const std::string& variable)
{
	for (int i = 0; i < variable.size(); i++)
	{
		if (!isdigit(variable[i]))
		{
			return "no";
		}
	}
	return "integer";
}

const std::string RelationalAlgebra::isReal(const std::string& variable)
{
	int pos = variable.find('.', 0);
	if (pos == std::string::npos)
	{
		for (int i = 0; i < variable.size(); i++)
		{
			if (!isdigit(variable[i]))
			{
				return "no";
			}
		}
		return "realInt";
	}
	if (isdigit(variable[0]))
	{
		for (int i = 1; i < pos; i++)
		{
			if (!isdigit(variable[i]))
			{
				return "no";
			}
		}
		for (int i = pos + 1; i < variable.size(); i++)
		{
			if (!isdigit(variable[0]))
			{
				return "no";
			}
		}
		return "real";
	}
	else
		return "no";
}

const std::string RelationalAlgebra::isDate(const std::string& variable)
{
	int pos = variable.find("'", 0);
	int pos2 = variable.find("'", 11);
	if (variable.size() == 12)
	{
		if (pos == 0 && pos2 == 11)
		{
			if (isdigit(variable[1]) && isdigit(variable[2]) && isdigit(variable[3])
				&& isdigit(variable[5]) == '-' && isdigit(variable[8]) == '-')
			{
				if ((variable[6] == '0' && (variable[7] == '1' || variable[7] == '3'
					|| variable[7] == '5' || variable[7] == '7' || variable[7] == '8'))
					|| (variable[6] == '1' && (variable[7] == '0' || variable[7] == '2')))
				{
					if (variable[9] == '0' || variable[9] == '1' || variable[9] == '2')
					{
						if (isdigit(variable[10]))
						{
							return "date";
						}
					}
					else if (variable[9] == '3')
					{
						if (variable[10] == '0' || variable[10] == '1')
						{
							return "date";
						}
					}
				}
				else if ((variable[6] == '0' && (variable[7] == '4' || variable[7] == '6'
					|| variable[7] == '9')) || (variable[6] == '1' && variable[7] == '1'))
				{
					if (variable[9] == '0' || variable[9] == '1' || variable[9] == '2')
					{
						if (isdigit(variable[10]))
						{
							return "date";
						}
					}
					else if (variable[9] == '3')
					{
						if (variable[10] == '0')
						{
							return "date";
						}
					}
				}
				else if (variable[6] == '0' && variable[7] == '2')
				{
					if (variable[9] == '0' && variable[9] == '1')
					{
						if (isdigit(variable[10]))
						{
							return "date";
						}
					}
					else if (variable[9] == '2')
					{
						if (isdigit(variable[10]) && variable[10] != '9')
						{
							return "date";
						}
					}
				}
			}
		}
	}
	return "no";
}

const std::string RelationalAlgebra::isString(const std::string& variable)
{
	int pos = variable.find('"', 0);
	int pos2 = variable.find('"', variable.size() - 3);

	if (pos == std::string::npos)
	{
		pos = variable.find('"', 0);
	}
	if (pos == 0 && pos2 == variable.size() - 1)
	{
		return "string";
	}
	return "no";
}

const std::string RelationalAlgebra::isAttributeType(const std::string& attr)
{
	std::string attrName, tabName, temp;
	int pos = attr.find('.', 0);
	tabName = attr.substr(0, pos);
	attrName = attr.substr(pos + 1, attr.size());
	for (int i = 0; i < usedNicknames.size(); i++)
	{
		if (tabName == usedNicknames[i])
		{
			tabName = usedTables[i];
		}
	}
	temp = currentDatabase.getAttributeType(tabName, attrName);
	if (temp == "No")
	{
		return "No";
	}
	else
		return temp;
}

const std::string RelationalAlgebra::getCurrentWord()
{
	return currentWord;
}

const std::string RelationalAlgebra::getEquation()
{
	return equation;
}

const std::string RelationalAlgebra::getNestedStatement()
{
	return nestedStatement;
}