#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include <gmp.h>
#include <gmpxx.h>

#include <string>

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float;

constexpr uint PRECISION_MAX = 64;

class Calculation {
    public:
        int IDX;
        ~Calculation() = default;
        
        virtual cpp_int CalculateBoost(int i) = 0;
        virtual mpz_class Calculate(int i) = 0;

        virtual std::string returnString10(const cpp_int& i) = 0;
        virtual std::string returnScientific(const cpp_int& i, int size, int precision) = 0;

        virtual std::string returnString10(mpz_class i) = 0;
        virtual std::string returnScientific(mpz_class i, int precision) = 0;

        virtual int returnTrailingZeros(int i) = 0;
        virtual int returnNumDigits(int i) = 0;
};
class RubiksCube : public Calculation {
    public:
        RubiksCube();
        ~RubiksCube() = default;

        cpp_int CalculateBoost(int i) override;
        mpz_class Calculate(int i) override;

        std::string returnString10(const cpp_int& i) override;
        std::string returnScientific(const cpp_int& i, int size, int precision) override;

        std::string returnString10(mpz_class i) override;
        std::string returnScientific(mpz_class i, int precision) override;

        int returnTrailingZeros(int i) override;
        int returnNumDigits(int i) override;
};
class Pyraminx : public Calculation {
    public: 
        Pyraminx();
        ~Pyraminx() = default;

        cpp_int CalculateBoost(int i) override;
        mpz_class Calculate(int i) override;

        std::string returnString10(const cpp_int& i) override;
        std::string returnScientific(const cpp_int& i, int size, int precision) override;

        std::string returnString10(mpz_class i) override;
        std::string returnScientific(mpz_class i, int precision) override;

        int returnTrailingZeros(int i) override;
        int returnNumDigits(int i) override;
};
class DodecagonMinx : public Calculation {
    public: 
        DodecagonMinx();
        ~DodecagonMinx() = default;

        cpp_int CalculateBoost(int i) override;
        mpz_class Calculate(int i) override;

        std::string returnString10(const cpp_int& i) override;
        std::string returnScientific(const cpp_int& i, int size, int precision) override;

        std::string returnString10(mpz_class i) override;
        std::string returnScientific(mpz_class i, int precision) override;

        int returnTrailingZeros(int i) override;
        int returnNumDigits(int i) override;
};