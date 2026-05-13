#pragma once
#include <exception>
#include <string>
#include <utility>

class pokeException : public std::exception {
protected:
    std::string message;
public:
    explicit pokeException(std::string  msg) : message(std::move(msg)) {}
    
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class statException : public pokeException {
public:
    explicit statException(const std::string& msg)
        : pokeException("STAT ERROR: " + msg) {}
};

class inputException : public pokeException {
public:
    explicit inputException(const std::string& msg)
        : pokeException("INPUT ERROR: " + msg) {}
};

class battleException : public pokeException {
public:
    explicit battleException(const std::string& msg)
        : pokeException("BATTLE ERROR: " + msg) {}
};