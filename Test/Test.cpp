#include <iostream>
#include <map>

class B{
  public:
    virtual void f(){
        std::cout << "B" << std::endl;
    }
};

class B1 : virtual public B {
  public:
    virtual void f(){}
};

class B2 : virtual public B {
  public:
    virtual void f(){}
};

class B3 :  public B1,  public B2 {
  public:
    virtual void f(){}
};
int main(int argc, char **argv)
{
    B *pB = new B3();
    B1 *pB1 = dynamic_cast<B1*>(pB);
    B2 *pB2 = dynamic_cast<B2*>(pB1);
    B3 *pB3 = dynamic_cast<B3*>(pB2);
    return 0;
}