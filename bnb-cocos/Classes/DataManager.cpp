#include "DataManager.h"
#include <random>

uint64_t DataManager::secret_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    uint64_t val;
    for (int i = 0; i < 64; i++) {
        val += dis(gen);
        val = val << 2;
    }
    return val;
}
uint64_t DataManager::secret_code = DataManager::secret_generator();

DataManager* DataManager::getInstance() {
    static DataManager INSTANCE;
    return &INSTANCE;
}


int         DataManager::getIntegerForKey(const char *key) {
    return name2int[std::string(key)];
}

void       DataManager::setIntegerForKey(const char *key, int value) {
    name2int[std::string(key)] = value;
}
std::string DataManager::getStringForKey(const char* key) {
    return name2str[std::string(key)];
}

void DataManager::setStringForKey(const char* key, const std::string& value) {
    name2str[std::string(key)] = value;
}

void DataManager::setFloatForKey(const char* key, float value) {
    name2float[std::string(key)] = value;
}
float DataManager::getFloatForKey(const char* key) {
    return name2float[std::string(key)];
}
