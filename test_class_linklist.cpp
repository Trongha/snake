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
enum parts{
    HEAD,
    BODY,
    LAST
};
enum directions{
    LEFT,
    UP,
    RIGHT,
    DOWN
};
class snake_body{
    private:
        int x;
        int y;
        parts part;
        snake_body* node;
        char shape = '#';
        directions direction;
    public:
        snake_body() : snake_body(0, 0){}
        snake_body(int _x, int _y) : snake_body(_x, _y, NULL, BODY){}
        snake_body(int _x, int _y, parts _part) : snake_body(_x, _y, NULL, _part){}
        snake_body(int _x, int _y, snake_body* _node, parts _part){
            x = _x;
            y = _y;
            node = _node;
            part = _part;
            direction = RIGHT;
        }
        void set_direction (directions _direction){
                direction = _direction;
        }
        void change_direction();
        void move_snake();
        void inp_node();
        void set_node(snake_body* _node){
            node = _node;
        }
        void set_node(int _x, int _y, snake_body *_node = NULL);
        snake_body* get_node();
        directions get_direction();
        int get_x();
        int get_y();
        void print();
        friend void inp_1(snake_body *(&last));
        friend void print_all(snake_body *head);
};
void inp_1(snake_body *(&last));
void print_all(snake_body *head);
bool checkKey(int key);


int main(){
    snake_body *head= new snake_body [1];
    snake_body *last= new snake_body [1];
    (*head) = snake_body (5, 5, HEAD);
    last = head;
    cout << " 0 ";
    for (int i=1; i<=3 ; i++){
        cout << i << endl;
        inp_1(last);
    }

    system("pause");
    system("cls");

    for (int i=1 ; i<=15 ; i++){
        system("cls");
        print_all(head);
        snake_body *t = new snake_body[1];
        (*t) = snake_body(head->get_x(), head->get_y(), head->get_node(), BODY);

        head ->change_direction();
        head -> move_snake();
        head -> set_node(t);

        Sleep(600);
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
    if (part == BODY)
        cout << shape;
    else if (part == HEAD)
        cout << '@';
}

void inp_1(snake_body *(&last)){
    snake_body* t=new snake_body [1];
    t->inp_node();
    last->node = t;
    last = t;
}

void snake_body::move_snake(){
    if (direction == LEFT){
        x--;
    }
    else if (direction == RIGHT){
        x++;
    }
    else if (direction == UP){
        y--;
    }
    else if (direction == DOWN){
        y++;
    }
}
directions snake_body::get_direction(){
    return direction;
}
void print_all(snake_body *head){
    while (head!= NULL){
            (*head).print();
            head = (head)->get_node();
        }
}
int snake_body::get_x(){
    return x;
}
int snake_body::get_y(){
    return y;
}
bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}
void snake_body::change_direction(){
    if (checkKey(VK_LEFT) && direction!=RIGHT)
            direction = LEFT;
        else if (checkKey(VK_RIGHT) && direction!=LEFT)
            direction = RIGHT;
        else if (checkKey(VK_DOWN) && direction != UP)
            direction = DOWN;
        else if (checkKey(VK_UP) && direction != DOWN)
            direction = UP;
}
