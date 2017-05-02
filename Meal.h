#ifndef MEAL_H
#define MEAL_H


class Meal
{
    public:
        Meal();
 //       Meal(int _x, int _y);
        void set_x(const int _x);
        void set_y(const int _y);
        void Sinh(const int xmax, const int ymax)
        virtual ~Meal();

    protected:

    private:
        int x;
        int y;
};

#endif // MEAL_H
