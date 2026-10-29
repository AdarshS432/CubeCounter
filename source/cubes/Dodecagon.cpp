#include <Calculation.h>
#include <format>
#include <algorithm>
#include <cmath>
#include <string>

/*cpp_int Factorial24;
cpp_int Factorial12;
cpp_int Fact7X3to6;*/
inline mpz_class Factorial24, Factorial12, Fact7X3to6;

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
DodecagonMinx::DodecagonMinx() {
    Factorial24 = factorial(24_mpz);
    Factorial12 = factorial(12_mpz);
    Fact7X3to6 = factorial(7_mpz) * (int)pow(3, 6); 
}
cpp_int DodecagonMinx::CalculateBoost(int i) {return 0;}
/*
DodecagonMinx::Calculation() {
    Factorial24 = factorial(24);
    Factorial12 = factorial(12);
    Fact7X3to6 = factorial(7) * 729;
}
*/
mpz_class DodecagonMinx::Calculate(int i) {
    if(i == 0) return 0_mpz;
    if(i == 1) return 1_mpz;
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

    mpz_class FinalNumber = Fact7X3to6 * OddComponent * FlooredComponent * FinalComponent;
    return FinalNumber;
}
/*
cpp_int DodecagonMinx::Calculate(int i) {
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


std::string DodecagonMinx::returnString10(mpz_class i) {
    return i.get_str(10);
}
std::string DodecagonMinx::returnScientific(mpz_class i, int precision) {
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


std::string DodecagonMinx::returnString10(const cpp_int& i) {
    return i.str();
}
std::string DodecagonMinx::returnScientific(const cpp_int& i, int size, int precision) {
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


int DodecagonMinx::returnNumDigits(int i) {
    if(i == 0) return 0;
    if(i == 1) return 1;
    double a = 6.56515806476;
    double b = 13.0708481624;
    double c = 23.7927056702;
    double d = 15.5114382199;

    return floor(a + (i%2)*b + std::floor((i-2)/2)*c + std::floor(pow((i-2)/2.0,2))*d) + 1;
}
int DodecagonMinx::returnTrailingZeros(int i) {
    if(i <= 1) return 0;
    return std::pow(i-((i%2) + 1), 2) + 2*(i%2);
}
