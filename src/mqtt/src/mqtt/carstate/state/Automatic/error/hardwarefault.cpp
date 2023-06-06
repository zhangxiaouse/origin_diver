#include "hardwarefault.hpp"

#include "../normal/preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  HardwareDefault::HardwareDefault() {
    std::cout << "Enter HardwareDefault 车辆硬件存在问题 请检查" << std::endl;
  }

  HardwareDefault::~HardwareDefault() {}

  std::string HardwareDefault::getStateName() const {
    return std::string("HardwareDefault");
  }

  boost::statechart::result HardwareDefault::react(const EvFromHardware& EvFromHardware) {
    if (context<Carstate>().hardware_state() == 0) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3