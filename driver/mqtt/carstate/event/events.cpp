#include "events.hpp"

#include <iostream>

namespace cyberc3 {
namespace carstate {

  //============EvFromCar============//
  EvFromCar::EvFromCar() {
    // std::cout << "Construct EvFromCar cmd" << std::endl;
  }
  EvFromCar::~EvFromCar() {
    // std::cout << "Destruct EvFromCar cmd" << std::endl;
  }

  //============EvFromObstcle============//
  EvFromObstcle::EvFromObstcle() {
    // std::cout << "Construct EvFromObstcle cmd" << std::endl;
  }

  EvFromObstcle::~EvFromObstcle() {
    // std::cout << "Destruct EvFromObstcle cmd" << std::endl;
  }

  //============EvFromWebEmergency============//
  EvFromWebEmergency::EvFromWebEmergency() {
    // std::cout << "Construct EvFromWebEmergency cmd" << std::endl;
  }
  EvFromWebEmergency::~EvFromWebEmergency() {
    // std::cout << "Destruct EvFromWebEmergency cmd" << std::endl;
  }

  //============EvFromPlanning============//
  EvFromPlanning::EvFromPlanning() {
    // std::cout << "Construct EvFromPlanning cmd" << std::endl;
  }
  EvFromPlanning::~EvFromPlanning() {
    // std::cout << "Destruct EvFromPlanning  cmd" << std::endl;
  }

  //============EvFromHardware============//
  EvFromHardware::EvFromHardware() {
    // std::cout << "Construct EvFromHardware cmd" << std::endl;
  }
  EvFromHardware::~EvFromHardware() {
    // std::cout << "Destruct EvFromHardware  cmd" << std::endl;
  }

  //============EvFromLocalization============//
  EvFromLocalization::EvFromLocalization() {
    // std::cout << "Construct EvFromLocalization cmd" << std::endl;
  }
  EvFromLocalization::~EvFromLocalization() {
    // std::cout << "Destruct EvFromLocalization  cmd" << std::endl;
  }
  //============EvFromelectricfence============//
  EvFromElectricfence::EvFromElectricfence() {
    // std::cout << "Construct EvFromLocalization cmd" << std::endl;
  }
  EvFromElectricfence::~EvFromElectricfence() {
    // std::cout << "Destruct EvFromLocalization  cmd" << std::endl;
  }

}  // namespace carstate
}  // namespace cyberc3