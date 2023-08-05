#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "../../carstate.hpp"
#include "../../event/events.hpp"
#include "../istate.hpp"
namespace cyberc3 {
namespace carstate {

  class Normal;
  // NormalRun Normal
  class Automatic : public boost::statechart::simple_state<Automatic, Carstate, Normal>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromCar> reactions;

    Automatic();
    ~Automatic();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromCar& EvFromCar);
  };

}  // namespace carstate
}  // namespace cyberc3