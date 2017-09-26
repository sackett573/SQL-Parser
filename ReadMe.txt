This program is an parser for a basic SQL language. The purpose of the parser is too scan through SQL code presented by
the user, check it against a database submitted by the user, and have the program convert the SQL code into valid
relational algebra. Afterwards the relational algebra is the converted into a query tree. The query tree then has
optimizations performed on it that would help an actual SQL compiler be able to run the code faster. A sample database
with some sample test cases is also included with these files.