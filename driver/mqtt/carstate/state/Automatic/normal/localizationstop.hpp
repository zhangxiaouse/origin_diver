#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class LocalizationStop : public boost::statechart::simple_state<LocalizationStop, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromLocalization> reactions;

    LocalizationStop();
    ~LocalizationStop();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromLocalization& EvFromLocalization);
  };

}  // namespace carstate
}  // namespace cyberc3