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
\operatorname{floor}\left(6.56515806476\ +\operatorname{mod}\left(N,2\right)13.0708481624+\operatorname{floor}\left(\frac{N-2}{2}\right)23.7927056702+\operatorname{floor}\left(\left(\frac{N-2}{2}\right)^{2}\right)15.5114382199\right)+1
$$

Number of Trailing Zeros in the Result:
$$
\left(N-\left(\operatorname{mod}\left(N,2\right)+1\right)\right)^{2}+2\operatorname{mod}\left(N,2\right)
$$

**IF YOU OWN A CPU THAT CONTAINS Zen 5 CORES, PLEASE READ BELOW:**

It is stated on the GMP webpage that Ryzen 9000 series processors may be affected by their library, and have reported that some of the processors in their testing computers have died. Please exercise caution (or even better, modify this project to better fit your computer) to prevent damage. 

The software itself is unlikely to cause any harm to the CPU. The damage is likely due to the custom assembly used to optimize the library, which can wear out the CPU, if the safety measures built into Zen5 processors fail. 

The user is advised to exercise common sense when using this software, and to understand the limitations of their own device, and the intensity and duration of the calculations they run. 