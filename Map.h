#ifndef MAP_H
#define MAP_H

enum Object{
    empt = 0,
    head,
    body,
    wall,
    meal
};
class Map
{
    public:
        Map();
        Map(Object _m);
        void set_m(Object _m);
        Object get_m();
        void print();

        virtual ~Map();

    protected:
    private:
        Object m;
};

#endif // MAP_H
