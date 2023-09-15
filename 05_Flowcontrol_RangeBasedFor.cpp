#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <string_view>

struct P
{
    int first;
    char second;
    friend std::ostream& operator<<(std::ostream& os, const P& p)
    {
        return os << '{' << p.first << ",'" << p.second << "'}";
    }
};

auto print = [](std::string_view name, auto const& v)
{
    std::cout << name << ": ";
    for (auto n = v.size(); const auto& e : v)
        std::cout << e << (--n ? ", " : "\n");
};


int main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    // std::vector<int>::iterator ptr = v.begin();
 
    std::cout <<  "access by const reference :";
    for (const int& i : v) // access by const reference
        std::cout << i << ' ';
    std::cout << '\n';

    std::cout <<  "using iterator :";
    for (auto ptr = v.begin()+2; ptr != v.end()-1; ptr++) // Displaying vector elements using begin() and end()
        std::cout << *ptr << ' ';
    std::cout << '\n';

    std::cout <<  "access by value :";
    for (auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
 
    std::cout <<  "access by forwarding :";
    for (auto&& i : v) // access by forwarding reference, the type of i is int&
        std::cout << i << ' ';
    std::cout << '\n';
 
    const auto& cv = v;
    std::cout <<  "access by f-d reference :";
    for (auto&& i : cv) // access by f-d reference, the type of i is const int&
        std::cout << i << ' ';
    std::cout << '\n';
 
    std::cout <<  "braced-init-list initializer :";
    for (int n : {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::cout <<  "array initializer :";
    int a[] = {0, 1, 2, 3, 4, 5};
    for (int n : a) // the initializer may be an array
        std::cout << n << ' ';
    std::cout << '\n';
 
    for ([[maybe_unused]] int n : a)  // maybe_unused attribute suppresses warnings on unused entities.
        std::cout << 1 << ' '; // the loop variable need not be used
    std::cout << '\n';
 
    for (auto n = v.size(); auto i : v) // the init-statement (C++20)
        std::cout << --n + i << ' ';
    std::cout << '\n';
 
    for (typedef decltype(v)::value_type elem_t; elem_t i : v)
    // typedef declaration as init-statement (C++20)
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (using elem_t = decltype(v)::value_type; elem_t i : v)
    // alias declaration as init-statement (C++23)
        std::cout << i << ' ';
    std::cout << '\n';


    // FOR EACH
    // =================================================
    // #include <algorithm>
    std::cout << "\nfor each:\n";

    std::vector<int> v2 {3, -4, 2, -8, 15, 267};

    auto print_int = [](const int& n) { std::cout << n << ' '; };

    std::cout << "before:\t";
    std::for_each(v2.cbegin(), v2.cend(), print_int);
    std::cout << '\n';

    // increment elements in-place
    std::for_each(v2.begin(), v2.end(), [](int &n) { n++; });

    std::cout << "after:\t";
    std::for_each(v2.cbegin(), v2.cend(), print_int);
    std::cout << '\n';

    struct Sum
    {
        void operator()(int n) { sum += n; }
        int sum {0};
    };

    // invoke Sum::operator() for each element
    Sum s1 = std::for_each(v2.cbegin(), v2.cend(), Sum());
    std::cout << "sum:\t" << s1.sum << '\n';

    // FOR EACH N
    // =================================================
    // #include <algorithm>

    std::cout << "\nfor each n:\n";
    std::array a2 {1, 2, 3, 4, 5};
    print("a", a2);
    // Negate first three numbers:
    std::ranges::for_each_n(a2.begin(), 3, [](auto& n) { n *= -1; });
    print("a", a2);

    std::array s { P{1,'a'}, P{2, 'b'}, P{3, 'c'}, P{4, 'd'} };
    print("s", s);
    // Negate data members 'P::first' using projection:
    std::ranges::for_each_n(s.begin(), 2, [](auto& x) { x *= -1; }, &P::first);
    print("s", s);
    // Capitalize data members 'P::second' using projection:
    std::ranges::for_each_n(s.begin(), 3, [](auto& c) { c -= 'a'-'A'; }, &P::second);
    print("s", s);
}