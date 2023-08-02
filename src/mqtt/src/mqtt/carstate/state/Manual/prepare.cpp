#include "prepare.hpp"

#include "../Automatic/normal/preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  Prepare::Prepare() {
    std::cout << "Enter Prepare 车辆未准备完毕 请在准备完毕后切换到自动模式 " << std::endl;
  }

  Prepare::~Prepare() {}

  std::string Prepare::getStateName() const {
    return std::string("Prepare");
  }

  boost::statechart::result Prepare::react(const EvFromCar& EvFromCar) {
    if (context<Carstate>().auto_state() == 1) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3