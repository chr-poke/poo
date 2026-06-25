#pragma once
#include <map>
#include <string>

template <typename T>

class registry {
private:
    std::map<std::string, T> database;

public:
    void add(const std::string& key, const T& item) {
        database[key] = item;
    }
    
    T& get(const std::string& key) {
        return database[key];
    }

    [[nodiscard]] bool hasSeen(const std::string& key) const {
        return database.contains(key);
    }

    const std::map<std::string, T>& getDatabase() const {
        return database;
    }
};