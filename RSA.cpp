#pragma once
#include <iostream>
#include <climits>
using namespace std;

class RSA
{
public:
 bool isPrime(unsigned long long x);
 unsigned long long getPrime(unsigned long long min, unsigned long long max) {


 }
 unsigned long long gcd(unsigned long long x, unsigned long long y) {


 }
 unsigned long long lcm(unsigned long long x, unsigned long long y) {


 }
 unsigned long long modInverse(unsigned long long e, unsigned long long lam) {


 }
 unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long n) {


 }
 void init(unsigned long long seed) {


 }
 unsigned long long encipher(unsigned long long m) {


 }
 unsigned long long decipher(unsigned long long c) {


 }

private:
 unsigned long long p;
 unsigned long long q;
 unsigned long long n;
 unsigned long long lambda;
 unsigned long long d;
 unsigned long long e;
 
};
