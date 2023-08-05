#include "webstop.hpp"

#include "preparedone.hpp"

namespace cyberc3 {
namespace carstate {

  WebStop::WebStop() {
    std::cout << "Enter WebStop 云端发布急停请求 " << std::endl;
  }

  WebStop::~WebStop() {}

  std::string WebStop::getStateName() const {
    return std::string("WebStop");
  }

  boost::statechart::result WebStop::react(const EvFromWebEmergency& EvFromWebEmergency) {
    if (context<Carstate>().webemergency_state() == 0) {
      context<Carstate>().SetcarState(2);
      return transit<PrepareDone>();
    } else
      return discard_event();
  }

}  // namespace carstate
}  // namespace cyberc3