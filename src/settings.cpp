#include "settings.h"

std::unordered_map<std::string, std::variant<bool, double>> settings {
    {"UncapFPS", true},
	{"ClickSound", true},
	{"MasterVolume", 1.0}
};