#pragma once

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "manual.hpp"

namespace cyberc3 {
namespace carstate {

  class Prepare : public boost::statechart::simple_state<Prepare, Manual>, public IState {
   public:
    typedef boost::statechart::custom_reaction<EvFromCar> reactions;

    Prepare();
    ~Prepare();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromCar& EvFromCar);
  };

}  // namespace carstate
}  // namespace cyberc3