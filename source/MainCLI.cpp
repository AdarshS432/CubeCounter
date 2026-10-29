#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <Calculation.h>

int LAYERS = 3;
int PRECISION = 4;
bool PRINTFULLNUMBER = false;
bool WRITE_TO_FILE = false;

bool APPEND = false;
bool OVERWRITE = false; 
const char* FILE_PATH;

enum class CubeType {
    _RubiksCube = 0,
    _Pyraminx = 1,
    _DodecagonMinx = 2
};
CubeType selected_cube;

//static cpp_int number;
static mpz_class number;
static std::string numcombos;
static std::string numcombos_scientific;
static std::string numdigits;
static std::string numtrailzeros;


int main(int argc, char* argv[]) {
    for(int i=0; i<argc; i++) {
        std::string arg = argv[i];
        if(arg == "--cube") {
            if(i == argc - 1) {
                std::cerr<<"[ERROR] No Cube Type Provided"<<std::endl;
                return -1;
            }
            std::string arg1 = argv[i+1];
            if(arg1 == "Rubik" || arg1 == "R") {
                selected_cube = CubeType::_RubiksCube;
            } else if(arg1 == "Pyraminx" || arg1 == "P") {
                selected_cube = CubeType::_Pyraminx;
            } else if(arg1 == "Minx" || arg1 == "Dodecagon" || arg1 == "M" || arg1 == "D") {
                selected_cube = CubeType::_DodecagonMinx;
            } else {
                std::cerr<<"[ERROR] Invalid Cube Type Provided"<<std::endl;
                return -1;
            }
        }
        if(arg == "--layercount") {
            if(i == argc-1) {
                std::cerr<<"[ERROR] No Layer Count Provided"<<std::endl;
                return -1;
            }
            LAYERS = std::stoi(argv[i+1]);
        }
        if(arg == "--printfullnumber") {
            PRINTFULLNUMBER = true;
        }
        if(arg == "--precision") {
            if(i == argc-1) {
                std::cerr<<"[ERROR] No Precision Provided"<<std::endl;
                return -1;
            }
            PRECISION = std::stoi(argv[i+1]);
        }
        if(arg == "--file") {
            if(i == argc-1) {
                std::cerr<<"[ERROR] No File Path Provided"<<std::endl;
                return -1;
            }
            WRITE_TO_FILE = true;
            FILE_PATH = argv[i+1];
        }
        if(arg == "--append") {
            APPEND = true;
        }
        if(arg == "--overwrite") {
            OVERWRITE = true;
        }
    }
    if((APPEND || OVERWRITE) && !WRITE_TO_FILE) {
        std::cerr<<"[ERROR] Append/Overwrite Selected Without Write To File Enabled"<<std::endl;
        return -1;
    }
    if(!APPEND && !OVERWRITE && WRITE_TO_FILE) {
        std::cerr<<"[ERROR] No Write Mode Selected (--append/--overwrite)"<<std::endl;
        return -1;
    }
    if(APPEND && OVERWRITE) {
        std::cerr<<"[ERROR] Both Append and Overwrite Selected"<<std::endl;
        return -1;
    }

    std::unique_ptr<Calculation> calculation;   

    switch(selected_cube) {
        case CubeType::_RubiksCube:
            calculation = std::make_unique<RubiksCube>();
            break;
        case CubeType::_Pyraminx:
            calculation = std::make_unique<Pyraminx>();
            break;
        case CubeType::_DodecagonMinx:
            calculation = std::make_unique<DodecagonMinx>();
            break;
    }

    std::cout<<"Calculating Number Of Combinations [1/5]"<<std::endl;
    number = calculation->Calculate(LAYERS);

    std::cout<<"Converting to String [2/5]"<<std::endl;
    if(calculation->returnNumDigits(LAYERS) < 50 || PRINTFULLNUMBER) numcombos = number.get_str();
    else std::cout<<"[Info] Skipping Conversion. Use '--printfullnumber 1' or '--printfullnumber true' to print the entire number"<<std::endl;

    std::cout<<"Calculating Scientific Notation and Formatting [3/5]"<<std::endl;
    numcombos_scientific = calculation->returnScientific(number, PRECISION);

    std::cout<<"Calculating Number of Digits [4/5]"<<std::endl;
    numdigits = std::to_string(calculation->returnNumDigits(LAYERS));

    std::cout<<"Calculating Number Of Trailing Zeros [5/5]"<<std::endl;
    numtrailzeros = std::to_string(calculation->returnTrailingZeros(LAYERS));
    std::cout<<"-----------------------------------------"<<std::endl;

    if(WRITE_TO_FILE) {
        std::cout<<"Writing to File [1/1]"<<std::endl;

        std::ios::openmode mode;
        if(APPEND) {
            mode = std::ios::app;
        }
        if(OVERWRITE) {
            mode = std::ios::trunc;
        }

        std::ofstream file(FILE_PATH, mode);
        if(file.is_open()) {
            if(APPEND) {
                file<<"-----------------------------------------"<<std::endl;
            }
            file<<"Size of Cube: "<<LAYERS<<std::endl;
            file<<"Number of Combinations: "<<std::endl;
            file.write(number.get_str().c_str(), std::stoi(numdigits));
            file<<std::endl;
            file<<"Number of Combinations (Scientific): "<<std::endl;
            numcombos_scientific[strcspn(numcombos_scientific.c_str(), "\n")] = '\0';
            file<<numcombos_scientific<<std::endl;

            file<<"Number of Digits: "<<std::endl;
            file<<numdigits.c_str()<<std::endl;

            file<<"Number of Trailing Zeros: "<<std::endl;
            file<<numtrailzeros.c_str()<<std::endl;
            file.close();
            std::cout<<"Successfully Wrote to File: "<<FILE_PATH<<std::endl;
            std::cout<<"-----------------------------------------"<<std::endl;
        } else {
            std::cerr<<"[ERROR] Count Not Open File"<<std::endl;
        }
    }


    std::cout<<"Calculation Finished Successfully"<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
    std::cout<<"Size of Cube: "<<LAYERS<<std::endl;
    std::cout<<"Number of Combinations: "<<std::endl;
    if(calculation->returnNumDigits(LAYERS) < 50 || PRINTFULLNUMBER) {
        std::cout<<numcombos.c_str()<<std::endl;
    } else {
        std::cout<<"[Info] Number too large to display fully."<<std::endl;
    }
    std::cout<<"Number of Combinations (Scientific): "<<std::endl;
    numcombos_scientific[strcspn(numcombos_scientific.c_str(), "\n")] = '\0';
    std::cout<<numcombos_scientific<<std::endl;

    std::cout<<"Number of Digits: "<<std::endl;
    std::cout<<numdigits.c_str()<<std::endl;

    std::cout<<"Number of Trailing Zeros: "<<std::endl;
    std::cout<<numtrailzeros.c_str()<<std::endl;
}