#pragma once

#include <boost/statechart/event.hpp>

namespace cyberc3 {
namespace carstate {

  class EvFromCar : public boost::statechart::event<EvFromCar> {
   public:
    EvFromCar();
    ~EvFromCar();
  };

  class EvFromObstcle : public boost::statechart::event<EvFromObstcle> {
   public:
    EvFromObstcle();
    ~EvFromObstcle();
  };

  class EvFromWebEmergency : public boost::statechart::event<EvFromWebEmergency> {
   public:
    EvFromWebEmergency();
    ~EvFromWebEmergency();
  };

  class EvFromPlanning : public boost::statechart::event<EvFromPlanning> {
   public:
    EvFromPlanning();
    ~EvFromPlanning();
  };

  class EvFromHardware : public boost::statechart::event<EvFromHardware> {
   public:
    EvFromHardware();
    ~EvFromHardware();
  };

  class EvFromLocalization : public boost::statechart::event<EvFromLocalization> {
   public:
    EvFromLocalization();
    ~EvFromLocalization();
  };

  class EvFromElectricfence : public boost::statechart::event<EvFromElectricfence> {
   public:
    EvFromElectricfence();
    ~EvFromElectricfence();
  };
}  // namespace carstate
}  // namespace cyberc3