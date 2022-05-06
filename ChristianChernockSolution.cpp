// Christian Chernock Solution
// Uses C++ 17 or higher

#include <tuple>
#include <iostream>
using namespace std;

// Get type: 
//   i = numeric
//   s = string or character
//   x = ignore
template <typename T> constexpr char getType() {
    if (is_convertible_v<T, int>) { return 'i'; } // Check if numeric
    else if (is_convertible_v<T, string>) { return 's'; } // check if castable
    else { return 'x'; }
}

// Boolean
template <> constexpr char getType<bool>() { return 'x'; } 

// Character types
#define CHARACTERS(C) template <> constexpr char getType<C>() { return 's'; }
CHARACTERS(char);
CHARACTERS(signed char);
CHARACTERS(unsigned char);
CHARACTERS(wchar_t);
//CHARACTERS(char8_t); // C++ 20 only
CHARACTERS(char16_t);
CHARACTERS(char32_t);

template<size_t I, typename Tuple, typename Output>
void foreach(Tuple& in, Output& out) {
    if constexpr (I > 0) { foreach<I - 1>(in, out); } // Foreach
    const char constexpr isType = getType<tuple_element_t<I, Tuple>>(); // Get type
    if constexpr (isType == 'i') { // Add numeric entries together
        get<0>(out) += get<I>(in);
    } else if constexpr (isType == 's') { // Concatenate strings and characters
        get<1>(out) += " ";
        get<1>(out) += get<I>(in);
    } else {
        get<2>(out)++;  // Increase ignored counter
    }
}

template<class ...Args>
void TupleCodeChallenge(tuple<Args...> input) {
    using Output = tuple<double, string, int>; // Output is: double, string, int
    Output out(0, "", 0);   // Create output tuple
    const size_t size = tuple_size<tuple<Args...>>::value; // Get input size
    // Ensure input is not empty
    if constexpr (size > 0) { foreach<size - 1>(input, out); } // Loop input and get output
    cout << get<0>(out) << "," << get<1>(out) << ", " << get<2>(out) << endl; // Display output
}

int main() {
    using Tuple = tuple<int32_t, bool, string, float, const char*>;
    Tuple t{ 10, true, "Modern", 2.3f, "C++"};
    TupleCodeChallenge(t);
    TupleCodeChallenge(make_tuple(1.1f, 2, "Hello", "World", '!', true));
}
