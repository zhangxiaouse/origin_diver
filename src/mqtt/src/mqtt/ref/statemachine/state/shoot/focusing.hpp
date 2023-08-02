#ifndef __FOCUSING_HPP__
#define __FOCUSING_HPP__

#include <boost/mpl/list.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>
#include <boost/statechart/simple_state.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: Shooting is the context of Focusing, so
//   full definition of Shooting is needed when defining Focusing, thus include
//   shooting.hpp here;
#include "shooting.hpp"

using namespace boost::statechart;

class Focusing : public simple_state<Focusing, Shooting>, public IState {
 public:
  // Yuanguo:
  // if the user fully press shutter when the camera is still in focusing (has
  // not focused yet), we defer the event until focused.
  // that means:
  // when an event of EvShutterFull comes:
  //    copy the EvShutterFull event by copy-constructor;
  //    put the copy in a separated queue;
  //    destruct the EvShutterFull event;
  // when camera exits Focusing state (e.g. gets into Focused state):
  //    let Focused state process the events in the queue;
  //    empty the queue and destruct the copied events;
  typedef boost::mpl::list<custom_reaction<EvInFocus>, deferral<EvShutterFull> > reactions;

  Focusing();
  ~Focusing();
  string getStateName() const;
  result react(const EvInFocus& evInFocus);
};

#endif