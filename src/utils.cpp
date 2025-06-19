#include "utils.h"

bool isSkinColor(int r, int g, int b) {
	bool cond1 = r > 95 && g > 40 && b > 20;
	bool cond2 = __max(r, __max(g, b)) - __min(r, __min(g, b)) > 15;
	bool cond3 = abs(r - g) > 15 && r > g && r > b;

	return cond1 && cond2 && cond3;
}