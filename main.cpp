#include <bits/stdc++.h>
#include <fstream>
#include <json/json.h>
#include <algorithm>
std::string _rename(std::string name);//function that takes string and converts characters that are either letter or integer into a hexadecimal (definition after the main function)
const char *values = "0123456789abcdef";
void go_through(Json::Value obj, Json::Value &objNew); //function recursively going through object of its own.
void go_through_array(Json::Value obj, Json::Value &arrNew); //function recursively going through its own arrays.



Json::Value objNew; // json object in which we will save our converted everything.
int main()
{
    //opening files
    std::ifstream in("in.json");
    std::ofstream out("out.json");

    //parsing from file to object obj
    Json::Value obj;
    Json::Reader reader;
    reader.parse(in, obj);

    //starting recursion
    go_through(obj, objNew);

    //printing converted object to file
    out<<objNew;

    //closing files
    in.close();
    out.close();
}
std::string _rename(std::string name) //string to hex converter (a char at a time)
{
    std::string hex="";
    for(auto i = name.begin(); i != name.end(); i++)
    {
        hex.append("\\u00");
        int d = *i/16, r = *i%16; //d - divider, r - remainder
        hex.push_back(values[d]);
        hex.push_back(values[r]);

    }
    std::cout << name << " - " <<hex<< "\n";  //printing map of all converted values to terminal
    return hex;
}
void go_through(Json::Value obj, Json::Value &objNew)
{
    for(auto i = obj.begin(); i!=obj.end(); ++i)
    {

        std::string temp = _rename(i.key().asString());

        if ((*i).isString())
            objNew[temp] = _rename((*i).asString());

        else if((*i).isObject())
        {
            obj[temp] = {};
            go_through(*i, objNew[temp]);
        }
        else if((*i).isArray())
        {
            objNew[temp] = Json::arrayValue;
            go_through_array(*i, objNew[temp]);
        }
        else objNew[temp] = *i;


    }
}
void go_through_array(Json::Value obj, Json::Value &arrNew)
{
    for(auto i = 0; i<obj.size(); ++i)
        if (obj[i].isString())
            arrNew[i] = _rename(obj[i].asString());
        else if(obj[i].isObject())
        {
            arrNew[i] = {};
            go_through(obj[i], arrNew[i]);
        }
        else if(obj[i].isArray())
 {
            arrNew[i] = Json::arrayValue;
            go_through_array(obj[i], arrNew[i]);
}
        else arrNew[i] = obj[i];

}
