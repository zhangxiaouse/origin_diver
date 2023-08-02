#include "error.hpp"

#include "../normal/preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  Error::Error() {
    std::cout << "Enter Error" << std::endl;
  }

  Error::~Error() {}

  std::string Error::getStateName() const {
    return std::string("Error");
  }

  boost::statechart::result Error::react(const EvFromHardware& EvFromHardware) {
    if (context<Carstate>().hardware_state() == 0) {
      context<Carstate>().SetcarState(2);
      return transit<Normal>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3