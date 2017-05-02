#include <iostream>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

class snake_body{
    private:
        int x;
        int y;
        snake_body* node;
        char shape = '#';
    public:
        snake_body() : snake_body(0, 0){}
        snake_body(int _x, int _y) : snake_body(_x, _y, NULL){}
        snake_body(int _x, int _y, snake_body* _node){
            x = _x;
            y = _y;
            node = _node;
        }
        void inp_node();
        void set_node(int _x, int _y, snake_body *_node = NULL);
        snake_body* get_node();
        void print();
        friend void inp_1(snake_body *(&last));
};
class snake_head : public
void inp_1(snake_body *(&last));
int main(){
    snake_body *head= new snake_body [1];
    snake_body *last= new snake_body [1];
    (*head) = snake_body(5, 5);
    last = head;
    cout << " 0 ";
    for (int i=1; i<=5 ; i++){
        cout << i << endl;
        inp_1(last);
        cout <<"   head: "<< head  << " last: " << last << " headnode: " << head->get_node() << endl;;
    }
    system("cls");
    while (head!= NULL){
        (*head).print();
        head = (head)->get_node();
    }
    return 0;
}

void snake_body::set_node(int _x, int _y, snake_body *_node){
    x=_x;
    y=_y;
    node=_node;
}
void snake_body::inp_node(){
    int x, y;
    cin >> x >> y;
    set_node(x, y);
}
snake_body* snake_body::get_node(){
    return node;
}
void snake_body::print(){
    gotoxy(x, y);
    cout << shape;
}

void inp_1(snake_body *(&last)){
    snake_body* t=new snake_body [1];
    t->inp_node();
    last->node = t;
    last = t;
}

