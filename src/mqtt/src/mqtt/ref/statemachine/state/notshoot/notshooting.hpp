#ifndef __NOTSHOOTING_HPP__
#define __NOTSHOOTING_HPP__

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: NotShooting is the initial state of Camera, and Camera is the
// context of NotShooting, so
//  1. forward declaration of NotShooting is needed when defining Camera, see
//  camera.hpp;
//  2. full definition of Camera is needed when defining NotShooting, thus
//  include camera.hpp here;
#include "../../camera/camera.hpp"

using namespace boost::statechart;

// Yuanguo: forward declaration;
class Idle;

class NotShooting : public simple_state<NotShooting, Camera, Idle>, public IState {
 public:
  typedef custom_reaction<EvShutterHalf> reactions;

  NotShooting();
  ~NotShooting();
  string getStateName() const;
  result react(const EvShutterHalf& evShutterHalf);
};

#endif