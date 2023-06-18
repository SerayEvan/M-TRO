#include "split.hpp"

#include <vector>
#include <string>

using namespace std;

vector<string> split(const string phrase){
    vector<string> list;
    string s = string(phrase);
    size_t pos = 0;
    string token;
    while ((pos = s.find(" ")) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + 1);
    }
    list.push_back(s);
    return list;
}