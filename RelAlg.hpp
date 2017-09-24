#ifndef  RELALG_HPP
#define  RELALG_HPP
#include <string>
#include <vector>

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
		bool parseInput();
		bool isKeyword();
		bool isSelect();
		bool isSelectStatement();
		bool isFrom();
		bool isValidFromStatement();
		bool isWhere();
		bool isWhereClause();
		bool isGroupby();
		bool isGBClause();
		bool isHaving();
		bool isHavingClause();
		bool isAggregate();
		bool areValidAttributes();
		bool isValidAttribute(const std::string& attrName);
		bool isExpression(const std::string& whereEquation);

		const std::string isInteger(const std::string& variable);
		const std::string isReal(const std::string & variable);
		const std::string isDate(const std::string& variable);
		const std::string isString(const std::string& variable);
		const std::string isAttributeType(const std::string& attr);
		const std::string getCurrentWord();
		const std::string getEquation();
		const std::string getNestedStatement();
};



#endif