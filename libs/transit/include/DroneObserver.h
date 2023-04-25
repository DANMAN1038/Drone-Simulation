#ifndef DRONEOBSERVER_H_
#define DRONEOBSERVER_H_

#include "IEntity.h"
#include "Drone.h"
#include "IController.h"
#include "util/json.h"


class DroneObserver {
 public:

  virtual ~DroneObserver() {}

  virtual void Update(const std::string &message_from_subject) = 0;

  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif
