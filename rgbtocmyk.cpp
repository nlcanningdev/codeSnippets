#include <iostream>

float getMin(float a, float b) {
	if(a < b)
		return a;
	if(b < a)
		return b;
	return a;
}

void rgbtocmyk(float &c, float &m, float &y, float &k) {
	float r, g, b;
	c = 0; m = 0; y = 0; k = 0;
	
	std::cout << "r: ";
	std::cin >> r;
	std::cout << "g: ";
	std::cin >> g;
	std::cout << "b: ";
	std::cin >> b;
	
	if(r == 0 && g == 0 && b == 0) {
		k = 1;
		return;
	}
	
	c = 1 - (r / 255);
	m = 1 - (g / 255);
	y = 1 - (b / 255);
	
	k = getMin(c, getMin(m, y));
	
	c = (c - k) / (1 - k);
	m = (m - k) / (1 - k);
	y = (y - k) / (1 - k);
	return;
}

int main() {
	float c, m, y, k;
	rgbtocmyk(c, m, y, k);
	std::cout << c << " " << m << " " << y << " " << k << std::endl;
	char input;
	std::cout << "type a single character + return to quit" << std::endl;
	std::cin >> input;
	return 0;
}