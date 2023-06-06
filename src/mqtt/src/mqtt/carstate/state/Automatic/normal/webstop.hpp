#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class WebStop : public boost::statechart::simple_state<WebStop, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromWebEmergency> reactions;

    WebStop();
    ~WebStop();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromWebEmergency& EvFromWebEmergency);
  };

}  // namespace carstate
}  // namespace cyberc3