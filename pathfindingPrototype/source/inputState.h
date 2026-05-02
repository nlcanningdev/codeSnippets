#pragma once

struct InputState {
	InputState() : w(false), a(false), s(false), d(false) {}
	bool w;
	bool a;
	bool s;
	bool d;
};