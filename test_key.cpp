#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}
int main(){
    char c;
    for (int i=1 ; i<=10 ; i++){
        cout << "    " << i << " ";
        if (checkKey(VK_LEFT))
            cout << "dm";
        else if (checkKey(VK_RIGHT))
            cout << "right";
        else if (checkKey(VK_DOWN))
            cout << "down";
        else if (checkKey(VK_UP))
            cout << "up";
        Sleep(2000);
        if (checkKey(VK_LEFT))
            cout << "dm";
        else if (checkKey(VK_RIGHT))
            cout << "right";
        else if (checkKey(VK_DOWN))
            cout << "down";
        else if (checkKey(VK_UP))
            cout << "up";

    }
    return 0;
}
