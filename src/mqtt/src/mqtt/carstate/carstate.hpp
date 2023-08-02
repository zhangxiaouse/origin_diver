
#pragma once

#include <boost/statechart/state_machine.hpp>

#include "event/events.hpp"

namespace cyberc3 {
namespace carstate {
  class Manual;

  class Carstate : public boost::statechart::state_machine<Carstate, Manual> {
   public:
    Carstate();
    ~Carstate();

    inline int carState() const {
      return car_state_;
    }
    inline void SetcarState(int state) {
      car_state_ = state;
    };

    inline int planning_state() const {
      return planning_state_;
    };
    inline int webemergency_state() const {
      return webem_state_;
    };
    inline int obstacle_state() const {
      return obsta_state_;
    };
    inline int auto_state() const {
      return autobutton_state_;
    };
    inline int hardware_state() const {
      return hardware_state_;
    };
    inline int localization_state() const {
      return localization_state_;
    };
    
    inline int electricfence_state() const {
      return electricfence_state_;
    };

    inline void set_planning(int state) {
      planning_state_ = state;
    };
    inline void set_webemergency(int state) {
      webem_state_ = state;
    };
    inline void set_obstacle(int state) {
      obsta_state_ = state;
    };
    inline void set_auto(int state) {
      autobutton_state_ = state;
    };
    inline void set_hardware(int state) {
      hardware_state_ = state;
    };
    inline void set_localization(int state) {
      localization_state_ = state;
    };
    inline void set_electricfence(int state) {
      electricfence_state_ = state;
    };
    std::string get_state() const;

   private:
    int car_state_;

    int planning_state_;
    int webem_state_;
    int obsta_state_;
    int autobutton_state_;
    int hardware_state_;
    int localization_state_;
    int electricfence_state_;
  };

}  // namespace carstate
}  // namespace cyberc3