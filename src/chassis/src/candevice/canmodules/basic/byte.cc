#include "canmodules/basic/byte.h"

namespace cyberc3 {
namespace can {

  void byte_tool::set_bit_0(BYTE& byte, int pos) {
    static const uint8_t BIT_MASK_0[] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
    byte &= BIT_MASK_0[pos];
  }

  void byte_tool::set_bit_1(BYTE& byte, int pos) {
    static const uint8_t BIT_MASK_1[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    byte |= BIT_MASK_1[pos];
  }

  bool byte_tool::is_bit_0(BYTE& byte, int pos) {
    return ((byte >> pos) % 2 == 0);
  }

  bool byte_tool::is_bit_1(BYTE& byte, int pos) {
    return ((byte >> pos) % 2 == 1);
  }

}  // namespace can
}  // namespace cyberc3
