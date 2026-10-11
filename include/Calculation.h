#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include <gmp.h>
#include <gmpxx.h>

#include <string>

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float;

class Calculation {
    public:
        int IDX;
        Calculation();
        cpp_int CalculateBoost(int i);
        mpz_class Calculate(int i);

        std::string returnString10(const cpp_int& i);
        std::string returnScientific(const cpp_int& i, int size, int precision);

        std::string returnString10(mpz_class i);
        std::string returnScientific(mpz_class i, int precision);

        int returnTrailingZeros(int i);
        int returnNumDigits(int i);
};