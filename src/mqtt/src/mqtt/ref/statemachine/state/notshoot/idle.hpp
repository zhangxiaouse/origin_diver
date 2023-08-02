#ifndef __IDLE_HPP__
#define __IDLE_HPP__

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: Idle is the initial state of NotShooting, and NotShooting is the
// context of Idle, so
//  1. forward declaration of Idle is needed when defining NotShooting, see
//  notshooting.hpp;
//  2. full definition of NotShooting is needed when defining Idle, thus include
//  notshooting.hpp here;
#include "notshooting.hpp"

using namespace boost::statechart;

class Idle : public simple_state<Idle, NotShooting>, public IState {
 public:
  typedef custom_reaction<EvConfig> reactions;

  Idle();
  ~Idle();
  string getStateName() const;
  result react(const EvConfig& evConfig);
};

#endif