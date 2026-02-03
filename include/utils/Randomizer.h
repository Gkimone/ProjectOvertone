#pragma once
#include <random>

namespace Overtone {
	class Rand {
	private:
		static std::mt19937& getEngine() {
			static std::random_device randNum;
			static std::mt19937 engine(randNum());
			return engine;
		}

	public:
        static int getInt(int min, int max) {
            std::uniform_int_distribution<int> randInt(min, max);
            return randInt(getEngine());
        }

        static float getFloat(float min = 0.0f, float max = 1.0f) {
            std::uniform_real_distribution<float> randflt(min, max);
            return randflt(getEngine());
        }

        static bool chance(float probability) {
            return getFloat() < probability;
        }

		Rand() = delete;
	};
}