//Database.hpp
//Ojective: header file for the database class which stores information on the
//          theoretical database
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
		//Purpose: checks if a name is a table in the database
		//Precondition: none
		//Postcondiont: returns true if name is the name of a table in the database
		bool isTable(std::string name);
		//Purpose: checks if a name is an attribute in the datatbase
		//Precondition: none
		//Postcondition: returns true if name is the name of an attribute in the database
		bool isAttribute(std::string name);
		//Purpose: checks if an attribute attrName is an attribute in the table tabName
		//Precondition: none
		//Postcondition: returns true if attrName is an attribute in the table tabName
		bool isAttributeInTab(std::string tabName, std::string attrName);
		//Purpose: checks if an attribute attrName is an attribute in multiple tables
		//Precondition: none
		//Postcondition: returns true if attrName if it is an attribute in multiple tables
		bool isAttInMultTab(std::string attrName);
		//Purpose: gets the type of an attribute in a table
		//Precondition: none
		//Postcondition: returns the type of attrName in tabName
		std::string getAttributeType(std::string tabName, std::string attrName);
		//Purpose: outputs the database
		//Precondition: none
		//Postcondition: uses cout to output the database to the screen
		void outputDatabase();
};

#endif