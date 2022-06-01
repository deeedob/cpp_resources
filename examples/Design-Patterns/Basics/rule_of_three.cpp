#include <iostream>
#include <cstring>

using namespace std;

class RuleOfThree {
public:
    RuleOfThree( const char* s = ""){
        cout << "Standard Constructor!" <<"        :: " << this << endl;
        size_t n = strlen(s) +1;
        buffer = new char[n];
        memcpy(buffer, s, n);
    }
    /* first. destructor */
    ~RuleOfThree() {
        cout << "Deleting:                    -- " << &buffer << endl;
        delete[] buffer;
    }
    /* second. copy constructor*/
    RuleOfThree( const RuleOfThree& other) : RuleOfThree(other.buffer) {
        cout << "Copy Constructor!" << "            :: " << this << endl;
    }
    /* third. copy assignment */
    RuleOfThree& operator=( const RuleOfThree& other) {
        cout << "Copy Assign Constructor!" << "     :: " << this << endl;
        if(this == &other)
            return *this;

        size_t n{ strlen(other.buffer) +1 };
        char* tmp = new char[n];
        memcpy(tmp, other.buffer, n);
        delete[] buffer;
        buffer = tmp;
        return *this;

    }

    void print() {
        cout << buffer << " :: " << &buffer << endl;
    }
private:
    char* buffer;
};

int main() {
    cout << "\n:::STANDARD:::\n" << endl;
    RuleOfThree basic_con("Standard Constructor");

    cout << "\n:::COPY:::\n"<< endl;
    RuleOfThree copy_con{basic_con};
    RuleOfThree copy2_con = copy_con;

    cout << "\n:::COPY ASSIGN:::\n"<< endl;
    RuleOfThree copy_assign_con;
    copy_assign_con = copy2_con;

    cout << '\n' << endl;

    return EXIT_SUCCESS;
}