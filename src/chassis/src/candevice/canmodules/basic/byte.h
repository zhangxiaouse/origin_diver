#pragma once

#include "stdint.h"

typedef unsigned char BYTE;
typedef unsigned int  UINT;

namespace cyberc3 {
namespace can {

  class byte_tool {
   public:
    static void set_bit_0(BYTE& byte, int pos);
    static void set_bit_1(BYTE& byte, int pos);
    static bool is_bit_0(BYTE& byte, int pos);
    static bool is_bit_1(BYTE& byte, int pos);
  };

}  // namespace can
}  // namespace cyberc3