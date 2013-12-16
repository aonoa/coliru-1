
#include <type_traits>

template<typename T>
void f_impl(T); //forward declaration

template<typename T>
void f(T)
{
    static_assert(T(), "first requirement failed to meet.");
    f_impl(T());
    T t = 10;
}

template<typename T>
void f_impl(T)
{
    static_assert(T::value, "second requirement failed to meet.");     
}   


int main()
{
    f(std::false_type{});
}
