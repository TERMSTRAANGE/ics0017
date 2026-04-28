#include "exceptions.h"

InvalidInputException::InvalidInputException(const std::string& context) {
    message = "Invalid input. " + context;
}

const char* InvalidInputException::what() const noexcept {
    return message.c_str();
}

InvalidFundsException::InvalidFundsException(int amount) : amount(amount) {
    message = "Invalid funds amount. Your input: " + std::to_string(amount) + 
              ". Please enter a positive amount.";
}

const char* InvalidFundsException::what() const noexcept {
    return message.c_str();
}

InvalidBetException::InvalidBetException(int amount, int available_funds) 
    : amount(amount), available_funds(available_funds) {
    message = "Invalid bet amount. Your input: " + std::to_string(amount) + 
              ". Must be between 1$ and " + std::to_string(available_funds) + "$.";
}

const char* InvalidBetException::what() const noexcept {
    return message.c_str();
}

InvalidChoiceException::InvalidChoiceException(int choice) : choice(choice) {
    message = "Invalid choice. Your input: " + std::to_string(choice) + 
              ". Please enter 1 (Hit) or 2 (Stand).";
}

const char* InvalidChoiceException::what() const noexcept {
    return message.c_str();
}

InvalidResponseException::InvalidResponseException(const std::string& response) : response(response) {
    message = "Invalid response '" + response + "'. Please enter 'yes' or 'no'.";
}

const char* InvalidResponseException::what() const noexcept {
    return message.c_str();
}