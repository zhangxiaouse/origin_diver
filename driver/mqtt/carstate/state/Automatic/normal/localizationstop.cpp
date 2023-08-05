#include "localizationstop.hpp"

#include "preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  LocalizationStop::LocalizationStop() {
    std::cout << "Enter LocalizationStop 定位失效 " << std::endl;
  }

  LocalizationStop::~LocalizationStop() {}

  std::string LocalizationStop::getStateName() const {
    return std::string("LocalizationStop");
  }

  boost::statechart::result LocalizationStop::react(const EvFromLocalization& EvFromLocalization) {
    if (context<Carstate>().localization_state() == 0) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3