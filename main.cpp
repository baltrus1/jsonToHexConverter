#include <bits/stdc++.h>
#include <fstream>
#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include <algorithm>
std::string _rename(std::string name);//function that takes string and converts characters that are either letter or integer into a hexadecimal (definition after the main function)
const char *values = "0123456789abcdef";
void go_through(Json::Value obj, Json::Value &objNew);
void go_through_array(Json::Value obj, Json::Value &arrNew);



Json::Value objNew;
int main()
{
    std::string a;
    std::ifstream in("in.json");
    std::ofstream out("out.json");
    Json::Value obj;

    Json::Reader reader;
    reader.parse(in, obj);
    go_through(obj, objNew);
    out<<objNew;
    //std::cout<<'\\';
    //std::cout << string_to_hex("a");
    in.close();
    out.close();
}
std::string _rename(std::string name)
{
    std::string hex="";
    for(auto i = name.begin(); i != name.end(); i++)
    {
        hex.append("\\u00");
        int d = *i/16, r = *i%16; //d - divider, r - remainder
        hex.push_back(values[d]);
        hex.push_back(values[r]);

    }
    std::cout << name << " - " <<hex<< "\n";
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
