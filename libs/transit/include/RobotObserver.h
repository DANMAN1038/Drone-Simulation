#ifndef ROBOTOBSERVER_H_
#define ROBOTOBSERVER_H_

#include "IEntity.h"
#include "Drone.h"
#include "Robot.h"
#include "IController.h"
#include "util/json.h"


class RobotObserver {
 public:

  virtual ~RobotObserver() {}
    
  virtual void Update(const std::string &message_from_subject) = 0;

  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif
