sh main.cpp
================================================================================

find /Archive -name main.cpp | wc -l
================================================================================

zoidberg || zoidberg
================================================================================


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) = delete; // { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
//    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};       // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  //const char s[6] ="Hello";                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  char s[6] = "Hello";
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>

int main() {
    std::cout << "Hello, world!\n";
}

================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  //const char s[6] ="Hello";                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  char s[6] = "Hello";
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  const char s[6] ="Hello";                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  const char s[6]{"Hello"};                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  char s[6]{"Hello"};                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  char s[6] = "Hello";                           
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  const A (&a1)[2] = {{1, 2}, 3};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  const A (&a1)[2] = {};
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a8(static_cast<const A (&)[2]>({}))
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a6{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a7{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a5{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a6{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
//  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
//    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a5{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a6{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, {3}}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a5{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a6{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4[2]{{1, 2}, 3};    // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, 3}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a5{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a6{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{1, 2};         // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4{{1, 2}, 3};       // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, 3}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
  A()          { cout << "A()"          << endl; }
  A(int)       { cout << "A(int)"       << endl; }
  A(int, int)  { cout << "A(int, int)"  << endl; }
  A(const A &) { cout << "A(const A &)" << endl; }
  ~A()         { cout << "~A()"         << endl; }
};

struct B
{
  A a1;
  A a2;
};

struct X
{
  X()
  {
    cout << "X()" << endl;
  }

  X(int)
    : m_a1()            // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => each element is directly value-initialized:
                        //                                                                        A(), A()
                        // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
    , m_a2(m_a1)        // InitializerList_t(m_a1)->MakeExpression()                           => ill-formed (except for internal copy-constructor use, which copies m_a1)
    , m_a3(1, 2)        // InitializerList_t(1, 2)->MakeExpression()                           => ill-formed; array initialization requires curly braces
    , m_a4{}            // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                        //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
    , m_a5{1, 2}        // InitializerList_t(1, 2)                                             => each element is copy initialized:
                        //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
    , m_a6{{1, 2}, 3}   // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                        //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  {
    cout << "X(int)" << endl;
  }

  ~X()
  {
    cout << "~X()" << endl;
  }

  A m_a1[2];               // static_cast<pExpr_t>(nullptr)                                       => each element is directly default-initialized: A(), A()
                           //                                                                        A(), A()
  A m_a2[2]{};             // InitializerList_t(MakeFakeExpression(ST_BTempty))                   => each element is copy initialized:
                           //                                                                        A(), A(const A &), A(), A(const A &), ~A(), ~A()
  A m_a3[2]{e1, e2};       // InitializerList_t(1, 2)                                             => each element is copy initialized:
                           //                                                                        A(int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a4{{1, 2}, 3};       // InitializerList_t(InitializerList_t(1, 2), 3)                       => each element is copy initialized:
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), ~A(), ~A()
  A m_a5[2] = m_a1;        // m_a1                                                                => ill-formed; array initialization requires curly braces
  A m_a6[2] = {};          // InitializerList_t(MakeFakeExpression(ST_BTempty))->MakeExpression() => copy of static_cast<const A (&)[2]>({}):
                           //                                                                        A(), A(const A &), A(), A(const A &), A(const A &), A(const A &), ~A(), ~A()
                           // MakeFakeExpression(ST_BTempty)                                      => [alternate encoding of above]
  A m_a7[2] = {1, 2};      // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1}, A{2}}):
                           //                                                                        A(int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
  A m_a8[2] = {{1, 2}, 3}; // InitializerList_t(1, 2)->MakeExpression()                           => copy of static_cast<const A (&)[2]>({A{1, 2}, A{3}}):
                           //                                                                        A(int, int), A(const A &), A(int), A(const A &), A(const A &), A(const A &), ~A(), ~A()
};

int main()
{
  X x1;
  X x2(1);
}


================================================================================

#include "/bin/cat"

int main() {
    
}

================================================================================

HEADER='<html><body>'
FOOTER='</body></html>'

for f in `ls -t /Archive | head -n10` ; do 
    echo "<a href='$f'>$f</a>" >> body
done

echo "${HEADER}
$(cat body)
${FOOTER}"
================================================================================

<html>
<body>
<h1>Hello World!</h1>
</body>
</html>
================================================================================

<html>
<body>
<h1>Hello World!</h1>
</body>
</html>
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}

================================================================================

Hello World!
================================================================================

Hello World!
================================================================================

zoidberg 'Hello World!'
================================================================================


================================================================================

hello world
================================================================================


<!DOCTYPE html>
<html>
<head>

    <title>Coliru History</title>
    <style type="text/css">

        html, body, textarea {
            position: relative;
            font-family: monospace;
            width: 100%;
            height: 100%;
        }
        body { 
            overflow: scroll;
        }

        h1 { margin: 8px; }
        h2 { margin: 12px; }

        #page {
            position: relative;
            width: 100%;
            height: 100%;
        }

        .margin {
            min-width: 20px;
            padding: 40px;
        }

        textarea {
            border: 0; /*1px solid gray;*/
            min-width: 800px;
            max-width: 800px;
            outline: 0 !important;
            appearance: none;
            -webkit-appearance: none;
            -moz-appearance: none;
        }


        .hbox {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            padding: 0;
            margin: 0;
            box-orient: horizontal;
            -webkit-box-orient: horizontal;
            -moz-box-orient: horizontal;
            box-align: stretch;
            -webkit-box-align: stretch;
            -moz-box-align: stretch;
        }

        .vbox {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            padding: 0;
            margin: 0;
            box-orient: vertical;
            -webkit-box-orient: vertical;
            -moz-box-orient: vertical;
            box-align: stretch;
            -webkit-box-align: stretch;
            -moz-box-align: stretch;
        }

        .f0 {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            box-flex: 0.0;
            -webkit-box-flex: 0.0;
            -moz-box-flex: 0.0;
        }

        .f1 {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            box-flex: 1.0;
            -webkit-box-flex: 1.0;
            -moz-box-flex: 1.0;
        }

    </style>
    <script type="text/javascript" src="https://raw.github.com/timrwood/moment/2.0.0/min/moment.min.js"></script>
    <script>

        // Redirect www. to host domain.
        if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
            var host = window.location.hostname + "";
            host = host.replace(/^www./, "");
            host = host.replace(/^stacked/, "coliru.stacked");
            window.location.hostname = host;
        }


        window.http_get = function (url) {
            var x = new XMLHttpRequest();
            x.open("GET", url, false);
            x.send(null);
            return x.responseText;
        };


        window.onload = function () {

//            Element.prototype.createNBSP = function () {
//                this.appendChild(document.createTextNode("\u00a0"));
//            };
            Element.prototype.createChild = function (tagNamePath) {
                var result = this;
                var tagNames = tagNamePath.split("/");
                for (var i = 0; i < tagNames.length; ++i) {
                    var child = document.createElement(tagNames[i]);
                    result.appendChild(child);
                    result = child;
                }
                return result;
            };
            var getHistory = function () {
                var historyObj = localStorage['history_items'];
                if (historyObj === undefined) {
                    historyObj = '{}';
                } else if (historyObj === null) {
                    localStorage.clear();
                    historyObj = '{}';
                }

                return JSON.parse(historyObj);
            };
            var history = getHistory();

            var length = Object.keys(history).length;

            if (length === 1) {
                document.getElementById('h2').textContent = "There is currently " + length + " item in your history.";
            } else {
                document.getElementById('h2').textContent = "There are currently " + length + " items in your history.";
            }


            var bydate = [];
            for (var key in history) {
                if (history.hasOwnProperty(key))
                {
                    var obj = history["" + key];
                    bydate.push(JSON.stringify({ 'timestamp':obj.timestamp, 'url':obj.url, 'src':obj.src, 'cmd':obj.cmd, 'output':obj.output }));
                }
            }

            bydate.sort(function (a, b) {
                if (a !== b) {
                    if (a < b) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                return -1;
            });

            for (var i = 0; i < bydate.length; ++i) {
                var obj = JSON.parse(bydate[i]);
                var url = obj.url;
                var c = document.getElementById('content');
                var a = c.createChild('div/strong/a');
                a.href = url;
                a.textContent = moment.unix(obj.timestamp / 1000).fromNow();

                var d = c.createChild('div');

                var cmd_field = d.createChild('div/textarea');
                cmd_field.setAttribute('readonly', 'true');

                cmd_field.textContent = obj.src + '\n\n\n' + obj.cmd + '\n' + obj.output;
                cmd_field.rows = Math.min(20, cmd_field.textContent.split('\n').length);
                cmd_field.setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                cmd_field.onkeydown = function(e){
                    if (e.keyCode == 27) {
                        this.setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                        var oldw = this.width;
                        document.body.style.overflow='scroll';
                        this.width = oldw;
                        this.blur();
                    }
                };
                cmd_field.onmouseup = function(){
                    this.select();
                    this.setAttribute('style', 'overflow-y:scroll; background-color: #EEEEEE');
                };
                cmd_field.onmousedown = function(){
                    document.body.style.overflow='hidden';
                    var textareas = document.getElementsByTagName('textarea');
                    for (var i = 0; i < textareas.length; ++i)
                    {
                        textareas[i].setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                    }
                };
                d.createChild('br');
            }
        }
    </script>
</head>
<body class="vbox f1">
<h1>Coliru History</h1>
<h2 id="h2">Coliru History</h2>


<div class='hbox f1'>
    <div class='margin'></div>
    <div id="content" class="vbox f1"></div>
    <div class='margin'></div>
</div>
</body>
</html>

================================================================================


================================================================================

echo hi
================================================================================

echo hi
================================================================================


class ModelMeshPart {
     // At first, having a `MeshPart` seems unncesarry,
     // but as XNA and other non-independent projects
     // have surmised, Parts should be broken up by
     // material, to avoid doing many shader switches
     // thus, a ModelMeshPart contains an
     // Index and/or Vertex Buffer, plus materials related specifically to that buffer
}

class ModelMesh {
    // Here, we put multiple ModelMeshParts
    // We also have bones here, because Bones pertain to a whole Mesh and
    // are not split up by Materials on a single Mesh
    // Thus, this acts as the highlevel "Mesh" that will also
    // take care of animation.
    // Rendering it will just be a matter of making sure the bones match up to the
    // individual mesh parts,
    // but if it gets too complicated we can always just scrap the ModelMeshPart
    // and take the hit for multiple shader constant buffer switches
}

class Model {
    // The high-level container for ModelMesh.
    // It will contain:
    // a ModelTextureCollection, for textures that have been loaded for use with the meshes and materials
    // a ModelBoneCollection, for all the bones in all the meshes
    // a ModelMaterialCollection, for all the materials. This could be moved downstream to ModelMeshPart
    // and we could just make the ModelMeshPart the owner of its own materials (this would eliminate the need for a ModelTextureCollection)
}

int main ( int argc, char* argv[] ) {
    
    
    
}
================================================================================

# Shows most recent coliru posts
POSTS="$(ls -t /Archive/*/timestamp | xargs -I {} dirname {} | xargs -I {} basename {})"
for p in $POSTS ; do 
    echo -n $(date -d @$(cat /Archive/$p/timestamp)) ; echo ": http://coliru.stacked-crooked.com/view?=$p"
done
================================================================================

# Shows most recent coliru posts
POSTS="$(ls -t /Archive/*/timestamp | xargs -I {} dirname {} | xargs -I {} basename {})"
for p in $POSTS ; do 
    echo -n $(date -d @$(cat /Archive/$p/timestamp) +"%Y-%m-%d %H:%M:%S") ; echo ": http://coliru.stacked-crooked.com/view?=$p"
done
================================================================================

ModelMeshPart Load ( string somefile ) {
    // How access and build ModelMeshPart? :c
}

class ModelMeshPart {
private:
    // How populate with datas? :c
    ModelMesh* parentmodelmesh;
	const Matrix* bonetransforms;
	Matrix world;
	ulword rootbone;
	std::vector<ulword> bones;
	std::unordered_map<String, ulword> boneindices;
	std::vector<ulword> materials;
	std::unordered_map<String, ulword> materialindices;
	BoundingBox box;
	String name;
	ptr<VertexBuffer> vertices;
	ptr<IndexBuffer> indices;
	PrimitiveTopology topology;
	uint32 vertexoffset, indexoffset, primitivecount;

public:
	
	ModelMeshPart ();
    
}

int main ( int argc, char* argv[] ) {
    
    
    
}
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}

================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}

================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}

================================================================================


================================================================================

# Finding the most recent Coliru posts.
find /Archive -name timestamp | xargs grep . \
    | perl -p -e 's,(.+?):(.+),\2 \1,g' \
    | sort -r -n \
    | cut -d ' ' -f2 \
    | xargs -I {} dirname {} \
    | xargs -I {} echo "{}/main.cpp" \
    | xargs -I {} bash -c "echo '// =============================================================================' ; cat {} ; echo"



================================================================================

Finding the most recent Coliru posts.
================================================================================


================================================================================

// Finds the most recent post.
================================================================================

// Finds the most recent post.
================================================================================

// Finds the most recent post.
================================================================================

#include <tuple>

template<typename TL, class T1, class T2> struct Functor{};
template< typename TL,
          template<size_t...> class T1, size_t... A1, // read only arguments
          template<size_t...> class T2, size_t... A2  // read-write arguments
        >
struct Functor< TL, T1<A1...>, T2<A2...>> {
    typedef void (*Type)(const typename std::tuple_element<A1, TL>::type* ... ,
                               typename std::tuple_element<A2, TL>::type* ...);

    Functor(Type) {}
};

void foo(const float  *,
         const int    *,
               double *)
{}

template<size_t ... T> struct Pack {};

int main()
{
    using Pixel = std::tuple<float, double, int>;
    Functor<Pixel, Pack<0,2>, Pack<1>> apply_foo(foo);
}
================================================================================

