#include "carstate.hpp"

#include <iostream>

#include "state/Manual/manual.hpp"
#include "state/Manual/prepare.hpp"

int main() {
  cyberc3::carstate::Carstate Carstate;

  Carstate.initiate();
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_auto(1);
  Carstate.process_event(cyberc3::carstate::EvFromCar());  //模拟按 EvFromCar
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_planning(1);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl << std::endl << std::endl;

  std::cout << "[test] 云端急停" << std::endl;
  Carstate.set_webemergency(1);
  Carstate.process_event(cyberc3::carstate::EvFromWebEmergency());  //模拟按 webEmergency
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_webemergency(0);
  Carstate.process_event(cyberc3::carstate::EvFromWebEmergency());  //模拟按 webEmergencyd
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_planning(1);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl << std::endl << std::endl;
  // normal

  std::cout << "[test] 定位失效" << std::endl;
  Carstate.set_localization(0);
  Carstate.process_event(cyberc3::carstate::EvFromLocalization());  //模拟 localization_state_ = 0
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_localization(1);
  Carstate.process_event(cyberc3::carstate::EvFromLocalization());  //模拟按 EvFromLocalization
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_localization(0);
  Carstate.process_event(cyberc3::carstate::EvFromLocalization());  //模拟按 EvFromLocalization
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_planning(1);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl << std::endl << std::endl;
  // normal

  std::cout << "[test] 电子围栏保护" << std::endl;
  Carstate.set_electricfence(0);
  Carstate.process_event(cyberc3::carstate::EvFromElectricfence());  //模拟 electricfence_state_ = 0
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_electricfence(1);
  Carstate.process_event(cyberc3::carstate::EvFromElectricfence());  //模拟 electricfence_state_ = 1
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_electricfence(0);
  Carstate.process_event(cyberc3::carstate::EvFromElectricfence());  //模拟 electricfence_state_ = 0
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_planning(1);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl << std::endl << std::endl;
  // normal

  std::cout << "[test] 检测到障碍物停车" << std::endl;
  Carstate.set_obstacle(0);
  Carstate.process_event(cyberc3::carstate::EvFromObstcle());  //模拟 obsta_state_ = 0 没有问题
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_obstacle(1);
  Carstate.process_event(cyberc3::carstate::EvFromObstcle());  //模拟按 EvFromObstcle
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_obstacle(0);
  Carstate.process_event(cyberc3::carstate::EvFromObstcle());  //模拟按 EvObstacleDisappear
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_planning(1);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl << std::endl << std::endl;
  // normal

  std::cout << "[test] 到达站点" << std::endl;
  Carstate.set_planning(0);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 0
  std::cout << Carstate.get_state() << std::endl;
  // 到达站点

  std::cout << "[test] 未设置站点" << std::endl;
  Carstate.set_planning(2);
  Carstate.process_event(cyberc3::carstate::EvFromPlanning());  //模拟按 EvFromPlanning 0
  std::cout << Carstate.get_state() << std::endl;
  // 未设置站点

  std::cout << "[test] 硬件检测" << std::endl;
  Carstate.set_hardware(1);
  Carstate.process_event(cyberc3::carstate::EvFromHardware());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl;

  Carstate.set_hardware(0);
  Carstate.process_event(cyberc3::carstate::EvFromHardware());  //模拟按 EvFromPlanning 1
  std::cout << Carstate.get_state() << std::endl;
  // mew

  return 0;
}