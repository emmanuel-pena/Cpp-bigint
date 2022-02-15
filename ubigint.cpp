//Emmanuel Pena
//epena6
//Kidus Michael
//kimichae

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;
#include <vector>
#include <cmath>
#include <string>

#include "debug.h"
#include "relops.h"
#include "ubigint.h"

ubigint::ubigint(unsigned long that)
{
    string val = to_string(that);

    for (char digit : val)
    {
        auto it = ubig_value.begin();
        ubig_value.insert(it, digit);
        if (isdigit(digit) == 0)
        {
            throw invalid_argument("ubigint::ubigint(" + val + ")");
        }
    }

    while (ubig_value.size() > 0 && ubig_value.back() == '0')
    {
        ubig_value.pop_back();
    }

}

ubigint::ubigint(const string& that)
{
    for (char digit : that)
    {
        auto it = ubig_value.begin();
        ubig_value.insert(it, digit);
        if (isdigit(digit) == 0)
        {
            throw invalid_argument("ubigint::ubigint(" + that + ")");
        }
    }

    while (ubig_value.size() > 0 && ubig_value.back() == '0')
    {
        ubig_value.pop_back();
    }
}

ubigint ubigint::operator+ (const ubigint& that) const {
    ubigint result;

    long unsigned int sum, mus, sv;
    long unsigned int carry = 0;
    long unsigned int i = 0;  // index

    // Check which value is longer
    if (ubig_value.size() > that.ubig_value.size()) {
        sv = that.ubig_value.size();
    }
    else if (ubig_value.size() < that.ubig_value.size()) {
        sv = ubig_value.size();
    }
    else {
        sv = ubig_value.size();
    }

    // Repeat add as many times as smaller value length
    while (i < sv) {
        long unsigned int a = ubig_value[i] - 48;
        long unsigned int b = that.ubig_value[i] - 48;
        sum = a + b + carry;

        // Check Carry
        if (sum >= 10) {
            carry = 1;
        }
        else {
            carry = 0;
        }

        mus = sum % 10;
        unsigned char summ = mus + '0';
        result.ubig_value.push_back(summ);
         
        i++;
    }

    // Only executes if 'ubig_value' is larger
    while (i < ubig_value.size()) {
        sum = (ubig_value[i] - 48) + carry;

        // Check carry
        if (sum >= 10) {
            carry = 1;
        }
        else {
            carry = 0;
        }

        mus = sum % 10;

        unsigned char summ = mus + '0';
        result.ubig_value.push_back(summ);

        i++;
    }

    // ONly executes if 'that.ubig_value' is longer
    while (i < that.ubig_value.size()) {
        sum = (that.ubig_value[i] - 48) + carry;

        // Check carry
        if (sum >= 10) {
            carry = 1;
        }
        else {
            carry = 0;
        }

        mus = sum % 10;

        unsigned char summ = mus + '0';
        result.ubig_value.push_back(summ);

        i++;
    }

    // Remainder Carry
    if (carry == 1) {
        unsigned char carri = carry + '0';
        result.ubig_value.push_back(carri);
    }

    return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
    ubigint result;

    long unsigned int sv;
    long int rem = 0;
    long int borrow = 0;
    long unsigned int mer;
    long unsigned int i = 0;

    // Compare length of this.ubig and that.ubig
    if (ubig_value.size() > that.ubig_value.size()) {
        sv = that.ubig_value.size();
    }
    else if (ubig_value.size() < that.ubig_value.size()) {
        sv = ubig_value.size();
    }
    // ubig_value.size() == that.ubig_value.size()
    else {
        sv = ubig_value.size();
    }

    // Subtract that.ubig from ubig
    while (i < sv) {
        long int a = ubig_value[i] - 48;
        long int b = that.ubig_value[i] - 48;
        rem = a - b + borrow;

        if (rem < 0) {
            borrow = -1;
            mer = rem + 10;
        }
        else {
            borrow = 0;
            mer = rem;
        }

        unsigned char remm = mer + '0';
        result.ubig_value.push_back(remm);

        i++;
    }

    // Only execute if ubig is the longer bigint
    while (i < ubig_value.size()) {
        long int a = ubig_value[i] - 48;
        rem = a + borrow;

        if (rem < 0) {
            borrow = -1;
            mer = rem + 10;
        }
        else {
            borrow = 0;
            mer = rem;
        }

        unsigned char remm = mer + '0';
        result.ubig_value.push_back(remm);

        i++;
    }

    // Only execute if that.ubig is the longer bigint
    while (i < that.ubig_value.size()) {
        long int b = that.ubig_value[i] - 48;
        rem = b + borrow;

        if (rem < 0) {
            borrow = -1;
            mer = rem + 10;
        }
        else {
            borrow = 0;
            mer = rem;
        }

        unsigned char remm = mer + '0';
        result.ubig_value.push_back(remm);

        i++;
    }

    // Remove leading 0s
    while (result.ubig_value.size() > 0 
           && result.ubig_value.back() == '0') {
        result.ubig_value.pop_back();
    }

    return result;
}

