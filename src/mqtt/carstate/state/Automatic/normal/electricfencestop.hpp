#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class ElectricfenceStop : public boost::statechart::simple_state<ElectricfenceStop, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromElectricfence> reactions;

    ElectricfenceStop();
    ~ElectricfenceStop();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromElectricfence& EvFromElectricfence);
  };

}  // namespace carstate
}  // namespace cyberc3