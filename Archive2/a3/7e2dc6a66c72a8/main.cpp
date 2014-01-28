#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>

class MyTemplateClass {
public:
    template<class T>
    void saveData(T data) {
        my_data = data;
    }
private:
    boost::any my_data;
};

class LibraryUser{
public:
    void saveData(double* data) {
        my_generic_object.saveData(data);
    }
    void saveData(float* data) {
        my_generic_object.saveData(data);
    }
private:
    MyTemplateClass my_generic_object;
};

int main()
{
    LibraryUser user;
    double d[2] = {1.1111, 2.222222};
    user.saveData(d);
    
	float f = 9.9999f;
    user.saveData(&f);
}