#include <iostream>
#include <limits>

int main()
{
    float fInf = std::numeric_limits<float>::infinity();
    double dInf = std::numeric_limits<double>::infinity();
    std::cout << (fInf == fInf) << std::endl;
    std::cout << (dInf == dInf) << std::endl;
}

================================================================================

#include <functional>


template <typename T, typename...Args>
std::function<T*()> MakeFactoryMethod(Args&&... args)
{
    return std::bind([](Args&... args2)
        {
            return new T(std::forward<Args>(args2)...);
        },
        std::forward<Args>(args)...);
}

struct foo {
    explicit foo(int) {}
};

int main()
{
    auto test = MakeFactoryMethod<foo>(5);
    delete test();
}
================================================================================

#include <tuple>

template<typename TL, class T1, class T2> struct Functor{};
template< typename TL,
          template<size_t...> class T1, size_t... A1, // read only arguments
          template<size_t...> class T2, size_t... A2  // read-write arguments
        >
struct Functor< TL, T1<A1...>, T2<A2...>> {
    typedef void (*Type)(const typename std::tuple_element<A1, TL>::type* ... ,
                               typename std::tuple_element<A2, TL>::type* ...);

    Functor(Type) {}
};

void foo(const float  *,
               double *,
         const int    *)
{}

template<size_t ... T> struct Pack {};

int main()
{
    using Pixel = std::tuple<float, double, int>;
    Functor<Pixel, Pack<0,2>, Pack<1>> apply_foo(foo);
}
================================================================================

template <class T>
class Outer {
    Outer();
    void foo();
};

template<class T>
Outer<T>::Outer<T>() {}

// Not working
template <class T>
typename Outer<T>::Inner* Outer<T>::x = 0;

int main() {
    int x;
}
================================================================================

#include <iostream>
#include <string>
#include <vector>

struct X
{
  X() : m_a() {}             // well-formed
  X(int (&a)[3]) : m_a{a} {} // ill-formed; however, compiler-generated copy constructors may do this; see ConstructorPrologProcessor::BaseOrMemberProcessor::Process
  X(int) : m_a(1, 2, 3) {}   // ill-formed
  X(char) : m_a{1, 2, 3} {}  // well-formed; new behavior in C++11

  int m_a[3];
  int m_b1[3]{};           // well-formed
  int m_b2[3] = {};        // well-formed
  int m_b3[3]{1, 2, 3};    // well-formed
  int m_b4[3] = {1, 2, 3}; // well-formed
  int m_b5[3]{m_a};        // ill-formed
  int m_b6[3] = m_a;       // ill-formed
};

int main()
{
}

================================================================================

#include <iostream>
#include <string>
#include <vector>

struct X
{
  X() : m_a() {}             // well-formed
//  X(int (&a)[3]) : m_a{a} {} // ill-formed; however, compiler-generated copy constructors may do this; see ConstructorPrologProcessor::BaseOrMemberProcessor::Process
//  X(int) : m_a(1, 2, 3) {}   // ill-formed
  X(char) : m_a{1, 2, 3} {}  // well-formed; new behavior in C++11

  int m_a[3];
  int m_b1[3]{};           // well-formed
  int m_b2[3] = {};        // well-formed
  int m_b3[3]{1, 2, 3};    // well-formed
  int m_b4[3] = {1, 2, 3}; // well-formed
//  int m_b5[3]{m_a};        // ill-formed
//  int m_b6[3] = m_a;       // ill-formed
};

int main()
{
}

================================================================================

