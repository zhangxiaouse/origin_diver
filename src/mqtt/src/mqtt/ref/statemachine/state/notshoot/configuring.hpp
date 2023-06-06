#ifndef __CONFIGURING_HPP__
#define __CONFIGURING_HPP__

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: NotShooting is the context of Configuring, so
//   full definition of NotShooting is needed when defining Configuring, thus
//   include notshooting.hpp here;
#include "notshooting.hpp"

// Yuanguo: full definition of Idle is needed in line
//      typedef transition< EvConfig, Idle >
#include "idle.hpp"

using namespace boost::statechart;

class Configuring : public simple_state<Configuring, NotShooting>, public IState {
 public:
  // Yuanguo: a short way for:
  //      typedef custom_reaction< EvConfig > reactions;
  //      result react( const EvConfig & evConfig)
  //      {
  //        return transit< Idle >(&Camera::powerSavingMode, evConfig);
  //        //transition action is Camera::powerSavingMode()
  //      }
  typedef transition<EvConfig, Idle, Camera, &Camera::powerSavingMode> reactions;  // transition action is Camera::powerSavingMode()

  Configuring();
  ~Configuring();
  string getStateName() const;
};

#endif