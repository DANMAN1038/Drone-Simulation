#include "HelicopterFactory.h"

/**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
IEntity* HelicopterFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("helicopter") == 0) {
    std::cout << "Helicopter Created" << std::endl;
    return new Helicopter(entity);
  }
  return nullptr;
}
