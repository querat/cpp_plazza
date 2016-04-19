//
// Created by lina on 19/04/16.
//

#ifndef PLAZZA_TEST_HH
#define PLAZZA_TEST_HH

#include <iostream>
#include <regex.h>

class   OpenFile{
public:
    OpenFile();
    ~OpenFile();
    void ReadFile();

private:
    std::string     _file;

};

#endif //PLAZZA_TEST_HH
