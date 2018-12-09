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

private:
  play::image_drawable drawable_;
  SteeringBehaviors& steeringBehavior;
  //MovingActor* movingActor;

  kmint::math::vector2d velocity;
  kmint::math::vector2d heading;
  kmint::math::vector2d side;
  double mass = 50;
  double maxSpeed = 1;
  double maxForce;
  double maxTurnRate;

};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
