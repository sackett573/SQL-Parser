//RelAlg.hpp
//Objective: header file for the relationalAlgebra class which takes input
//           and turns it into relational algebra

#ifndef  RELALG_HPP
#define  RELALG_HPP
#include <string>
#include <vector>

//Global variables for symbols used in relational algebra
const char pi = 227;
const char sigma = 229;
const char inSymbol = 155;
const char andSymbol = 94;
const char unionSymbol = 154;
const char interSymbol = 239;

class RelationalAlgebra
{
	private :
		std::string equation;
		std::string currentWord;
		std::vector<std::string> usedAttributes;
		std::vector<std::string> usedTables;
		std::vector<std::string> usedNicknames;
		std::string nestedStatement;
		bool inSelectStatement;
		bool ifInStatement;
		bool ifCombine;
		bool ifGroupBy;
		bool ifHaving;

	public :
		RelationalAlgebra();
		~RelationalAlgebra();
		//Purpose: initial function to parse input
		//Precondition: none
		//Postcondition: returns true if the input was parsed successfully
		bool parseInput();
		//Purpose: checks if currentWord is a keyword
		//Precondition: currentWord must have input
		//Postcondition: returns true if currentWord is a keyword
		bool isKeyword();
		//Purpose: checks if the query has the SELECT keyword
		//Precondition: currentWord == "SELECT"
		//Postcondition: returns true if currenntWord == SELECT and there
		//               isSelectStatment() returns true
		bool isSelect();
		//Purpose: checks if the query has valid attributes following select
		//Precondition: currentWord has input
		//Postcondition: returns true if the attributes in the select statement are grammitcally
		//               correct and if isFrom() returns true
		bool isSelectStatement();
		//Purpose: checks that the FROM keyword is used
		//Precondition: currentWord = FROM
		//Postcondition: returns ture if currentWord = FROM and isValidFromStatement is true
		bool isFrom();
		//Purpose: checks that there are valid tables following FROM
		//Precondtion: currentWord has input
		//Postcondition: returns true if currentWord are valid tables in the database
		bool isValidFromStatement();
		//Purpose: checks for the WHERE keyword
		//Precondition: currentWord = WHERE
		//Postcondition: returns true if currentWord is WHERE and isWhereClause is true
		bool isWhere();
		//Purpose: checks for valid comparisons after WHERE
		//Precondtion: currentWord has input
		//Postcondtion: returns true if the expressions after where are valid expressions
		bool isWhereClause();
		//Purpose: checks for the GROUP BY keyword
		//Precondition: currentWord = GROUP BY
		//Postcondition: returns true if currentWord is GROUP BY and isGBClause is true
		bool isGroupby();
		//Purpose: checks that there are valid attributes after GROUP BY
		//Precondition: currentWord has input
		//Postconditin: returns true if there are valid attribute after GROUP BY
		bool isGBClause();
		//Purpose: checks for the HAVING keyword
		//Precondition: currentWord = HAVING
		//Postcondition: returns true if currentWord = HAVING and isHavingClause is true
		bool isHaving();
		//Purpose: checks for valid expressions after HAVING
		//Precondition: currentWord has input
		//Postcondition: returns true if there are valid attributes after HAVING
		bool isHavingClause();
		//Purpose: checks if currentWord is an aggregate function
		//Precondition: currentWord is an aggregate keyword
		//Postcondition: returns true if currentWord is an aggregate function
		bool isAggregate();
		//Purpose: checks if the attributes in SELECT are in the tables in FROM
		//Precondtion: isSelectStatment is true and isValidFromStatement is true
		//Postcondition: returns true if the attributes in SELECT are in the tables in FROM
		bool areValidAttributes();
		//Purpose: checks if an attribute is a valid attribute in the database
		//Precondition: must have had attributes in SELECT
		//Postcondition: returns true if an attribute is a valid attribute in the database
		bool isValidAttribute(const std::string& attrName);
		//Purpose: checks if an expression is a valid expression
		//Precondition: must have an expression
		//Postcondition: returns true if whereEquation is a valid expression
		bool isExpression(const std::string& whereEquation);

		//Purpose: checks if variable is type integer
		//Precondition: must have a input for variable
		//Postcondition: returns integer if variable is an integer and no otherwise
		const std::string isInteger(const std::string& variable);
		//Purpose: checks if variable is type real
		//Precondition: must have a input for variable
		//Postcondition: returns real if variable is real, realInt if variable is a real integer
		//                and no otherwise
		const std::string isReal(const std::string & variable);
		//Purpose: checks if variable is type date
		//Precondition: must have a input for variable
		//Postcondition: returns date if variable is a date and no otherwise
		const std::string isDate(const std::string& variable);
		//Purpose: checks if variable is type string
		//Precondition: must have a input for variable
		//Postcondition: returns string if variable is a string and no otherwise
		const std::string isString(const std::string& variable);
		//Purpose: checks an attributes type
		//Precondition: must have a input for variable
		//Postcondition: returns integer, realInt, real, string, or date depending on attr type
		const std::string isAttributeType(const std::string& attr);
		//returns the member variable currentWord
		const std::string getCurrentWord();
		//returns the member variable equation
		const std::string getEquation();
		//returns the member variable nestedStatement
		const std::string getNestedStatement();
};



#endif