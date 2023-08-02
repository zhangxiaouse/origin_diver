#include "normalrun.hpp"

#include "arrivestation.hpp"
#include "localizationstop.hpp"
#include "obstaclestop.hpp"
#include "preparedone.hpp"
#include "webstop.hpp"
#include "electricfencestop.hpp"

namespace cyberc3 {
namespace carstate {

  NormalRun::NormalRun() {
    std::cout << "Enter NormalRun 一切正常 车辆正常行驶 " << std::endl;
  }

  NormalRun::~NormalRun() {}

  std::string NormalRun::getStateName() const {
    return std::string("NormalRun");
  }

  boost::statechart::result NormalRun::react(const EvFromPlanning& EvFromPlanning) {
    if (context<Carstate>().planning_state() == 0) {
      context<Carstate>().SetcarState(4);
      return transit<ArriveStation>();
    } else if (context<Carstate>().planning_state() == 2) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

  boost::statechart::result NormalRun::react(const EvFromObstcle& EvFromObstcle) {
    if (context<Carstate>().obstacle_state() == 1) {
      context<Carstate>().SetcarState(7);
      return transit<ObstacleStop>();
    } else
      return discard_event();
  }

  boost::statechart::result NormalRun::react(const EvFromWebEmergency& EvFromWebEmergency) {
    if (context<Carstate>().webemergency_state() == 1) {
      context<Carstate>().SetcarState(6);
      return transit<WebStop>();
    } else
      return discard_event();
  }

  boost::statechart::result NormalRun::react(const EvFromLocalization& EvFromLocalization) {
    if (context<Carstate>().localization_state() == 1) {
      context<Carstate>().SetcarState(9);
      return transit<LocalizationStop>();
    } else
      return discard_event();
  }

  boost::statechart::result NormalRun::react(const EvFromElectricfence& EvFromElectricfence) {
    if (context<Carstate>().electricfence_state() == 1) {
      context<Carstate>().SetcarState(10);
      return transit<ElectricfenceStop>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3