#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

//�Q�l
//https://easings.net/ja

class EasingFunctions {
public:
	float easeInSine(float x) {
		return 1 - cos((x * M_PI) / 2);
	}
};