#include <iostream>
using namespace std;

/* user defined functors */
struct AddOne {
    template<class T>
    auto operator()(T x) const { return x + 1; }
};

struct SumFunction {
    template<class T>
    auto operator()(T x, T y) const { return x + y; }
};

/*
 * Create a Pipeable Closure Function
 * Uses variadic template parameter pack
 */
template<class F>
struct PipeableClosure : F {
    template<class... Xs>
    PipeableClosure( Xs&&... xs) : F(forward<Xs>(xs)...) { }
};

/* helper function that converts a Function to a Closure */
template<class F>
auto makePipeClosure(F f) { return PipeableClosure<F>(move(f)); }

template<class F>
struct PipableClosureBinary {
    template<class... Ts>
    auto operator()(Ts... xs) const {
        return makePipeClosure( [=](auto x) -> decltype(auto) {
            return F()(x, xs...);});
    }
};

/* declare pipe operator */
template<class T, class F>
decltype(auto) operator|(T&& x, const PipeableClosure<F>& pfn) {
    return pfn(std::forward<T>(x));
}

int main() {
    const PipeableClosure<AddOne> fn_add_one = {};
    int value = 1 | fn_add_one | fn_add_one;
    cout << "add one : " << value << endl;

    const PipableClosureBinary<SumFunction> fn_sum = {};
    int value1 = 1 | fn_sum(2) | fn_sum(10) | fn_add_one;
    cout << "sum : " << value1 << endl;
}