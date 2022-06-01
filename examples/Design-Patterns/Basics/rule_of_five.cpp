#include <iostream>
#include <cstring>
#include <utility>

using namespace std;
class RuleOfFive {
public:
    RuleOfFive( const char* s = "") {
        cout << "Standard Constructor!" <<"        :: " << this << endl;
        size_t n = strlen(s) + 1;
        buffer = new char[n];
        memcpy(buffer, s, n);
    }
    /* first. destructor */
    ~RuleOfFive() {
        cout << "Deleting:                    -- " << &buffer << endl;
        delete[] buffer;
    }
    /* second. copy constructor */
    RuleOfFive( const RuleOfFive& other) : RuleOfFive(other.buffer) {
        cout << "Copy Constructor!" << "            :: " << this << endl;
    }
    /* third. move constructor */
    RuleOfFive( RuleOfFive&& other) noexcept : buffer(exchange(other.buffer, nullptr)){
        cout << "Move Constructor!"<< "            :: " << this << endl;
    }
    /* fourth. copy assignment */
    RuleOfFive& operator=( const RuleOfFive& other) {
        cout << "Copy Assign Constructor!" << "     :: " << this << endl;
        /* calls move assignment */
        return *this = RuleOfFive(other.buffer);
    }
    /* fifth. move assignment */
    RuleOfFive& operator=( RuleOfFive&& other) noexcept {
        cout << "Move Assign Constructor!"<< "     :: " << this << endl;
        swap(buffer, other.buffer);
        return *this;
    }
    void print() {
        cout << buffer << " :: " << &buffer << endl;
    }
private:
    char* buffer;
};

int main() {
    /* Standard */
    cout << "\n:::STANDARD:::\n" << endl;
    RuleOfFive basic_con("Standard Constructor");

    cout << "\n:::COPY:::\n"<< endl;
    RuleOfFive copy_con{basic_con};
    RuleOfFive copy2_con = copy_con;

    cout << "\n:::MOVE:::\n"<< endl;
    RuleOfFive move_con(move(RuleOfFive("Move Constructor")));

    cout << "\n:::COPY ASSIGN:::\n"<< endl;
    RuleOfFive copy_assign_con;
    copy_assign_con = copy2_con;

    cout << "\n:::MOVE ASSIGN:::\n"<< endl;
    RuleOfFive move_assign_con;
    move_assign_con = move(RuleOfFive("Move Assignment"));

    cout << '\n' << endl;

    return EXIT_SUCCESS;
}