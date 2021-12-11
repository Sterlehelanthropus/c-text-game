#include "GameObject.h"

GameObject::GameObject(const string* _s_name, const string* _desc, const string* _keyword) :
s_name(s_name), desc(desc), keyword(keyword) {};

string* GameObject::getName(){
    return this->s_name;
};

string* GameObject::getDesc() {
    return this->desc;
};

string* GameObject::getKeyword() {
    return this->keyword;
};