#include <iostream>
#include <string>
#include <vector>

struct X
{
  X() : m_a() {}             // well-formed
  X(int (&a)[3]) : m_a{a} {} // ill-formed; however, compiler-generated copy constructors may do this; see ConstructorPrologProcessor::BaseOrMemberProcessor::Process
  X(int) : m_a(1, 2, 3) {}   // ill-formed
  X(char) : m_a{1, 2, 3} {}  // well-formed; new behavior in C++11

  int m_a[3];
  int m_b1[3]{};           // well-formed
  int m_b2[3] = {};        // well-formed
  int m_b3[3]{1, 2, 3};    // well-formed
  int m_b4[3] = {1, 2, 3}; // well-formed
  int m_b5[3]{m_a};          // ill-formed
  int m_b6[3] = m_a;       // ill-formed
};

int main()
{
}

================================================================================

#include <iostream>
#include <mutex>


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<const T> operator->() const;
    
    Locker<T> operator->();

private:    
    friend class Locker<T>;
    friend class Locker<const T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK" << std::endl;
    }
    
    Locker(Locker<T> && rhs) = default;
    
    ~Locker()
    {
        std::cout << "UNLOCK\n" << std::endl;
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
struct Locker<const T>
{
    Locker(const Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK (const)" << std::endl;
    }
    
    Locker(Locker<const T> && rhs) = default;
    
    ~Locker()
    {
        std::cout << "UNLOCK (const)\n" << std::endl;
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};


template<typename T>
Locker<T> Protected<T>::operator->()
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
    void car() const { std::cout << "Foo::car() const" << std::endl; }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T> for full access.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<const T> for const access
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car(); // can only call const methods
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    
================================================================================

#include <iostream>
#include <mutex>


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<const T> operator->() const;
    Locker<T> operator->();

private:    
    friend class Locker<T>;
    friend class Locker<const T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK" << std::endl;
    }
    
    Locker(Locker<T> && rhs) = default;
    
    ~Locker()
    {
        std::cout << "UNLOCK\n" << std::endl;
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
struct Locker<const T>
{
    Locker(const Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK (const)" << std::endl;
    }
    
    Locker(Locker<const T> && rhs) = default;
    
    ~Locker()
    {
        std::cout << "UNLOCK (const)\n" << std::endl;
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};


template<typename T>
Locker<T> Protected<T>::operator->()
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
    void car() const { std::cout << "Foo::car() const" << std::endl; }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car();
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    
================================================================================

#include <iostream>
#include <mutex>


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<const T> operator->() const;
    Locker<T> operator->();

private:    
    friend class Locker<T>;
    friend class Locker<const T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK" << std::endl;
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
        std::cout << "MOVE LOCK" << std::endl;
    }        
    
    ~Locker()
    {
        std::cout << "UNLOCK\n" << std::endl;
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
struct Locker<const T>
{
    Locker(const Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        std::cout << "LOCK (const)" << std::endl;
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
        std::cout << "MOVE LOCK (const)" << std::endl;
    }        
    
    ~Locker()
    {
        std::cout << "UNLOCK (const)\n" << std::endl;
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};


template<typename T>
Locker<T> Protected<T>::operator->()
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { std::cout << "Foo::bar()" << std::endl; }
    void car() const { std::cout << "Foo::car() const" << std::endl; }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car();
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    
================================================================================

#include <iostream>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<const T> operator->() const;
    Locker<T> operator->();

private:    
    friend class Locker<T>;
    friend class Locker<const T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        TRACE
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
        TRACE
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
struct Locker<const T>
{
    Locker(const Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        TRACE
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
        TRACE
    }
    
    const T& get() const { return obj_; }    
    const T* operator->() const { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    const T & obj_;
};


template<typename T>
Locker<T> Protected<T>::operator->()
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


template<typename T>
Locker<const T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { TRACE }
    void car() const { TRACE }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
        foo.car();
    }
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<const Foo> locker(foo);
        const Foo & foo = locker.get();
        foo.car();
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
    foo->car();
}

    
================================================================================

#include <iostream>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<T> operator->() const;

private:    
    friend class Locker<T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        TRACE
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
        TRACE
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
Locker<T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}

struct Foo
{
    void bar() { TRACE }
};

int main()
{
    Protected<Foo> foo;
    
    // Using Locker<T>
    // add scope to define scope of lock.
    {
        Locker<Foo> locker(foo);
        Foo & foo = locker.get();
        foo.bar();
    }
    
    
    // Single actions can be performed quickly with operator-> 
    foo->bar();
}

    
================================================================================

#include <cassert>

int main() {
    int UB;
    assert(UB <3);
}

================================================================================

#include <cassert>

int main() {
    int UB;
    assert(UB <3);
}
================================================================================

#include <assert>

int main() {
    int UB;
    assert(UB <3);
}
================================================================================

auto rock = 1;
auto paper = 2;
auto scissors = 3;

int main()
{
    return rock, paper and scissors;
}

================================================================================

auto rock = 1;
auto paper = 2;
auto scissors = 3;

int main()
{
    return rock, paper and scissors;
}

================================================================================

#include <iostream>
#include <string>
#include <vector>

#include <boost/any.hpp>

int main()
{
    std::vector<boost::any> v;
    
    v.push_back(std::string { "Hi" });
    v.push_back(42);
    
    std::cout << v[0] << " " << v[1] ;
}
================================================================================

#include <string>
#include <vector>

#include <boost/any.hpp>

int main()
{
    std::vector<boost::any> v;
    v.push_back(std::string { "Hi" });
    v.push_back(42);
}
================================================================================

#include <iostream>
#include <mutex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename>
struct Locker;


template<typename T>
struct Protected
{
    template<typename ...Args>
    Protected(Args && ...args) :
        obj_(std::forward<Args>(args)...)
    {        
    }
    
    Locker<T> operator->() const;

private:    
    friend class Locker<T>;
    mutable std::mutex mtx_;
    T obj_;
};


template<typename T>
struct Locker
{
    Locker(Protected<T> & p) :
        lock_(p.mtx_),
        obj_(p.obj_)
    {
        TRACE
    }
    
    Locker(Locker<T> && rhs) :
        lock_(std::move(rhs.lock_)),
        obj_(rhs.obj_)
    {
    }        
    
    ~Locker()
    {
        TRACE
    }
    
    const T& get() const { return obj_; }
    T& get() { return obj_; }
    
    const T* operator->() const { return &get(); }
    T* operator->() { return &get(); }
    
private:    
    std::unique_lock<std::mutex> lock_;
    T & obj_;    
};


template<typename T>
Locker<T> Protected<T>::operator->() const
{
    return Locker<T>(const_cast<Protected<T>&>(*this));
}


int main()
{
    struct Foo
    {
        void bar() { TRACE }
    };
    
    Protected<Foo> foo;
    foo->bar();
}

    
================================================================================

#include<stdio.h>
main()
{
    printf("hello world");
    return 0;
}
================================================================================

#include <iostream>
#include <string>
#include <utility>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vec)
{
    for (const auto & x : vec)
    {
        os << x << " ";
    }
    return os;
}


struct range
{
    range(int * b, int * e) : begin(b), end(e) {}
    
    std::size_t size() const { return end - begin; }
    
    std::pair<range, range> split()
    {
        auto s2 = size() / 2;
        return std::make_pair(range(begin, begin + s2),
                              range(begin + s2, end + s2));
    }
    
    int & operator[](int n)
    {
        return begin[n];
    }
    
    int * begin;
    int * end;    
};


std::ostream& operator<<(std::ostream& os, const range & r)
{
    for (auto i = r.begin; i != r.end; ++i)
    {
        os << (*i) << "  ";
    }
    return os;
}


void qsort(range & v)
{    
    std::cout <<  v << std::endl;
            
    auto size = v.end - v.begin;
    if (size <= 1)
        return;
        
    if (v.size() == 2 && v[1] < v[0])
    {
        std::cout <<  v << std::endl;
        std::swap(v[0], v[1]);
    }
        
        
    auto p = v.size() / 2;
    
    
    std::size_t i = 0, j = v.size() - 1;
    for (;;)
    {        
        while (v[i] < v[p] && i < p) i++;
        
        std::size_t j = v.size() - 1;
        while (v[j] > v[p] && j > p) j--;
        
        if (i < p)
        {
            if (j > p)
            {
                std::swap(v[i], v[j]);
                std::cout <<  v << std::endl;
            }
            else
            {
                v.insert(v.begin() + p + 1, v[i]);
                v.erase(v.begin() + 1);
                std::cout <<  v << std::endl;
            }
        }        
        else if (j > p)
        {
            auto copy = v[j];
            v.erase(v.begin() + j);
            v.insert(v.begin(), copy);
            std::cout <<  v << std::endl;         
        }
        else
        {
            
            qsort(left_side);
            qsort(right_side);
            
            break;
        }
    }
}


std::vector<int> v = { 6, 5, 1, 4, 2, 3 };


int main()
{
    range r(&v[0], &v[0] + v.size());
    
    qsort(r);
    std::cout << "Sorted: " << v << std::endl;
}



================================================================================

#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
typename TGetter = default_get<T>, 
typename TLValueSetter = default_set<T>, 
typename TRValueSetter = default_set<T>>
struct property : private std::tuple<TGetter, TLValueSetter, TRValueSetter> {
private:
	typedef std::tuple<TGetter, TLValueSetter, TRValueSetter> getset;

public:
	T val;

	property ( const T& value, const TGetter& valuegetter = TGetter(), const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
		: getset( valuegetter, lvaluesetter, rvaluesetter ) {
			set( value );
	}

	T& data () {
		return val;
	}

	const T& data () const {
		return val;
	}

	T get () {
		return std::get<0>( *this )( val );
	}

	void set ( const T& right ) {
		std::get<1>( *this )( val, right );
	}

	void set ( T&& right ) {
		std::get<2>( *this )( val, std::move( right ) );
	}

	property& operator= ( const T& right ) {
		set( right );
		return *this;
	}

	property& operator= ( T&& right ) {
		set( std::move( right ) );
		return *this;
	}

	operator T () {
		return get();
	}
};

struct Hehehe {
    union {
        int v;
        property<int> prop;
    };
    
    Hehehe () {
        
    }
};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v + 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    Hehehe heart;
    heart.prop = rawprop;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << heart.v << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
    std::cout << sizeof(Hehehe) << std::endl;
}
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//d
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//c
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//b
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//a
================================================================================

#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
    typename TGetter = default_get<T>, 
	typename TLValueSetter = default_set<T>, 
	typename TRValueSetter = default_set<T>>
	struct property
    : private std::tuple<TGetter, TLValueSetter, TRValueSetter> {
    private:
        using getset = std::tuple<TGetter, TLValueSetter, TRValueSetter>;
	public:
		T val;

		property ( const T& value, const TGetter& valuegetter = TGetter(), const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
		: getset( valuegetter, lvaluesetter, rvaluesetter ) {
			set( value );
		}

		T get () {
			return std::get<0>( *this )( val );
		}

		void set ( const T& right ) {
			std::get<1>( *this )( val, right );
		}

		void set ( T&& right ) {
			std::get<2>( *this )( val, std::forward<T>( right ) );
		}

		property& operator= ( const T& right ) {
			set( right );
			return *this;
		}
        
		property& operator= ( T&& right ) {
			set( std::move( right ) );
			return *this;
		}

		operator T () {
			return get();
		}
	};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}
================================================================================

#include <utility>
#include <type_traits>
#include <iostream>
#include <tuple>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
    typename TGetter = default_get<T>, 
	typename TLValueSetter = default_set<T>, 
	typename TRValueSetter = default_set<T>>
	struct property {
	public:
		std::tuple<T, TGetter, TLValueSetter, TRValueSetter> getset;
		
		property ( const T& value, const TGetter& valuegetter = TGetter(), const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
		: getset( value, valuegetter, lvaluesetter, rvaluesetter ) {
			set( value );
		}

		T get () {
			return std::get<1>( getset )( std::get<0>( getset ) );
		}

		void set ( const T& right ) {
			std::get<2>( getset )( std::get<0>( getset ), right );
		}

		void set ( T&& right ) {
			std::get<3>( getset )( std::get<0>( getset ), std::move( right ) );
		}

		property& operator= ( const T& right ) {
			set( right );
			return *this;
		}

		property& operator= ( T&& right ) {
			set( std::move( right ) );
			return *this;
		}

		operator T () {
			return get();
		}
	};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}
================================================================================

#include <type_traits>
#include <tuple>
#include <iostream>

int main(){
    auto l = [](int i){ return i * 42; };
    typedef std::tuple<decltype(l)> tuple_t;
    
    static_assert(std::is_empty<tuple_t>(), "non-empty tuple with empty lambda");
    
    struct is_it_really {
        tuple_t t;
    };
    
    static_assert(std::is_empty<is_it_really>(), "non-empty struct containing tuple with empty lambda");

}
================================================================================

#include <type_traits>

int main(){
    auto l = [](int i){ return i * 42; };
    static_assert(std::is_empty<decltype(l)>(), "non-empty empty lambda");
}
================================================================================

#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
    typename TGetter = default_get<T>, 
	typename TLValueSetter = default_set<T>, 
	typename TRValueSetter = default_set<T>>
	struct property {
	public:
		std::tuple<TGetter, TLValueSetter, TRValueSetter> getset;
		T val;

		property ( const T& value, const TGetter& valuegetter = TGetter(), const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
		: getset( valuegetter, lvaluesetter, rvaluesetter ) {
			set( value );
		}

		T get () {
			return std::get<0>( getset )( val );
		}

		void set ( const T& right ) {
			std::get<1>( getset )( val, right );
		}

		void set ( T&& right ) {
			std::get<2>( getset )( val, std::forward<T>( right ) );
		}

		property& operator= ( const T& right ) {
			set( right );
			return *this;
		}
        
		property& operator= ( T&& right ) {
			set( std::move( right ) );
			return *this;
		}

		operator T () {
			return get();
		}
	};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}
================================================================================

#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
struct default_get {
	T operator () ( T& current ) {
		return current;
	}
};

template <typename T>
struct default_set {

	void operator () ( T& current, const T& val ) {
		current = val;
	}

	void operator () ( T& current, T&& val ) {
		current = std::move( val );
	}

};

template <typename T, 
	typename TGetter = default_get<T>, 
	typename TLValueSetter = default_set<T>, 
	typename TRValueSetter = TLValueSetter, 
	bool isdefaultconstructible = 
	std::is_default_constructible<TGetter>::value && 
	std::is_default_constructible<TLValueSetter>::value && 
	std::is_default_constructible<TRValueSetter>::value>
struct property;

template <typename T, 
	typename TGetter, 
	typename TLValueSetter, 
	typename TRValueSetter>
struct property<T, TGetter, TLValueSetter, TRValueSetter, true> {
public:
	T val;

	property () {

	}

	property ( const T& value ) {
		set( value );
	}

	property ( T&& value ) {
		set( std::forward<T>( value ) );
	}

	T get () {
		TGetter getter;
		return getter( val );
	}

	void set ( const T& right ) {
		TLValueSetter setter;
		setter( val, right );
	}

	void set ( T&& right ) {
		TRValueSetter setter;
		setter( val, std::forward<T>( right ) );
	}

	property& operator= ( const T& right ) {
		set( right );
		return *this;
	}

	property& operator= ( T&& right ) {
		set( std::forward<T>( right ) );
		return *this;
	}

	operator T () {
		return get();
	}
};

template <typename T, 
	typename TGetter, 
	typename TLValueSetter, 
	typename TRValueSetter>
struct property<T, TGetter, TLValueSetter, TRValueSetter, false> {
public:
	TGetter getter;
	TLValueSetter lsetter;
	TRValueSetter rsetter;
	T val;

    property ( const TGetter& valuegetter, const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {

	}

	property ( const T& value, const TGetter& valuegetter, const TLValueSetter& lvaluesetter = TLValueSetter(), const TRValueSetter& rvaluesetter = TRValueSetter() )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {
		set( value );
	}

	property ( T&& value, const TGetter& valuegetter, const TLValueSetter& lvaluesetter, const TRValueSetter& rvaluesetter )
	: getter( valuegetter ), lsetter( lvaluesetter ), rsetter( rvaluesetter ) {
		set( std::forward<T>( value ) );
	}

	T get () {
		return getter( val );
	}

	void set ( const T& right ) {
		lsetter( val, right );
	}

	void set ( T&& right ) {
		rsetter( val, std::forward<T>( right ) );
	}

	property& operator= ( const T& right ) {
		set( right );
		return *this;
	}

	property& operator= ( T&& right ) {
		set( std::forward<T>( right ) );
		return *this;
	}

	operator T () {
		return get();
	}
};

int main ( int argc, char* argv[] ) {
    auto fget = []( int& v )->int { return v = 200; };
    property<int, decltype(fget)> prop( 500, fget );
    property<int> rawprop = 500;
    
    std::cout << prop << std::endl;
    std::cout << rawprop << std::endl;
    std::cout << sizeof(prop) << std::endl;
    std::cout << sizeof(rawprop) << std::endl;
}
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//d
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//testje with timestampc
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//testje with timestampc
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//testje with timestampb
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//testje with timestampa
================================================================================

#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
//testje with timestamp