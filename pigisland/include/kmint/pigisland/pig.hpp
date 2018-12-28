#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"

//class MovingActor;

namespace kmint {
namespace pigisland {
class SteeringBehaviors;
class shark;
class boat;
class pig : public play::free_roaming_actor{
public:
  explicit pig(math::vector2d location, kmint::map::map_graph& graph, kmint::pigisland::shark& shark, kmint::pigisland::boat& boat);
  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceptive() const override { return alive_; }
  bool perceivable() const override { return alive_; }
  bool must_draw() const override { return alive_; }
  scalar range_of_perception() const override { return 30.0f; }
  scalar radius() const override { return 8.0f; }
  bool incorporeal() const override { return false; }
  void die();

  kmint::map::map_node* const getClosestNode() const;

  std::vector<pig*> getNeighbours(double neighbourDistance);

  shark* getShark() const { return &shark_; }
  boat* getBoat() const { return &boat_; }

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

  double getAttractionToShark() const { return attractionToShark; }
  double getAttractionToBoat() const { return attractionToBoat; }
  
  kmint::math::vector2d getHeading() const { return heading; }

private:
  bool alive_ = true;


  play::image_drawable drawable_;
  kmint::map::map_graph& _graph;

  double calculateDistance(const kmint::map::map_node& mapNode) const;

  shark& shark_;
  boat& boat_;

  SteeringBehaviors* steeringBehavior;
  kmint::math::vector2d velocity = kmint::math::vector2d(0, 0);
  kmint::math::vector2d heading = kmint::math::vector2d(0,0);
  
  void handleCollision();

  double mass = 1;
  double maxSpeed = 1;
  double maxForce = 1;
  double maxTurnRate = 1;
  
  double wanderRadius = 5;
  double wanderDistance = 1;
  double wanderJitter = .1;

  double alignmentForce = 1;
  double wanderForce = 1;
  double cohessionForce = .05;
  double seperationForce = 0.001;
  double attractionToShark = 1;
  double attractionToBoat = 1;

  double seperationDistance = 30;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
