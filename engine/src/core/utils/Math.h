#ifndef MATH_H
#define MATH_H

namespace engine {
    class Math {
    public:
        static int Gcd(int a, int b) {
            if (b == 0) {
                return a;
            }
            return Gcd(b, a % b);
        }

        static int Lcm(int a, int b) {
            return a * b / Gcd(a, b);
        }
    };
}

#endif