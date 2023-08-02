#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "../automatic.hpp"

namespace cyberc3 {
namespace carstate {

  class HardwareDefault;

  class Error : public boost::statechart::simple_state<Error, Automatic, HardwareDefault>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromHardware> reactions;

    Error();
    ~Error();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromHardware& EvFromHardware);
  };

}  // namespace carstate
}  // namespace cyberc3