#include <iostream>
#include <vector>
#include <format>
#include <algorithm>
#define FMT_HEADER_ONLY
#include <fmt/ranges.h>


using namespace std;

vector<int> find_gap(int gap, int a, int b) {
    vector<bool> sieve(b, false);
    sieve[0] = sieve[1] = true;    
    int last = 2;
    for (int i = 2; i <= b; i++){
      	if(!sieve[i]) {
            // fmt::print("{} - {::d}\n",i ,sieve);
            if (last >= a && last <= b && i - last == gap)
                return {last, i};
            else{
                last = i;
                for(int temp = 2*i; temp < b; temp +=i)
                    sieve[temp] = true;
            }
        }
    }
    return {0, 0};
}

typedef vector< vector< vector<int> > >  test_t;

int main(void){
    test_t tests {
        {{2,3,50}   , {3,5}},
        {{2,5,7}    , {5,7}},
        {{4,130,200}, {163,167}},
        {{2,100,110}, {101, 103}},
        {{4,100,110}, {103,107}}
    };

    uint total_test =  tests.size();
    uint counter = 0;
    for (auto t : tests){
        counter += 1;        
        auto output = find_gap(t[0][0], t[0][1], t[0][2]);        
        fmt::print("{}/{} Test {:8}", 
                counter, 
                total_test,
                equal(t[1].begin(), t[1].end(), output.begin()) ? "OK" : "Failed"
                );
        fmt::print("gap {} ({},{}) = {}\n", t[0][0], t[0][1], t[0][2], output);
    }
    return 0;
}