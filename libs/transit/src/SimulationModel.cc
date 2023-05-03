#include "SimulationModel.h"
#include "DroneLogger.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "DroneObserver.h"

/**
   * @brief Default constructor that create the SimulationModel object
   **/
SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
}

/**
   * @brief Destructor
   */
SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
}

/**
   * @brief Creates a new simulation entitiy
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entnity to create
   **/
void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  if(type.compare("drone") == 0){
    DroneObserver *observer = new DroneObserver(*(static_cast<Drone*>(myNewEntity)), controller);
    myNewEntity->setNum(droneCounter);
    droneCounter++;
  }
  else if(type.compare("robot") == 0){
    myNewEntity->setNum(robotCounter);
    robotCounter++;
  }
  myNewEntity->SetGraph(graph);

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

 /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
  // JsonObject details2;
  // details2["info"] = "How are you doing today \n I'm doing great 1 \n";
  // controller.SendEventToView("observe",details2);
  // JsonObject details3;
  // details3["info"] = "Testing a second message \n";
  // controller.SendEventToView("observe",details3);
}

/**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);

    DroneLogger* singleton = DroneLogger::GetInstance();     // Gets one instance and logdrone information to csv file
    singleton->logDrone(entities[i]);

    controller.UpdateEntity(*entities[i]);
  }
}

/**
   * @brief Add new factory into the simulation
   * @param factory - Factory to add into the simulation.
   */
void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
