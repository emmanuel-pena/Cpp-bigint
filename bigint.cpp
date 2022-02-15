//Emmanuel Pena
//epena6
//Kidus Michael
//kimichae

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"

bigint::bigint(long that) : uvalue(that), is_negative(that < 0)
{
    DEBUGF('~', this << " -> " << uvalue)
}

bigint::bigint(const ubigint& uvalue_, bool is_negative_) :
    uvalue(uvalue_), is_negative(is_negative_)
{

}

bigint::bigint(const ubigint&& uvalue_, bool is_negative_) :
    uvalue(std::move(uvalue_)), is_negative(is_negative_)
{

}

bigint::bigint(const string& that)
{
    is_negative = that.size() > 0 and that[0] == '_';
    uvalue = ubigint(that.substr(is_negative ? 1 : 0));
}

bigint bigint::operator+ () const
{
    return *this;
}

bigint bigint::operator- () const
{
    return { uvalue, not is_negative };
}

bigint bigint::operator+ (const bigint& that) const
{
    bigint result;

    if ( (this->is_negative == true) && (that.is_negative == true) )
    {
        result.uvalue = uvalue + that.uvalue;
        result.is_negative = this->is_negative;

        return result;
    }
    else if ((this->is_negative == false) 
            && (that.is_negative == false))
    {
        result.uvalue = uvalue + that.uvalue;
        result.is_negative = this->is_negative;

        return result;
    }
    else  
    {     

        if (this->uvalue > that.uvalue)
        {
           result.uvalue = this->uvalue - that.uvalue;   //this = larger
           result.is_negative = this->is_negative;

           return result;
        }
        else if (this->uvalue < that.uvalue)    //that = larger
        {
            result.uvalue = that.uvalue - this->uvalue;
            result.is_negative = that.is_negative;

            return result;
        }
        else if (this->uvalue == that.uvalue)
        {
            result.uvalue = that.uvalue - this->uvalue;
            result.is_negative = this->is_negative;  

            return result;
        }
    }
return result;
}

bigint bigint::operator- (const bigint& that) const
{
    bigint result;

    if ( this->is_negative != that.is_negative )
    {
        result.uvalue = this->uvalue + that.uvalue;
        result.is_negative = this->is_negative;

        return result;
    }
    else
    {
        
        if (this->uvalue > that.uvalue)
        {
           result.uvalue = this->uvalue - that.uvalue;
           result.is_negative = this->is_negative;

           return result;
        }
        else if (this->uvalue < that.uvalue)
        {
            result.uvalue = that.uvalue - this->uvalue;
            result.is_negative = !(this->is_negative);

            return result;
        }
        else if (this->uvalue == that.uvalue)
        {
            result.uvalue = that.uvalue - this->uvalue;
            result.is_negative = this->is_negative;

            return result;
        }

    }
return result;
}


bigint bigint::operator* (const bigint& that) const
{
    bigint result;
    result.uvalue = this->uvalue * that.uvalue;

    if (this->is_negative == true 
        && that.is_negative == true) // - * -
    {
        result.is_negative = false;
    }
    else if (this->is_negative == false 
            && that.is_negative == false) // + * +
    {
        result.is_negative = false;
    }
    else if (this->is_negative == true 
             && that.is_negative == false) // - * +
    {
        result.is_negative = true;
    }
    else if (this->is_negative == false 
             && that.is_negative == true) // + * -
    {
        result.is_negative = true;
    }
    else
    {
        result.is_negative = true; // just in case
    }
    return result;
}

bigint bigint::operator/ (const bigint& that) const
{
    bigint result;
    result.uvalue = this->uvalue / that.uvalue;

    if (this->is_negative == true 
            && that.is_negative == true)  //a - divided by a -
    {
        result.is_negative = false;
    }
    else if (this->is_negative == false 
            && that.is_negative == false)  //a + divided by a +
    {
        result.is_negative = false;
    }
    else if (this->is_negative == true 
             && that.is_negative == false) //  - / +
    {
        result.is_negative = true;
    }
    else if (this->is_negative == false 
             && that.is_negative == true) // + / -
    {
        result.is_negative = true;
    }
    else
    {
        result.is_negative = true; // just in case
    }

    return result;
}

bigint bigint::operator% (const bigint& that) const
{
   bigint result;
   result.uvalue = this->uvalue % that.uvalue;

   if (this->is_negative == true
            && that.is_negative == true)  //a - divided by a -
    {
        result.is_negative = false;
    }
    else if (this->is_negative == false
            && that.is_negative == false)  //a + divided by a +
    {
        result.is_negative = false;
    }
    else if (this->is_negative == true
             && that.is_negative == false) //  - / +
    {
        result.is_negative = true;
    }
    else if (this->is_negative == false
             && that.is_negative == true) // + / -
    {
        result.is_negative = true;
    }
    else
    {
        result.is_negative = true; // just in case
    }

    return result;

}

bool bigint::operator== (const bigint& that) const
{
    return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const
{
    if (is_negative != that.is_negative) return is_negative;
    return is_negative ? uvalue > that.uvalue
        : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that)
{
    return out << (that.is_negative ? "-" : "" ) << that.uvalue;
}

