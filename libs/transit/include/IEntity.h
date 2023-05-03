#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <list>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IObserver.h"


using namespace routing;

/**
 * @class IEntity
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity {
 public:
  /**
   * @brief Constructor that assigns a unique ID to the entity.
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }

  /**
   * @brief Virtual destructor for IEntity.
   */
  virtual ~IEntity() { delete graph; }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Gets the destination of the entity.
   * @return The destination of the entity.
   */
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  virtual std::string GetColor() const { return "None"; }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual float GetSpeed() const = 0;

  /**
   * @brief Gets the availability of the entity.
   * @return The availability of the entity.
   */
  virtual bool GetAvailability() const {}

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  virtual std::string GetStrategyName() const {}

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  virtual void SetStrategyName(std::string strategyName_) {}

  /**
   * @brief Sets the availability of the entity.
   * @param choice The desired availability of the entity.
   */
  virtual void SetAvailability(bool choice) {}

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   * @param scheduler The list of all entities in the system.
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}

  /**
   * @brief Sets the graph object used by the entity in the simulation.
   * @param graph The IGraph object to be used.
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void SetPosition(Vector3 pos_) {}

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void SetDirection(Vector3 dir_) {}

  /**
   *@brief Set the destination of the entity.
   *@param des_ The new destination of the entity.
   */
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  virtual void SetColor(std::string col_) {}

  /**
   * @brief Rotate the entity.
   * @param angle The angle to rotate the entity by.
   */
  virtual void Rotate(double angle) {}

  /**
   * @brief Make the entity jump.
   * @param height The height to make the entity jump.
   */
  virtual void Jump(double height) {}

  /**
   * @brief Generates a random float between min and max values
   * @param Min Minimum value of the random float.
   * @param Max Maximum value of the random float.
   * @return Random float between Min and Max.
   */
  virtual float Random(float Min, float Max) {
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
  }

  /**
   * @brief Attaches an IObserver object to the Observable object.
   * @param observer The IObserver object to attach.
   */
  void Attach(IObserver *observer){
    list_observer_.push_back(observer);
  }

  /**
   * @brief Detaches an IObserver object from the Observable object.
   * @param observer The IObserver object to detach.
   */
  void Detach(IObserver *observer){
    list_observer_.remove(observer);
  }

  /**
   * @brief Notifies all attached IObserver objects that the object's state has changed.
   */
  void Notify(){
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    while (iterator != list_observer_.end()) {
      (*iterator)->Update(message_);
      ++iterator;
    }
  }

  /**
   * @brief Creates a message to be sent to all attached IObserver objects.
   * @param message The message to be sent. Defaults to "Empty".
   */
  void CreateMessage(std::string message = "Empty") {
    this->message_ = message;
    Notify();
  }

  /**
   * @brief Prints the number of attached IObserver objects.
   */
  void HowManyObserver() {
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }

  /**
   * @brief Gets the number of drones.
   * @return Number of drones.
   */
  int getNum(){
    return num;
  }

  /**
   * @brief Sets the number of drones.
   * @param n Number of drones.
   */
  int setNum(int n){
    num = n;
  }

 protected:
  int id;
  const IGraph* graph;
  int num;

 private:
  std::list<IObserver *> list_observer_;
  std::string message_;
};

#endif
