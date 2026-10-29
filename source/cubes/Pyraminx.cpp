#include <Calculation.h>
#include <format>
#include <algorithm>
//#include <cmath>
#include <string>

#include <boost/multiprecision/gmp.hpp>

namespace bst = boost::multiprecision;

/*cpp_int Factorial24;
cpp_int Factorial12;
cpp_int Fact7X3to6;*/

//5 × 2^(2n²−3n−1) × 3^(n²/3+3n−16/3) × 1925^(n²/3−n−1/3) * 81, Source: https://speedcubing.org/blogs/news/number-of-combinations-calculator
inline mpz_class Pow2Calculation, Pow3Calculation, Pow1925Calculation;

using namespace std::string_literals;

static cpp_int factorial(unsigned int n) {
    cpp_int result = 1;
    for(unsigned int i = 2; i <= n; ++i) result *= i;
    return result;
}

static cpp_int integerPower(cpp_int base, unsigned long exponent) {
    cpp_int result = 1;
    while(exponent > 0) {
        if(exponent & 1UL) result *= base;
        exponent >>= 1UL;
        if(exponent > 0) base *= base;
    }
    return result;
}
static bst::mpz_int integerPower_mpz(bst::mpz_int base_mpz, bst::mpz_int exponent) {
    bst::mpz_int result = 1;
    while(exponent > 0) {
        if(bst::bit_test(exponent, 0)) result *= base_mpz;
        exponent >>= 1;
        if(exponent > 0) base_mpz *= base_mpz;
    }
    return result;
}

Pyraminx::Pyraminx() {

}
cpp_int Pyraminx::CalculateBoost(int i) {return 0;}
/*
Pyraminx::Calculation() {
    Factorial24 = factorial(24);
    Factorial12 = factorial(12);
    Fact7X3to6 = factorial(7) * 729;
}
*/
mpz_class Power(mpz_t i, int j) {
    mpz_class result;
    mpz_pow_ui(result.get_mpz_t(), i, j);
    return result;
}
mpz_class Pyraminx::Calculate(int i) {
    if(i == 0) return 0_mpz;
    if(i == 1) return 1_mpz;

    bst::mpz_int Int = i;

    bst::mpz_int Polynomial1 = 2*bst::pow(Int, 2) - 3*Int - 1;
    bst::mpz_int Polynomial2 = (bst::pow(Int, 2) + 9*Int - 16) / 3; //Multiplying and Dividing by 3 Avoids Int Truncation
    bst::mpz_int Polynomial3 = (bst::pow(Int, 2) - 3*Int - 1) / 3;

    bst::mpz_int Term1 = integerPower_mpz(2, Polynomial1);
    bst::mpz_int Term2 = integerPower_mpz(3, Polynomial2);
    bst::mpz_int Term3 = integerPower_mpz(1925, Polynomial3);
    
    bst::mpz_int FinalNumber = 5 * Term1 * Term2 * Term3 * 81;
    /*mpz_pow(Pow2Calculation.get_mpz_t(), 2_mpz, Int);
    mpz_ui_pow_ui()

    mpz_class Base = 24_mpz * (1<<10) * Factorial12;
    
    mpz_class OddComponent;
    mpz_pow_ui(OddComponent.get_mpz_t(), Base.get_mpz_t(), i%2);

    mpz_class FlooredComponent;
    mpz_pow_ui(FlooredComponent.get_mpz_t(), Factorial24.get_mpz_t(), floor((i-2)/2));

    mpz_class FinalComponent;
    mpz_class FinalBase;
    mpz_class Fact4to6;
    mpz_pow_ui(Fact4to6.get_mpz_t(), ((mpz_class)factorial(4_mpz)).get_mpz_t(), 6);
    FinalBase = Factorial24 / Fact4to6;
    mpz_pow_ui(FinalComponent.get_mpz_t(), FinalBase.get_mpz_t(), floor(pow((i-2)/2.0, 2)));

    mpz_class FinalNumber = Fact7X3to6 * OddComponent * FlooredComponent * FinalComponent;*/
    return FinalNumber.convert_to<mpz_class>();
}
/*
cpp_int Pyraminx::Calculate(int i) {
    if(i == 0) return 0;
    if(i == 1) return 1;
    cpp_int Base = 24 * (1<<10) * Factorial12;
    
    cpp_int OddComponent = integerPower(Base, static_cast<unsigned long>(i % 2));

    cpp_int FlooredComponent = integerPower(
        Factorial24,
        static_cast<unsigned long>(floor((i-2)/2))
    );

    cpp_int FinalBase;
    cpp_int Fact4to6 = integerPower(factorial(4), 6);
    FinalBase = Factorial24 / Fact4to6;
    cpp_int FinalComponent = integerPower(
        FinalBase,
        static_cast<unsigned long>(floor(pow((i-2)/2.0, 2)))
    );

    cpp_int FinalNumber = Fact7X3to6 * OddComponent * FlooredComponent * FinalComponent;
    return FinalNumber;
}
*/


std::string Pyraminx::returnString10(mpz_class i) {
    return i.get_str(10);
}
std::string Pyraminx::returnScientific(mpz_class i, int precision) {
    if(i == 0_mpz) return "0e+0";
    if(i == 1_mpz) return "1e+0";
    mpf_class f(i, (precision+10) * 4);
    mp_exp_t exp;

    std::string str = f.get_str(exp, 10, precision+1);

    bool negative = (str[0] == '-');
    if(negative) str = str.substr(1);
    std::string result = (negative ? "-" : "");
    result += str[0];
    result += '.';
    if(str.length() > 1) {
        result += str.substr(1, precision);
    } 
    result += "e+" + std::to_string(exp-1);
    return result;
}


std::string Pyraminx::returnString10(const cpp_int& i) {
    return i.str();
}
std::string Pyraminx::returnScientific(const cpp_int& i, int size, int precision) {
    if(i == 0) return "0E0";
    if(i == 1) return "1E0";

    using namespace boost::multiprecision;
    using cpp_float = number<backends::cpp_bin_float<PRECISION_MAX>>;

    if(precision > PRECISION_MAX) {
        std::cerr<<"[ERROR] Precision Inputted Exceeds Maximum Value of: "<<PRECISION_MAX<<std::endl;
    }

    int digits = returnNumDigits(size);
    int exp = digits - 1;
    size_t msb_value = msb(i);

    constexpr double conversion = 3.32192809489;
    size_t bit_precision = precision * conversion + 64;
    cpp_int truncated;
    int shift_amount = 0;
    if(msb_value > bit_precision) {
        shift_amount = msb_value - bit_precision;
        truncated = i >> shift_amount;
    } else {
        truncated = i;
    }
    cpp_float converted = truncated.convert_to<cpp_float>();
    cpp_float scaled = ldexp(converted, shift_amount);
    std::ostringstream oss;
    oss<<scaled<<std::endl;
    return oss.str();
}


int Pyraminx::returnNumDigits(int i) {
    if(i == 0) return 0;
    if(i == 1) return 1;
    double a = 6.56515806476;
    double b = 13.0708481624;
    double c = 23.7927056702;
    double d = 15.5114382199;

    return floor(a + (i%2)*b + std::floor((i-2)/2)*c + std::floor(pow((i-2)/2.0,2))*d) + 1;
}
int Pyraminx::returnTrailingZeros(int i) {
    if(i <= 1) return 0;
    return std::pow(i-((i%2) + 1), 2) + 2*(i%2);
}
