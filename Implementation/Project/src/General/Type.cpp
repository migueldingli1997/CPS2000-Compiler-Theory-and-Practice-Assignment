#include <stdexcept>
#include "Type.h"
#include "Exceptions.h"

const Type strToType(const std::string type) {

    // Attempt to match argument with one of the types
    for (int i = 0; i < NUMBER_OF_TYPES; i++) {
        if (type == TypeNames[i]) {
            return (Type) i;
        }
    }

    // Argument did not match with any of the types
    throw FatalTypeError("unhandled type.");
}
