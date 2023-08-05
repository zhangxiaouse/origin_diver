#pragma once

typedef unsigned char BYTE;
typedef unsigned int  UINT;

namespace cyberc3 {
namespace can {

  class can {
   public:
    UINT id;
    UINT len;
    BYTE data[8];
  };

}  // namespace can
}  // namespace cyberc3