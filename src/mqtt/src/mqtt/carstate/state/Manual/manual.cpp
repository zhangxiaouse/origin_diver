#include "manual.hpp"

#include "../Automatic/normal/preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  Manual::Manual() {
    std::cout << "Enter Manual" << std::endl;
  }

  Manual::~Manual() {}

  std::string Manual::getStateName() const {
    return std::string("Manual");
  }

  boost::statechart::result Manual::react(const EvFromCar& EvFromCar) {
    if (context<Carstate>().auto_state() == 1)
      return transit<Automatic>();
    else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3