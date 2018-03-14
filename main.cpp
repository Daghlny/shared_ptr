
#include <iostream>
#include "shared_ptr.hpp"

class Test{
    public:
        Test(int _n):num(_n){}
        int num;
};

int main(void) {
    shared_ptr<int> sptr(new int(43));
    shared_ptr<int> s2ptr(sptr);
    std::cout << *s2ptr << std::endl;

    shared_ptr<int> s1ptr = s2ptr;

    std::cout << "Use count: " << s1ptr.get_usecount() << std::endl;

    //shared_ptr<Test> s3ptr(new Test(25));
    //std::cout << s3ptr->num << std::endl;
    return 0;
}
