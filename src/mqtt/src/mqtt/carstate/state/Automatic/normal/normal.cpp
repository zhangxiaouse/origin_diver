#include "normal.hpp"

#include "../error/hardwarefault.hpp"

namespace cyberc3 {
namespace carstate {

  Normal::Normal() {
    std::cout << "Enter Normal" << std::endl;
  }

  Normal::~Normal() {
    // std::cout << "Exit Normal" << std::endl;
  }

  std::string Normal::getStateName() const {
    return std::string("Normal");
  }

  boost::statechart::result Normal::react(const EvFromHardware& EvFromHardware) {
    if (context<Carstate>().hardware_state() == 1) {
      context<Carstate>().SetcarState(8);
      return transit<Error>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3