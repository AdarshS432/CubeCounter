#include <Calculation.h>
#include <format>
#include <algorithm>
#include <cmath>
#include <string>

cpp_int Factorial24;
cpp_int Factorial12;
cpp_int Fact7X3to6;

constexpr uint PRECISION_MAX = 64;

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

Calculation::Calculation() {
    Factorial24 = factorial(24);
    Factorial12 = factorial(12);
    Fact7X3to6 = factorial(7) * 729;
}
cpp_int Calculation::Calculate(int i) {
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

std::string Calculation::returnString10(const cpp_int& i) {
    return i.str();
}
std::string Calculation::returnScientific(const cpp_int& i, int size, int precision) {
    if(i == 1) return "1E0";

    using namespace boost::multiprecision;
    using cpp_float = number<backends::cpp_bin_float<PRECISION_MAX>>;

    if(precision > PRECISION_MAX) {
        std::cerr<<"[ERROR] Precision Inputted Exceeds Maximum Value of: "<<PRECISION_MAX<<std::endl;
    }
    /*mpf_class f(i, (precision+10) * 4);
    mp_exp_t exp;

    std::string str = f.str(exp, 10, precision+1);*/
    int digits = returnNumDigits(size);
    int exp = digits - 1;
    auto leading_calc = i.convert_to<cpp_float>() / boost::multiprecision::pow(cpp_float(10), exp);

    cpp_float leading(leading_calc);
    std::string leading_trimmed = leading.str(precision, std::ios_base::fixed);

    std::ostringstream oss;
    oss<<leading_trimmed<<"E"<<exp;
    return oss.str();

    /*bool negative = (i_str[0] == '-');
    if(negative) i_str = i_str.substr(1);
    std::string result = (negative ? "-" : "");
    result += i_str[0];
    result += '.';
    if(i_str.length() > 1) {
        result += i_str.substr(1, precision);
    } 
    double exp = boost::multiprecision::log10(i);
    result += "E" + std::to_string(exp-1);
    return result;
    return i_str;*/
}
int Calculation::returnNumDigits(int i) {
    if(i == 1) return 1;
    double a = 6.56515806476;
    double b = 13.0708481624;
    double c = 23.7927056702;
    double d = 15.5114382199;

    return floor(a + (i%2)*b + std::floor((i-2)/2)*c + std::floor(pow((i-2)/2.0,2))*d) + 1;
}
int Calculation::returnTrailingZeros(int i) {
    if(i == 1) return 0;
    return std::pow(i-((i%2) + 1), 2) + 2*(i%2);
}
