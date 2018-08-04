#ifndef CPS2000_TYPE_H
#define CPS2000_TYPE_H

#include <string>

enum Type {
    Real,
    Bool,
    Int,
    String,
    NUMBER_OF_TYPES
};

const std::string TypeNames[NUMBER_OF_TYPES] = {
        "real",
        "bool",
        "int",
        "string"
};

const Type strToType(const std::string type);

#endif //CPS2000_TYPE_H
