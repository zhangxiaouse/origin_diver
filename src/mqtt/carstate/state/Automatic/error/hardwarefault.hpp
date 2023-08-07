#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "error.hpp"

namespace cyberc3 {
namespace carstate {

  class HardwareDefault : public boost::statechart::simple_state<HardwareDefault, Error>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromHardware> reactions;

    HardwareDefault();
    ~HardwareDefault();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromHardware& EvFromHardware);
  };

}  // namespace carstate
}  // namespace cyberc3