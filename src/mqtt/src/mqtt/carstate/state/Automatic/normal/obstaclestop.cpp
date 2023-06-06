#include "obstaclestop.hpp"

#include "preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  ObstacleStop::ObstacleStop() {
    std::cout << "Enter ObstacleStop 车辆遇到障碍物停车  " << std::endl;
  }

  ObstacleStop::~ObstacleStop() {}

  std::string ObstacleStop::getStateName() const {
    return std::string("ObstacleStop");
  }

  boost::statechart::result ObstacleStop::react(const EvFromObstcle& EvFromObstcle) {
    if (context<Carstate>().obstacle_state() == 0 || context<Carstate>().planning_state() == 0 || context<Carstate>().planning_state() == 2) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3