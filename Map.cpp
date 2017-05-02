#include "Map.h"
#include <iostream>

using namespace std;

Map::Map()
{
    //ctor
    Map(empt);
}

void Map::set_m(Object _m){
    m = _m;
}

Map::Map(Object _m){
    set_m(m);
}
Object Map::get_m(){
    return m;
}
void Map::print(){
    switch (m){
        case empt: break;
        case head: {
            cout << "#";
            break;
        }
        case body: {
            cout << "*";
            break;
        }
        case meal: {
            cout << "$";
            break;
        }
        case wall: {
            cout << "X";
            break;
        }
    }
}


Map::~Map()
{
    //dtor
}
