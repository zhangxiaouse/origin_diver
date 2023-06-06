#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class PrepareDone : public boost::statechart::simple_state<PrepareDone, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromPlanning> reactions;

    PrepareDone();
    ~PrepareDone();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromPlanning& EvFromPlanning);
  };

}  // namespace carstate
}  // namespace cyberc3
