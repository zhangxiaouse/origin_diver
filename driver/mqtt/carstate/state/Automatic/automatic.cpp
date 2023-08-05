#include "automatic.hpp"

#include "../Manual/prepare.hpp"
namespace cyberc3 {
namespace carstate {

  Automatic::Automatic() {
    std::cout << "Enter Automatic" << std::endl;
  }

  Automatic::~Automatic() {}

  std::string Automatic::getStateName() const {
    return std::string("Automatic");
  }

  boost::statechart::result Automatic::react(const EvFromCar& EvFromCar) {
    if (context<Carstate>().auto_state() == 0) {
      context<Carstate>().SetcarState(1);
      return transit<Manual>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3