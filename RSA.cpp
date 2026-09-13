#include "RSA.h"
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

 bool RSA::isPrime(unsigned long long x) {

    if (x == 1) {
        return false;
    }
    else if (x == 2) {
        return true;
    }
    else if (x % 2 == 0) {
       return false;
    }
    for (int i = 3; i < sqrt(x); i += 2) {
        //i++ works but you don't need to check even numbers since they are not prime
        if (x % i == 0) {
            return false;
        }
        }
    return true;
    }



 unsigned long long RSA::getPrime(unsigned long long min, unsigned long long max) {

   unsigned long long randomNum = rand() % (max - min + 1) + min; 
   
   while (isPrime(randomNum) == false) {
        randomNum = rand() % (max - min + 1) + min; 

   }
        return randomNum;
   }




 unsigned long long RSA::gcd(unsigned long long x, unsigned long long y) {

    if (y == 0) {
        return x;
    }
        return gcd(y, x % y);
    }


 unsigned long long RSA::lcm(unsigned long long x, unsigned long long y) {
    return (x * y) / gcd(x, y);
 }


 unsigned long long RSA::modInverse(unsigned long long e, unsigned long long lam) {

for (unsigned long long d = 1; d < lam; d++) {
    if ((e * d) % lam == 1) {
        return d;
    }
}
    return 0;
 }


 
unsigned long long RSA::modExp(unsigned long long base, unsigned long long exp, unsigned long long n) {
   unsigned long long ans = 1;
   for(unsigned long long i = 0; i < exp; i++) {
      ans = (ans * base) % n;
   }
   return ans;

}


 void RSA::init(unsigned long long seed) {
    srand(seed);

    p = getPrime(UCHAR_MAX, USHRT_MAX);
    q = getPrime(UCHAR_MAX, USHRT_MAX);

        cout << p << " " << q << endl;

        n = p * q; 

        lambda = lcm(p - 1, q - 1);

        e = getPrime(2, lambda - 1);

    while (lambda % e == 0) {
        e = getPrime(2, lambda - 1);
    }
        cout << e << endl;
        d = modInverse(e, lambda);
        cout << d << endl;
        cout << "Public key: " << n << " " << e << endl; 
        cout << "Private key: " << n << " " << d << endl;
 }


 unsigned long long RSA::encipher(unsigned long long m) {
   return modExp(m, e, n);
 }


 unsigned long long RSA::decipher(unsigned long long c) {

    return modExp(c, d, n); 
 }


