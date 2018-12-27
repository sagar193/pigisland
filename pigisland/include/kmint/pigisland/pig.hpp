#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"

//class MovingActor;

namespace kmint {
namespace pigisland {
class SteeringBehaviors;

class pig : public play::free_roaming_actor{
public:
  explicit pig(math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceptive() const override { return true; }
  scalar range_of_perception() const override { return 30.0f; }

  std::vector<pig*> getNeighbours(double neighbourDistance);

  double getMass() const { return mass; }
  double getMaxSpeed() const { return maxSpeed; }
  double getMaxForce() const { return maxForce; }
  double getMaxTurnRate() const { return maxTurnRate; }

  double getWanderRadius() const { return wanderRadius; }
  double getWanderDistance() const { return wanderDistance; }
  double getWanderJitter() const { return wanderJitter; }
  double getWanderForce() const { return wanderForce; }

  double getCohessionForce() const { return cohessionForce; }
  double getSeperationForce() const { return seperationForce; }

  double getAlignmentForce() const { return alignmentForce; }

  double getSeperationDistance() const { return seperationDistance; }
  kmint::math::vector2d getHeading() const { return heading; }
private:
  play::image_drawable drawable_;

  SteeringBehaviors* steeringBehavior;
  kmint::math::vector2d velocity = kmint::math::vector2d(0, 0);
  kmint::math::vector2d heading = kmint::math::vector2d(0,0);
  
  double mass = 1;
  double maxSpeed = 1;
  double maxForce = 1;
  double maxTurnRate = 1;
  
  double wanderRadius = 20;
  double wanderDistance = 15;
  double wanderJitter = 1;

  double alignmentForce = 0;
  double wanderForce = 11;
  double cohessionForce = 0;
  double seperationForce = 0;
  double seperationDistance = 30;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
