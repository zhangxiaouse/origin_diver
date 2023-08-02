#ifndef __STORING_HPP__
#define __STORING_HPP__

#include <boost/mpl/list.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>
#include <boost/statechart/simple_state.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

// Yuanguo: Shooting is the context of Storing, so
//   full definition of Shooting is needed when defining Storing, thus include
//   shooting.hpp here;
#include "shooting.hpp"

using namespace boost::statechart;

class Storing : public simple_state<Storing, Shooting>, public IState {
 public:
  // Yuanguo: we have multiple reactions for different events;
  // 存在多个事件，可以转移到多个状态 需要多个 reaction
  typedef boost::mpl::list<custom_reaction<EvStored>, custom_reaction<EvShutterRelease> > reactions;

  Storing();
  ~Storing();
  string getStateName() const;
  result react(const EvStored& evStored);
  result react(const EvShutterRelease& evShutterRelease);
};

#endif