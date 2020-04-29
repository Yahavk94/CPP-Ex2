#pragma once

#include <bits/stdc++.h>
#include <queue>

#define FEMALE 0
#define MALE 1
#define EMPTY 2

class MyException : public std::exception {
private:
    std::string msg;
public:
    MyException(std::string msg) {this->msg = msg;}
    ~MyException() {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};