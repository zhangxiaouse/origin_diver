#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class ObstacleStop : public boost::statechart::simple_state<ObstacleStop, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromObstcle> reactions;

    ObstacleStop();
    ~ObstacleStop();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromObstcle& EvFromObstcle);
  };

}  // namespace carstate
}  // namespace cyberc3
