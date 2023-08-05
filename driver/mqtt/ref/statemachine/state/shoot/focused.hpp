#ifndef __FOCUSED_HPP__
#define __FOCUSED_HPP__

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: Shooting is the context of Focused, so
//   full definition of Shooting is needed when defining Focused, thus include
//   shooting.hpp here;
#include "shooting.hpp"

class Focused : public simple_state<Focused, Shooting>, public IState {
 public:
  typedef custom_reaction<EvShutterFull> reactions;

  Focused();
  ~Focused();
  string getStateName() const;
  result react(const EvShutterFull& evShutterFull);
};

#endif