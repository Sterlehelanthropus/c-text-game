#include <iostream>
#include "State.h"

using std::string;

class GameObject{
    string* s_name;
    string* desc;
    string* keyword;
public:
    /** constructor */
    GameObject(const string *_s_name, const string *_desc, const string *_keyword);

    string* getName();
    string* getDesc();
    string* getKeyword();
};
