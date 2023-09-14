#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cxxabi.h>
#include <format>

using namespace std;

#define WIDTH 30
#define TABLE_WIDTH 40 + WIDTH * 3

template <typename T>
void printTypeInfo(void)
{
    T t;
    
    char *real_name = abi::__cxa_demangle(typeid(t).name(), NULL, NULL, NULL); // http://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html

    cout << format("| {:<20} | {:^4} | {:^{}} | {:^{}} | {:^{}} |",
                   real_name, 
                   sizeof(t), 
                   numeric_limits<T>::lowest(), WIDTH, 
                   numeric_limits<T>::min()   , WIDTH, 
                   numeric_limits<T>::max()   , WIDTH) 
                   << endl;
    std::free(real_name);
}
 

int main()
{
    cout << std::string(TABLE_WIDTH, '=') << endl;
    cout << format("| {:<20} | {:^2} | {:^{}} | {:^{}} | {:^{}} |",
        "type",
        "size",
        "lowest", WIDTH ,
        "min"   , WIDTH ,
        "max"   , WIDTH
        ) << endl;    
    cout << std::string(TABLE_WIDTH, '=') << endl;    
    printTypeInfo<signed char>();
    printTypeInfo<unsigned char>();
    printTypeInfo<short>();
    printTypeInfo<short int>();
    printTypeInfo<signed short>();
    printTypeInfo<signed short int>();
    printTypeInfo<unsigned short>();
    printTypeInfo<unsigned short int>();
    printTypeInfo<int>();
    printTypeInfo<signed>();
    printTypeInfo<signed int>();
    printTypeInfo<unsigned>();
    printTypeInfo<unsigned int>();
    printTypeInfo<long>();
    printTypeInfo<long int>();
    printTypeInfo<signed long>();
    printTypeInfo<signed long int>();
    printTypeInfo<unsigned long>();
    printTypeInfo<unsigned long int>();
    printTypeInfo<long long>();
    printTypeInfo<long long int>();
    printTypeInfo<signed long long>();
    printTypeInfo<signed long long int>();
    printTypeInfo<unsigned long long>();
    printTypeInfo<unsigned long long int>();    
    cout << std::string(TABLE_WIDTH, '=') << endl;    
    printTypeInfo<bool>();
    cout << std::string(TABLE_WIDTH, '=') << endl;    
    printTypeInfo<signed char>();
    printTypeInfo<unsigned char>();
    // printTypeInfo<wchar_t>();
    // printTypeInfo<char16_t>();
    // printTypeInfo<char32_t>();
    cout << std::string(TABLE_WIDTH, '=') << endl;    
    printTypeInfo<float>();
    printTypeInfo<double>();
    printTypeInfo<long double>();     

    cout << std::string(TABLE_WIDTH, '=') << endl;    

    return 0;
}
