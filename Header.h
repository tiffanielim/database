//
// Created by Tiffanie Lim on 12/4/24.
//

#ifndef DATABASE_HEADER_H
#define DATABASE_HEADER_H
#include <iostream>

class Header {
private:
    std::string _name;

public:
    Header() = default;
    explicit Header(const std::string &name);
    std::string getName() const;
    void setName(const std::string &name);
};

#endif //DATABASE_HEADER_H
