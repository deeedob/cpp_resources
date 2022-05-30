#include <iostream>

/*
 * C# like getters and setters with clang!
 * */
class Person {
    int age_;
public:
    int get_age() const {
        return age_;
    }
    void set_age(const int val){
        age_ = val;
    }
    __declspec(property(get=get_age, put=set_age)) int age;
};

int main() {
    Person p;
    p.age = 100;

    std::cout << p.age << std::endl;
}
