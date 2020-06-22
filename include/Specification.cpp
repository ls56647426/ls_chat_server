#include "Specification.h"

Specification::Specification()
{

}

string Specification::isNull(string key)
{
    return key + " is null";
}

string Specification::isNotNull(string key)
{
    return key + " is not null";
}

string Specification::equal(string key, string value)
{
    return key + " = " + value;
}

string Specification::notEqual(string key, string value)
{
    return key + " <> " + value;
}

string Specification::like(string key, string value)
{
    return key + " like " + value;
}

string Specification::Or(string a, string b)
{
    return "(" + a + ") or (" + b + ")";
}

string Specification::Or(list<string> list)
{
    string res;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        if(it != list.begin())
            res += " or ";
        res += "(" + *it + ")";
    }

    return res;
}

string Specification::And(string a, string b)
{
    return "(" + a + ") and (" + b + ")";
}

string Specification::And(list<string> list)
{
    string res;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        if(it != list.begin())
            res += " and ";
        res += "(" + *it + ")";
    }

	return res;
}

string Specification::tranString(const string &value)
{
	return "'" + value + "'";
}

string Specification::getSqlWhere() const
{
    return sqlWhere;
}

void Specification::setSqlWhere(const string &value)
{
    sqlWhere = value;
}
