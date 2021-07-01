#include <random>
#include <iomanip>
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

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

        static Vector2f GetRandomVector2(float maxX, float maxY)
        {
            float randX = GetRandomFloat(0, maxX);
            float randY = GetRandomFloat(0, maxY);

            return Vector2f(randX, randY);
        }
};