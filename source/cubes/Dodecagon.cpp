#include <Calculation.h>
#include <format>
#include <algorithm>
//#include <cmath>
#include <string>


namespace bst = boost::multiprecision;

/*cpp_int Factorial24;
cpp_int Factorial12;
cpp_int Fact7X3to6;*/

//Odd: 30! × 20! × (60!)^(m²−1) × 2^(28−m) × 3¹⁹ ÷ (5!)^(12m²−12m), L = 2m + 1
//Even: ((19! / 2) × 3¹⁸) × (60! / 2)^(m−1) × (60! / (5!)¹²)^((m−1)²), L = 2m
//Source: https://speedcubing.org/blogs/news/number-of-combinations-calculator
using namespace std::string_literals;

static mpz_class factorial(unsigned int n) {
    mpz_class result = 1;
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

    mpz_class m = (i % 2 == 0) ? (i / 2) : ((i - 1) / 2);

    mpz_class m2;
    mpz_pow_ui(m2.get_mpz_t(), m.get_mpz_t(), 2);

    mpz_class m2_1;
    mpz_sub_ui(m2_1.get_mpz_t(), m2.get_mpz_t(), 1);

    mpz_class fact60;
    mpz_fac_ui(fact60.get_mpz_t(), 60);

    if(i % 2 == 1) {
        mpz_class fact60_term;
        mpz_pow_ui(fact60_term.get_mpz_t(), fact60.get_mpz_t(), m2.get_ui() - 1);

        mpz_class fact_product;
        fact_product = factorial(30) * factorial(20) * fact60_term; //MAIN

        mpz_class exponential2;
        mpz_ui_pow_ui(exponential2.get_mpz_t(), 2, (m <= 28) ? (28-m.get_ui()) : (m.get_ui()-28)); //MAIN

        mpz_class exponential3;
        mpz_ui_pow_ui(exponential3.get_mpz_t(), 3, 19); //MAIN

        mpz_class division, exp5;
        division = factorial(5);
        mpz_mul_ui(exp5.get_mpz_t(), m2.get_mpz_t(), 12);//12m^2 - 12m
        mpz_submul_ui(exp5.get_mpz_t(), m.get_mpz_t(), 12);
        mpz_pow_ui(division.get_mpz_t(), division.get_mpz_t(), exp5.get_ui()); //MAIN

        mpz_class final_result;
        if(m.get_ui() <= 28) {
            final_result = fact_product * exponential2 * exponential3 / division; //MAIN
        } else {
            final_result = fact_product / exponential2 * exponential3 / division; //MAIN
        }

        return final_result;
    } else {
        mpz_class fact19;
        mpz_fac_ui(fact19.get_mpz_t(), 19);

        mpz_class fact19_div2;
        mpz_divexact_ui(fact19_div2.get_mpz_t(), fact19.get_mpz_t(), 2);

        mpz_class exponential3_18;
        mpz_ui_pow_ui(exponential3_18.get_mpz_t(), 3, 18);

        mpz_class term1; //MAIN
        mpz_mul(term1.get_mpz_t(), fact19_div2.get_mpz_t(), exponential3_18.get_mpz_t());

        mpz_class fact60_div2;
        mpz_divexact_ui(fact60_div2.get_mpz_t(), fact60.get_mpz_t(), 2);

        mpz_class term2; //MAIN
        mpz_pow_ui(term2.get_mpz_t(), fact60_div2.get_mpz_t(), m.get_ui() - 1);

        mpz_class fact60_div5_12;
        mpz_class fact5_12;
        mpz_fac_ui(fact5_12.get_mpz_t(), 5);
        mpz_pow_ui(fact5_12.get_mpz_t(), fact5_12.get_mpz_t(), 12);
        mpz_divexact(fact60_div5_12.get_mpz_t(), fact60.get_mpz_t(), fact5_12.get_mpz_t());

        mpz_class m_1_2;
        mpz_ui_pow_ui(m_1_2.get_mpz_t(), m.get_ui()-1, 2);

        mpz_class term3; //MAIN
        mpz_pow_ui(term3.get_mpz_t(), fact60_div5_12.get_mpz_t(), m_1_2.get_ui());

        mpz_class final_result;
        final_result = term1 * term2 * term3; //MAIN

        return final_result;
    }
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
    if(i % 2 == 1) {
        int m = (i-1)/2;

        double a = 59.8750885315;
        double b = 81.9201748494;
        double c = 0.301029995664;
        double d = 2.07918124605;

        return floor(a + b *(m*m - 1) + c*(28-m) - d*(12*m*m - 12*m)) + 1;
    } else {
        int m = i/2;

        double a = 25.3722472105;
        double b = 81.6191448537;
        double c = 56.9699998968;

        return floor(a + b*(m - 1) + c*pow((m - 1), 2)) + 1;
    }
}

int DodecagonMinx::returnTrailingZeros(int i) {
    if(i <= 1) return 0;
    if(i % 2 == 1) {
        return static_cast<int>(4*(i*i) - 2*i - 19);
    } else {
        return static_cast<int>(0.5 * (i*i) + 5*i - 9);
    }

}
