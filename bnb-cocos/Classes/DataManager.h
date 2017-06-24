#ifndef DataManager_hpp
#define DataManager_hpp

#include "cocos2d.h"

USING_NS_CC;

class DataManager {
public:
    static DataManager* getInstance();
    int         getIntegerForKey(const char *key);
    void         setIntegerForKey(const char *key, int value);
    std::string getStringForKey(const char* key);
    void setStringForKey(const char* key, const std::string&);
    float getFloatForKey(const char* key);
    void setFloatForKey(const char* key, float);
private:
    DataManager() = default;
    DataManager(const DataManager& s) = delete;
    DataManager& operator=(const DataManager& s) = delete;
    
    static uint64_t secret_code;
    static uint64_t secret_generator();
    std::map<std::string, int>          name2int;
    std::map<std::string, std::string>  name2str;
    std::map<std::string, float>        name2float;
};

#endif /* DataManager_hpp */
