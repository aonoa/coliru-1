#include <boost/variant.hpp>
#include <iostream>
#include <ostream>

using namespace std;
using namespace boost;


struct Cellphone { bool touch_screen; };
struct Laptop { double screen_size; };
struct Desktop { int hdd; };

typedef variant<Cellphone, Laptop, Desktop> Product;

struct Print: static_visitor<>
{
    void operator()(const Cellphone &x) const
    {
        cout << "Cellphone, touch_screen:" << x.touch_screen << endl;
    }
    void operator()(const Laptop &x) const
    {
        cout << "Laptop, screen_size:" << x.screen_size << endl;
    }
};

int main()
{
    Cellphone phone = {true};
    Laptop laptop = {11.1};
    
    Product x = phone;
    apply_visitor(Print(), x);
    x = laptop;
    apply_visitor(Print(), x);
}
