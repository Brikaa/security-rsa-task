#include <iostream>
#include <utility>

// returns x, y where ax + by = gcd(a, b)
std::pair<long long, long long> bezout(long long a, long long b)
{
    if (a == 0)
        return {0, 1};
    auto [x, y] = bezout(b % a, a);
    return {y - (b / a) * x, x};
}

long long mod_inverse(long long e, long long phi_n)
{
    auto [x, _] = bezout(e, phi_n);
    // since e * x + phi_n * y = gcd(e, phi_n)
    // ∴ e * x + phi_n * y = 1
    // ∴ e*x % phi_n + phi_n*y % phi_n = 1 % phi_n
    // ∴ e*x % phi_n = 1
    // ∴ x is our mod inverse (d)
    // We want positive x
    return (x % phi_n + phi_n) % phi_n;
}

long long multiply_mod(long long a, long long b, long long mod)
{
    // 8*3 = 2*4*b = 2*2*2*b
    // 9*3 = b + 2*4*b = b + 2*2*2*b
    long long res = 0;
    while (a != 1)
    {
        if (a % 2 == 1)
        {
            res = (res + b) % mod;
            --a;
        }
        b = (b + b) % mod;
        a /= 2;
    }
    return (res + b) % mod;
}

long long power_mod(long long base, long long exponent, long long mod)
{
    // 2 ** 8 = ((2 ** 2) ** 2) ** 2
    // 2 ** 9 = 2 * ((2 ** 2) ** 2) ** 2
    long long res = 1;
    while (exponent != 1)
    {
        if (exponent % 2 == 1)
        {
            res = multiply_mod(res, base, mod);
            --exponent;
        }
        base = multiply_mod(base, base, mod);
        exponent /= 2;
    }
    return multiply_mod(res, base, mod);
}

long long encrypt(long long m, long long e, long long n)
{
    return power_mod(m, e, n);
}

long long decrypt(long long c, long long d, long long p, long long q)
{
    return power_mod(c, d, p * q);
}

int main()
{
    long long p, q, e, m;
    std::cout << "p, q, e, m\n";
    std::cin >> p >> q >> e >> m;
    const long long d = mod_inverse(e, (p - 1) * (q - 1));
    long long encrypted = encrypt(m, e, p * q);
    std::cout << "d: " << d << '\n';
    std::cout << "Encrypted: " << encrypted << '\n';
    std::cout << "Decrypted: " << decrypt(encrypted, d, p, q) << '\n';
    return 0;
}
