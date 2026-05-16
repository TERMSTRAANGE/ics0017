#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class InvalidInputException : public std::exception {
private:
    std::string message;
public:
    InvalidInputException(const std::string& context);
    const char* what() const noexcept override;
};

class InvalidFundsException : public std::exception {
private:
    int amount;
    std::string message;
public:
    InvalidFundsException(int amount);
    const char* what() const noexcept override;
};

class InvalidBetException : public std::exception {
private:
    int amount;
    int available_funds;
    std::string message;
public:
    InvalidBetException(int amount, int available_funds);
    const char* what() const noexcept override;
};

class InvalidChoiceException : public std::exception {
private:
    int choice;
    std::string message;
public:
    InvalidChoiceException(int choice);
    const char* what() const noexcept override;
};

class InvalidResponseException : public std::exception {
private:
    std::string response;
    std::string message;
public:
    InvalidResponseException(const std::string& response);
    const char* what() const noexcept override;
};

class FileOpenError : public std::exception {
private:
    std::string message;
public:
    FileOpenError();
    const char* what() const noexcept override;
};

class InvalidFileFormat : public std::exception {
private:
    std::string message;
public:
    InvalidFileFormat();
    const char* what() const noexcept override;
};

#endif
