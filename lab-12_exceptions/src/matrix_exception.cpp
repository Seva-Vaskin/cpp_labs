#include "matrix_exception.h"

namespace matrix {
    const char *MatrixException::what() const noexcept {
        return message_.c_str();
    }
}