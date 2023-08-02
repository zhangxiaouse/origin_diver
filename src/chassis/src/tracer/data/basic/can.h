#pragma once

typedef unsigned char BYTE;
typedef unsigned int UINT;

namespace cyberc3 {
namespace basic {
    class can {
    public:
        UINT id;
        UINT len;
        BYTE data[8];
    };
}  // namespace basic
}  // namespace cyberc3