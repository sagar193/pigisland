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

  double getMass() const { return mass; }
  double getMaxSpeed() const { return maxSpeed; }
  double getMaxForce() const { return maxForce; }
  double getMaxTurnRate() const { return maxTurnRate; }
  double getWanderRadius() const { return wanderRadius; }
  double getWanderDistance() const { return wanderDistance; }
  double getWanderJitter() const { return wanderJitter; }
  kmint::math::vector2d getHeading() const { return heading; }
private:
  play::image_drawable drawable_;

  SteeringBehaviors* steeringBehavior;
  //MovingActor* movingActor;

  kmint::math::vector2d velocity = kmint::math::vector2d(0, 0);
  kmint::math::vector2d heading = kmint::math::vector2d(0,0);
  
  double mass = 50;
  double maxSpeed = .5;
  double maxForce = 1;
  double maxTurnRate = 1;
  double wanderRadius = 100;
  double wanderDistance = 10;
  double wanderJitter = 01.;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
