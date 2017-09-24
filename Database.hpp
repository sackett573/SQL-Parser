#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <string>
#include <vector>


struct Table
{
	std::string tableName;
	std::vector<std::string> attributeNames;
	std::vector<std::string> attributeTypes;
};

class Database
{
	private :
		std::vector<Table> tables;
		std::vector<std::string> attInMultTab;

	public :
		Database();
		~Database();
		bool isTable(std::string name);
		bool isAttribute(std::string name);
		bool isAttributeInTab(std::string tabName, std::string attrName);
		bool isAttInMultTab(std::string attrName);
		std::string getAttributeType(std::string tabName, std::string attrName);
		void outputDatabase();
};

#endif