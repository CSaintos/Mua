ToDo:
NumberUtils should be a Number class that is its own library.
Turn static libraries into dynamic libraries (this will require having postbuildcmds).
In some shape or form we need to reduce the decoupling such that I can get real threaded builds.
The Pollard Rho Algorithm doesn't work for all numbers. It is an improvement to trial division, but it only works on special numbers. Let's use 'n' as the number for which the algorithm may succeed. 
1. 'n' is an int.
2. 'n' > 2.
3. 'n' is an odd number.
4. (possibly) 'n' cannot be a product of an exponent. etc. 9 = 3^2; 5^3 = 125;

- Condition 1 is resolved using NumberUtils::fractionalize.
- Condition 2 is resolved using conditional for when n <= 2.
- Condition 3 can be resolved using a conditional of (n mod 2), and factoring out 2 until odd or prime.
- Condition 4 is still yet unknown to be true to me, so we should make a NumberUtilsTest for factorize, testing various numbers.
  - If after testing the condition is true, then either we research a way to resolve this problem, or we decide on using the msieve library as a replacement of the rho algorithm for the gnfs algorithm.
