#include "preparedone.hpp"

#include "normalrun.hpp"

namespace cyberc3 {
namespace carstate {

  PrepareDone::PrepareDone() {
    std::cout << "Enter PrepareDone 车辆准备完毕 请设置下一站 " << std::endl;
  }

  PrepareDone::~PrepareDone() {}

  std::string PrepareDone::getStateName() const {
    return std::string("PrepareDone");
  }

  boost::statechart::result PrepareDone::react(const EvFromPlanning& EvFromPlanning) {
    if (context<Carstate>().planning_state() == 1) {
      context<Carstate>().SetcarState(3);
      return transit<NormalRun>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3