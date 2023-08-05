#pragma once

#include <string>

namespace cyberc3 {
namespace carstate {

  struct IState {
    virtual std::string getStateName() const = 0;
  };

}  // namespace carstate
}  // namespace cyberc3