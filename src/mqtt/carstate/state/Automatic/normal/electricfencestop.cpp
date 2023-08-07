#include "electricfencestop.hpp"

#include "preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  ElectricfenceStop::ElectricfenceStop() {
    std::cout << "Enter ElectricfenceStop 触发电子围栏 " << std::endl;
  }

  ElectricfenceStop::~ElectricfenceStop() {}

  std::string ElectricfenceStop::getStateName() const {
    return std::string("ElectricfenceStop");
  }

  boost::statechart::result ElectricfenceStop::react(const EvFromElectricfence& EvFromElectricfence) {
    if (context<Carstate>().electricfence_state() == 0) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3