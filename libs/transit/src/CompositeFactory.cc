#include "CompositeFactory.h"

/**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
IEntity* CompositeFactory::CreateEntity(JsonObject& entity) {
  for (int i = 0; i < componentFactories.size(); i++) {
    IEntity* createdEntity = componentFactories.at(i)->CreateEntity(entity);
    if (createdEntity != nullptr) {
      return createdEntity;
    }
  }
  std::cout << "[!] Error: Type mismatched..." << std::endl;
  return nullptr;
}

 /**
   * @brief Adds given factory
   * @param factoryEntity - Factory to be added.
   **/
void CompositeFactory::AddFactory(IEntityFactory* factoryEntity) {
  componentFactories.push_back(factoryEntity);
}

 /**
   * @brief Destructor for IEntityFactory class.
   **/
CompositeFactory::~CompositeFactory() {
  for (int i = 0; i < componentFactories.size(); i++) {
    delete componentFactories[i];
  }
}
