#pragma once

#include <boost/mpl/list.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include "normal.hpp"

namespace cyberc3 {
namespace carstate {

  class NormalRun : public boost::statechart::simple_state<NormalRun, Normal>, public IState {
   public:
    typedef boost::mpl::list<boost::statechart::custom_reaction<EvFromPlanning>,
                             boost::statechart::custom_reaction<EvFromObstcle>,
                             boost::statechart::custom_reaction<EvFromWebEmergency>,
                             boost::statechart::custom_reaction<EvFromLocalization>,
                             boost::statechart::custom_reaction<EvFromElectricfence>>
      reactions;

    NormalRun();
    ~NormalRun();
    std::string               getStateName() const;
    boost::statechart::result react(const EvFromPlanning& EvFromPlanning);
    boost::statechart::result react(const EvFromObstcle& EvFromObstcle);
    boost::statechart::result react(const EvFromWebEmergency& EvFromWebEmergency);
    boost::statechart::result react(const EvFromLocalization& EvFromLocalization);
    boost::statechart::result react(const EvFromElectricfence& EvFromElectricfence);
  };

}  // namespace carstate
}  // namespace cyberc3