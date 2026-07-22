#ifndef SETTINGS
#define SETTINGS

#include <unordered_map>
#include <string>
#include <variant>

extern std::unordered_map<std::string, std::variant<bool, double>> settings;

template<typename T>
T& GetSetting(const std::string& key){
    return std::get<T>(settings.at(key));
}

#endif