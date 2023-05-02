#include "HumanFactory.h"

/**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
IEntity* HumanFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("human") == 0) {
    std::cout << "Human Created" << std::endl;
    return new Human(entity);
  }
  return nullptr;
}
