#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "../automatic.hpp"

namespace cyberc3 {
namespace carstate {

  class PrepareDone;

  class Normal : public boost::statechart::simple_state<Normal, Automatic, PrepareDone>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromHardware> reactions;

    Normal();
    ~Normal();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromHardware& EvFromHardware);
  };

}  // namespace carstate
}  // namespace cyberc3