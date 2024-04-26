//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_VALIDATOR_H
#define TURISM_QT_VALIDATOR_H

#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include "Oferta.h"

class ValidatorException : public std::exception {
    std::vector<std::string> msg;
public:
    explicit ValidatorException(std::vector<std::string> message) : msg(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        std::ostringstream oss;
        for(const auto& m : msg) {
            oss << m << "\n";
        }
        // Static string to hold the concatenated messages
        static std::string msg_str;
        msg_str = oss.str();
        return msg_str.c_str();
    }
    friend std::ostream& operator<<(std::ostream& out, const ValidatorException& ex);
};
std::ostream& operator<<(std::ostream& out, const ValidatorException& ex);


class OfertaValidator{
public:
    static void validate(const Oferta& of);
};

void testValidator();

#endif //TURISM_QT_VALIDATOR_H
