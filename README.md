# CubeCounter

This is the repository of the CubeCounter project. CubeCounter is an open source project for people to visualize and calculate the number of combinations on an NxNxN Rubik's Cube. As the number of combinations (even on the classic 3x3) may exceed the limit of a 64 bit integer by several orders of magnitude, special libraries are needed. CubeCounter not only uses a powerful library (GMP) to calculate massive numbers, but it also provides a visual representation of a Rubik's Cube of that size (which can be extremely hard to replicate physically). 

## Goal of CubeCounter

The number of combinations on an NxNxN Rubik's Cube is calculated by the formula:
$$\Large
7! \cdot 3^6 \cdot (24 \cdot 2^10 \cdot 12!)^{N \bmod 2} \cdot 24^{\lfloor \frac{N-2}{2} \rfloor} \cdot (24!/4!^6)^{{\lfloor (\frac{N-2}{2})^2} \rfloor}
$$

The above formula is actually very intuitive, and can be derived using combinatorics. Its derivation is explained on many sources online.
As expected from the many factorials and exponents in this formula, it grows very fast. In fact, by N = 3 (which represents the 3x3x3 Rubik's Cube), the value is already approx. $4.3 \times 10^{19}$. Programming languages such as C or C++, despite their speed, do not allow the user to calculate past $2^{64}$, which is for good reasons. However, such numbers are required to calculate the value of the formula for higher values of N. CubeCounter uses powerful libraries and provides a visual representation of the cube so the true scale of these numbers can be appreciated. 
CubeCounter not only contributes to this formula, but can also improve the field of number theory, by analyzing the many patterns that appear within these numbers, some of which are described below. 

## Formulas

Number of combinations on NxNxN Cube (not created by CubeCounter):
$$\Large
7! \cdot 3^6 \cdot (24 \cdot 2^10 \cdot 12!)^{N \bmod 2} \cdot 24^{\lfloor \frac{N-2}{2} \rfloor} \cdot (24!/4!^6)^{{\lfloor (\frac{N-2}{2})^2} \rfloor}
$$

Number of Digits in the Result (Using Logarithm of Combination Formula):
$$
\mathop{\text{floor}}\left(6.56515806476\ +\mathop{\text{mod}}\left(N,2\right)13.0708481624+\mathop{\text{floor}}\left(\frac{N-2}{2}\right)23.7927056702+\mathop{\text{floor}}\left(\left(\frac{N-2}{2}\right)^{2}\right)15.5114382199\right)+1
$$

Number of Trailing Zeros in the Result (custom formula):
$$
\left(N-\left(\mathop{\text{mod}}\left(N,2\right)+1\right)\right)^{2}+2\mathop{\text{mod}}\left(N,2\right)
$$

The custom formulas above are used within CubeCounter for efficiency, and are usually much faster than the standard methods of digit counting. 

## Building CubeCounter

### Prerequisites:

* C/C++ compiler (GCC for Linux, Clang for MacOS, MingW or MSVC for Windows)
    * Please make sure you also have a C++ compiler, or else the build will fail. 
* CMake
* Generator for CMake (Ninja for MacOS/Linux, Ninja or Visual Studio for Windows)

* OpenGL (GUI Version Only) For Linux
    * If building with the user interface, make sure you have the OpenGL packages installed:
    * Ubuntu/Debian based: `sudo apt install mesa-common-dev libgl1-mesa-dev`
    * Fedora based: `sudo dnf install mesa-common-devel libGL-devel`
    * Arch based: `sudo pacman -S mesa mesa-utils`

### Configure and Build

First, clone the git repository into a directory: `git clone https://github.com/AdarshS432/CubeCounter.git`

Move into the cloned directory: `cd CubeCounter` (or OS equivalent)

Use CMake to configure the project. Available presets:
    ```
    "main"              - Custom configure preset
    "windows-mingw"     - Windows Mingw
    "linux-gcc"         - Linux GCC
    "macos-clang"       - MacOS Clang
    "windows-mingw-cli" - Windows Mingw CLI-Only
    "linux-gcc-cli"     - Linux GCC CLI-Only
    "macos-clang-cli"   - MacOS Clang CLI-Only
    ```

When configuring, make sure to set the BUILD_GUI option (requires OpenGL). Set this to `OFF` for a cli-only build. 

If using Ninja:
`cmake --preset [PRESET_NAME] -DBUILD_GUI=[ON/OFF] -DCMAKE_BUILD_TYPE=[Debug/Release]`
If using Visual Studio:
`cmake --preset [PRESET_NAME] -DBUILD_GUI=[ON/OFF]`

Note: If a cli-only preset was selected, there is no need to set the BUILD_GUI option (as it sets it for OFF by default)

Then, build the project.

Ninja:
`cmake --build build/[PRESET_NAME]`
Visual Studio:
`cmake --build build/[PRESET_NAME] --config Release`

## How to Use

Navigate to `build/[PRESET_NAME]` or wherever the compiled files are. 

To launch the GUI version (the project must be built using `BUILD_GUI` set to `ON` to compile the GUI):
`./CubeCounter` (or OS equivalent)
To launch the CLI:
`./cubecounter-cli` (or OS equivalent)

The CLI version has options to control the calculation and output:

Cube Size: `--layercount [NUMBER]`

Print Full Number (this may print a very large number): `--printfullnumber`

Scientific Notation Precision (number of digits after decimal point): `--precision [NUMBER]`, Note: the number must be less than or equal to 64.

Write Output to File: `--file [PATH]`

Append Output to File: `--append` Note: This command places deshes (-) before the start of each file so that it is separated.


**IF YOU OWN A CPU THAT CONTAINS Zen 5 CORES, PLEASE READ BELOW:**

It is stated on the GMP webpage that Ryzen 9000 series processors may be affected by their library, and have reported that some of the processors in their testing computers have died. Please exercise caution (or even better, modify this project to better fit your computer) to prevent damage. 

The software itself is unlikely to cause any harm to the CPU. The damage is likely due to the custom assembly used to optimize the library, which can wear out the CPU, if the safety measures built into Zen5 processors fail. 

The user is advised to exercise common sense when using this software, and to understand the limitations of their own device, and the intensity and duration of the calculations they run. 