#ifndef __SHOOTING_HPP__
#define __SHOOTING_HPP__

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: Camera is the context of Shooting, so
//  full definition of Camera is needed when defining Shooting, thus include
//  camera.hpp here;
#include "../../camera/camera.hpp"

using namespace boost::statechart;

// Yuanguo: forward declaration
class Focusing;

class Shooting : public simple_state<Shooting, Camera, Focusing>, public IState {
 public:
  typedef custom_reaction<EvShutterRelease> reactions;

  Shooting();
  ~Shooting();
  string getStateName() const;
  result react(const EvShutterRelease& evShutterRelease);
};

#endif