ubigint ubigint::operator* (const ubigint& that) const
{
    ubigint bigintt;

    if((this->ubig_value.size() == 0)) 
    {
        bigintt.ubig_value.clear();
        return bigintt;
    }

    if ( (that.ubig_value.size() == 0)) 
    {
        bigintt.ubig_value.clear();
        return bigintt;
    }

 ubigvalue_t v(this->ubig_value.size()+that.ubig_value.size(), '0');
 bigintt.ubig_value = v;

   long unsigned int c;
    long unsigned int d;

    //asgn1 pdf algorithm for mul
    for (long unsigned int i = 0; i < this->ubig_value.size(); i++)
    {
        c = 0;

        for (long unsigned int j = 0; j < that.ubig_value.size(); j++)
        {
            d = (bigintt.ubig_value[i + j] - 48)
                + ((this->ubig_value[i] - 48) 
                * (that.ubig_value[j] - 48)) 
                + c;

            bigintt.ubig_value[i + j] = ((d % 10) + 48);
            c = floor(d / 10);
        }

        bigintt.ubig_value[i + that.ubig_value.size()] = c + 48;
    }

    //leading 0s??
    while(bigintt.ubig_value.size()>0 
          && bigintt.ubig_value.back()=='0')
    {
        bigintt.ubig_value.pop_back();
    }

 return bigintt;
}

void ubigint::multiply_by_2()
{
    ubigint two(2);
    ubigint temp(0);
    temp = (*this) * two;
    (*this) = std::move(temp);
}

void ubigint::divide_by_2()
{
    ubigint five(5);
    ubigint temp(0);
    temp = (*this) * five;
    temp.ubig_value.erase(temp.ubig_value.cbegin());
    (*this) = std::move(temp);
}

struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide(const ubigint& dividend, const ubigint& divisor_) {
    // NOTE: udivide is a non-member function.
    ubigint divisor{ divisor_ };
    ubigint zero{ 0 };
    if (divisor == zero) throw domain_error("udivide by zero");
    ubigint power_of_2{ 1 };
    ubigint quotient{ 0 };
    ubigint remainder{ dividend }; // left operand, dividend
    while (divisor < remainder) {
        divisor.multiply_by_2();
        power_of_2.multiply_by_2();
    }
    while (power_of_2 > zero) {
        if (divisor <= remainder) {
            remainder = remainder - divisor;
            quotient = quotient + power_of_2;
        }
        divisor.divide_by_2();
        power_of_2.divide_by_2();
    }
    DEBUGF('/', "quotient = " << quotient);
    DEBUGF('/', "remainder = " << remainder);
    return { quotient = quotient, remainder = remainder };
}

ubigint ubigint::operator/ (const ubigint& that) const
{
    return udivide(*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const
{
    return udivide(*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const
{
    bool equals = false;
    
    int Asize = this->ubig_value.size();
    int Bsize = that.ubig_value.size();
    int a;
    int b;


    if (Asize == Bsize)
    {
        equals = true;
    }

    if (equals == true)
    {

        for (int i = 0; i <= (Asize-1); ++i)
        {
             a = this->ubig_value[i] - 48;
             b = that.ubig_value[i] - 48;

            if (a != b)
            {
                equals = false;
                return equals;
            }
        }
    }
    
    return equals;
}

bool ubigint::operator< (const ubigint& that) const
{

    if (this->ubig_value.size() < that.ubig_value.size())
    {
        return true;
    }
    else if (this->ubig_value.size() > that.ubig_value.size())
    {
        return false;
    }
    else //same size so compare contents
    {
        int a;
        int b;

        for (int i = (this->ubig_value.size() - 1); i >= 0; --i)
        {
             a = this->ubig_value[i] - 48;
             b = that.ubig_value[i] - 48;

            if ( a < b )
            {
                return true;
            }
            else if ( a > b)
            {
                return false;
            }
            else
            {
             //places are equal, so continue loop
            }
        }
    }

return false; //no difference
}

ostream& operator<< (ostream& out, const ubigint& that)
{

    auto it = that.ubig_value.crbegin();
    int i = 1;
    while (it != that.ubig_value.crend())
    {
        if (i == 70)
        {
            out << "\\\n";
            i = 1; 
        }

        out << *it;

        ++it; 
        ++i;
    }

    return out;
}

//                                               sources
//https://www2.ucsc.edu/courses
///cse111-wm/:/Assignments/asg1-dc-bigint/asg1-dc-bigint.pdf
//the pseudocode for mult



