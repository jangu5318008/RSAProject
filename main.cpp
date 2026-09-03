#include "RSA.h"
#include <iostream>

using namespace std;
int SCORE = 0;

void testIsPrime(RSA& rsa);
void testGetPrime(RSA& rsa);
void testLCM(RSA& rsa);
void testGCD(RSA& rsa);
void testModInverse(RSA& rsa);
void testModExp(RSA& rsa);

int main()
{
    unsigned int seed;
    unsigned long long c;
    unsigned long long m;

    cout << "Constructing RSA object..." << endl;
    RSA rsa;

    cout << "\n*** Performing unit tests..." << endl;
    testIsPrime(rsa);
    testGetPrime(rsa);
    testLCM(rsa);
    testGCD(rsa);
    testModInverse(rsa);
    testModExp(rsa);
    cout << "*** Unit tests complete.  SCORE: " << SCORE << "/6\n" << endl;

    cout << "Enter a seed: ";
    cin >> seed;
    rsa.init(seed);

    cout << "Enter a positive number:" << endl;
    cin >> m;

    c = rsa.encipher(m);
    cout << "Cipher: " << c << endl;

    m = rsa.decipher(c);
    cout << "Decrypted cipher: " << m << endl;

    return 0;
}


void testIsPrime(RSA& rsa)
{
    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
    unsigned int primeIndex = 0;
    cout << "Testing isPrime on numbers 2 through 100..." << endl;
    bool passedIsPrime = true;
    for (int i = 2; i <= 100 && passedIsPrime; i++)
    {
        if (i == primes[primeIndex] && primeIndex < sizeof(primes) / 4)
        {
            primeIndex++;
            if (!rsa.isPrime(i)) passedIsPrime = false;
        }
        else if (rsa.isPrime(i)) passedIsPrime = false;
    }
    if (passedIsPrime)
    {
        cout << "Primes from 2 through 100 identified correctly.  +1 point." << endl;
        SCORE++;
        return;
    }
    else
    {
        cout << "Primes from 2 through 100 NOT identified correctly." << endl;
        return;
    }
}

void testGetPrime(RSA& rsa)
{
    bool passedGetPrime = true;
    cout << "Testing two calls to getPrime with default seed." << endl;
    ///41, 12197
    unsigned long long prime1, prime2;
    cout << "Calling getPrime(0, USHRT_MAX)..." << endl;
    prime1 = rsa.getPrime(0, USHRT_MAX);
    cout << "Calling getPrime(UCHAR_MAX, USHRT_MAX)..." << endl;
    prime2 = rsa.getPrime(UCHAR_MAX, USHRT_MAX);
#ifdef __linux__
    if (prime1 != 56401 || prime2 != 10529) passedGetPrime = false;
#elif _WIN32
    if (prime1 != 41 || prime2 != 12197) passedGetPrime = false;
#else

#endif
    if (passedGetPrime)
    {
        cout << "getPrime correctly returns a random prime using the given ranges.  +1 point." << endl;
        SCORE++;
        return;
    }
    else
    {
        cout << "getPrime does NOT correctly return a random prime using the given ranges." << endl;
        cout << "Prime 1: " << prime1 << endl;
        cout << "Prime 2: " << prime2 << endl;
        return;
    }
}

void testLCM(RSA& rsa)
{
    ///LCM
    cout << "Testing lcm..." << endl;
    bool passedLcm = true;

    cout << "Calling lcm(2940, 3150)..." << endl;
    unsigned long long lcm1 = rsa.lcm(2940, 3150);
    cout << "Calling lcm(1343540, 646982)..." << endl;
    unsigned long long lcm2 = rsa.lcm(1343540, 646982);
    if (lcm1 != 44100 || lcm2 != 434623098140) passedLcm = false;

    if (passedLcm)
    {
        cout << "LCMs correctly calculated.  +1 point." << endl;
        SCORE++;
        return;
    }
    else
    {
        cout << "LCMs NOT correctly calculated." << endl;
        return;
    }
}

void testGCD(RSA& rsa)
{
    ///GCD
    cout << "Testing gcd..." << endl;
    ///gcd
    bool passedGcd = true;
    cout << "Calling gcd(4200, 3780)..." << endl;
    unsigned long long gcd1 = rsa.gcd(4200, 3780);
    cout << "Calling gcd(41654564,42)..." << endl;
    unsigned long long gcd2 = rsa.gcd(41654564, 42);
    if (gcd1 != 420 || gcd2 != 14) passedGcd = false;
    if (passedGcd)
    {
        cout << "GCDs correctly calculated.  +1 point." << endl;
        SCORE++;
        return;
    }
    else
    {
        cout << "GCDs NOT correctly calculated." << endl;
        return;
    }
}

void testModInverse(RSA& rsa)
{
    ///modInverse
    cout << "Testing modInverse..." << endl;
    cout << "Using e = 3" << endl;
    cout << "Generating random coprime value for lam in the range [UCHAR_MAX...UINT_MAX]." << endl;
    unsigned long long rand1;

    do
    {
        rand1 = UCHAR_MAX + rand() % (UINT_MAX - UCHAR_MAX + 1);
    } while (rand1 % 3 == 0);

    cout << "Calling modInverse(" << 3 << ", " << rand1 << ")..." << endl;
    unsigned long long d = rsa.modInverse(3, rand1);

    if ((d * 3) % rand1 != 1)
    {
        cout << "(" << d << " * " << 3 << ")" << " % " << rand1 << " != 1.  Test failed." << endl;
        return;
    }
    else
    {
        cout << "(" << d << " * " << 3 << ")" << " % " << rand1 << " == 1.  Test passed.  +1 point" << endl;
        SCORE++;
        return;
    }
}

void testModExp(RSA& rsa)
{
    ///modExp
    cout << "Testing modExp(1337, 123456789, 111213141) ..." << endl;
    unsigned long long res = rsa.modExp(1337, 123456789, 111213141);
    if (res != 24409406)
    {
        cout << "modExp return value incorrect." << endl;
        return;
    }
    else
    {
        cout << "modExp return value correct. +1 point" << endl;
        SCORE++;
        return;
    }
}
