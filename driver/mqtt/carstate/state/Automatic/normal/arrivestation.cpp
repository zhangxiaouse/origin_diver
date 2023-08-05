#include "arrivestation.hpp"

#include "normalrun.hpp"
#include "preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  ArriveStation::ArriveStation() {
    std::cout << "Enter ArriveStation 车辆到达站点  " << std::endl;
  }

  ArriveStation::~ArriveStation() {}

  std::string ArriveStation::getStateName() const {
    return std::string("ArriveStation");
  }

  boost::statechart::result ArriveStation::react(const EvFromPlanning& EvFromPlanning) {
    if (context<Carstate>().planning_state() == 2) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else if (context<Carstate>().planning_state() == 1) {
      context<Carstate>().SetcarState(3);
      return transit<NormalRun>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3