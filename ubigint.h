//Emmanuel Pena
//epena6
//Kidus Michael
//kimichae

#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;
#include <vector>
#include <cmath>

#include "debug.h"

class ubigint {
    friend ostream& operator<< (ostream&, const ubigint&);
private:
    using ubigvalue_t = vector<uint8_t>;
    ubigvalue_t ubig_value;

public:
    void multiply_by_2();
    void divide_by_2();

    ubigint() = default; // Need default ctor as well.
    ubigint(unsigned long);
    ubigint(const string&);

    ubigint operator+ (const ubigint&) const;
    ubigint operator- (const ubigint&) const;
    ubigint operator* (const ubigint&) const;
    ubigint operator/ (const ubigint&) const;
    ubigint operator% (const ubigint&) const;

    bool operator== (const ubigint&) const;
    bool operator<  (const ubigint&) const;
};

#endif

