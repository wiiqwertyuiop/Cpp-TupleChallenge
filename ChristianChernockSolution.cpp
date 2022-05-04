// Christian Chernock Solution

#include <tuple>
#include <iostream>
using namespace std;

using output = tuple<double, string, int>; // Output is: double, string, int

template <typename T> constexpr char getType() { 
    if (is_convertible_v<T, int>) { return 'i'; } // Check if numeric
    else if (is_convertible_v<T, string>)  { return 's'; } // check if castable
    else { return 'x'; }
}

template <> constexpr char getType<bool>() { return 'x'; } // bool

// Character types
#define CHARACTERS(C) template <> constexpr char getType<C>() { return 's'; }
CHARACTERS(char);
CHARACTERS(signed char);
CHARACTERS(unsigned char);
CHARACTERS(wchar_t);
//CHARACTERS(char8_t); // C++ 20 only
CHARACTERS(char16_t);
CHARACTERS(char32_t);

template<size_t I, typename Tuple>
void foreach(Tuple& in, output& out) {
	
	// Foreach
    if constexpr (I > 0) { foreach<I-1>(in, out); } 
	
	// Get type
    const char isType = getType<tuple_element_t<I, Tuple>>(); 
	
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
    output out(0, "", 0);   // Create output tuple
    foreach<tuple_size<tuple<Args...>>::value-1>(input, out); // Loop through input tuple
    cout << get<0>(out) << "," << get<1>(out) << ", " << get<2>(out); // Display output
}

int main() {
    TupleCodeChallenge(make_tuple(10, true, "Modern", 2.3f, "C++"));
}
