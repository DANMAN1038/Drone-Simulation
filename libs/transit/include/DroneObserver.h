#ifndef DRONEOBSERVER_H_
#define DRONEOBSERVER_H_
#include "Drone.h"

class DroneObserver : public IObserver {
 public:
  DroneObserver(Drone &subject) : subject_(subject) {
    this->subject_.Attach(this);
    std::cout << "Hi, I'm the Drone Observer \"" << ++DroneObserver::static_number_ << "\".\n";
    this->number_ = DroneObserver::static_number_;
  }
  virtual ~DroneObserver() {
    std::cout << "Goodbye, I was the Drone Observer \"" << this->number_ << "\".\n";
  }

  void Update(const std::string &message_from_subject) override {
    message_from_subject_ = message_from_subject;
    PrintInfo();
  }
  void RemoveMeFromTheList() {
    subject_.Detach(this);
    std::cout << "Drone Observer \"" << number_ << "\" removed from the list.\n";
  }
  void PrintInfo() {
    std::cout << "Drone Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
  }

#endif
