#include "CommonUtils.h"
#define _USE_MATH_DEFINES

#include <cmath>

namespace utils {
	float toRad(float degrees) {
		return degrees * (static_cast<float>(M_PI) / 180.0f);
	}
}
