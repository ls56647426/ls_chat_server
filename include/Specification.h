#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <string>
#include <list>
using namespace std;

class Specification
{
public:
    Specification();

	static string isNull(string key);
	static string isNotNull(string key);

	static string equal(string key, string value);
	static string notEqual(string key, string value);
	static string like(string key, string value);

	static string Or(string a, string b);
	static string Or(list<string> list);

	static string And(string a, string b);
	static string And(list<string> list);

	static string tranString(const string &value);

    string getSqlWhere() const;
    void setSqlWhere(const string &value);

private:
    string sqlWhere;
};

#endif // SPECIFICATION_H
