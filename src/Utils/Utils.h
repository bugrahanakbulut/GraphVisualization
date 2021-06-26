#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

class Utils
{
    public:
        static float GetRandomFloat(float min = 0, float max = 1)
        {
            static random_device device;
            static default_random_engine gen(device());

            uniform_real_distribution<float> distribution(min, max);

            return distribution(gen);
        }
};