#include "CelebrationDecorator.h"

/**
   * @brief Construct a new Celebration Decorator object
   *
   * @param strategy the strategy to decorate onto
   */
CelebrationDecorator::CelebrationDecorator(IStrategy* strategy){
    this->strategy = strategy;
    time = 0;
}

 /**
   * @brief Celebration Destructor
   */
CelebrationDecorator::~CelebrationDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

/**
   * @brief Check if the movement is completed by checking the time.
   *
   * @return True if complete, false if not complete
   */
bool CelebrationDecorator::IsCompleted(){
  if(time >= 4.0){
    return true;
  } else {
    return false;
  }
}

