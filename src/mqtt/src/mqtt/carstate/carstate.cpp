#include "carstate.hpp"

#include <iostream>
#include <string>

#include "state/Automatic/automatic.hpp"
#include "state/Manual/manual.hpp"
#include "state/Manual/prepare.hpp"
#include "state/istate.hpp"

namespace cyberc3 {
namespace carstate {

  Carstate::Carstate()
    : car_state_(0), planning_state_(1), webem_state_(0), obsta_state_(0), autobutton_state_(0), hardware_state_(0), localization_state_(0), electricfence_state_(0) {
    std::cout << "Construct Carstate" << std::endl;
  }

  Carstate::~Carstate() {
    std::cout << "Destruct Carstate" << std::endl;
  }

  std::string Carstate::get_state() const {
    return std::string("CurrentState ------> ") + state_cast<const IState&>().getStateName() + "  state code: " + std::to_string(car_state_);
  }

}  // namespace carstate
}  // namespace cyberc3
