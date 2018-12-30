#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <map>
//#include "../../../../dependencies/SDL2/include/SDL_opengles2_gl2ext.h"

//class MovingActor;

namespace kmint {
namespace pigisland {

class SteeringBehaviors;
class shark;
class boat;

class pig : public play::free_roaming_actor{
public:
enum Forces{
  WANDER,
  ALIGNMENT,
  COHESION,
  SEPARATION,
  ATTRACTIONTOSHARK,
  ATTRACTIONTOBOAT
  };

  explicit pig(math::vector2d location,
	  double wanderForce, double alignmentForce, double separationForce, double cohesionForce, double attractionToShark,double attractionToBoat
	  ,map::map_graph& graph, shark& shark, boat& boat);

  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceptive() const override { return !caught_; }
  bool perceivable() const override { return !caught_; }
  bool must_draw() const override { return !caught_; }
  scalar range_of_perception() const override { return 50.0f; }
  scalar radius() const override { return 8.0f; }
  bool incorporeal() const override { return false; }
  math::vector2d heading() const override { return heading_; }
  void setLocation(math::vector2d newLocation) { location(newLocation); }

  map::map_node* const getClosestNode() const;

  const std::vector<const pig*> getNeighbours();

  shark* getShark() const { return &shark_; }
  boat* getBoat() const { return &boat_; }

  double getMass() const { return mass; }
  double getMaxSpeed() const { return maxSpeed; }

  double getWanderRadius() const { return wanderRadius; }
  double getWanderDistance() const { return wanderDistance; }
  double getWanderJitter() const { return wanderJitter; }
 
  std::map<Forces, double> getDNA() { return dna_; }
  //void setDna(double alignment, double cohesion, double separation, double attractionToShark, double attractionToBoat);
  
  bool alive() const { return alive_; }
  bool caught() const { return caught_; }
  delta_time timeAlive() const { return timeAlive_; }
  void revive(math::vector2d newLocation,double alignment, double cohesion, double separation, double attractionToShark, double attractionToBoat);
  void die();
  void spliceDNA(pig papa, pig mama);

private:
  bool caught_ = false;
  bool alive_ = true;
  delta_time timeAlive_;
  double calculateDistance(const map::map_node& mapNode) const;
  //void handleCollision(actor * collider);
  void checkCollision(delta_time dt);
  
  play::image_drawable drawable_;
  map::map_graph& _graph;

  shark& shark_;
  boat& boat_;
  SteeringBehaviors* steeringBehavior;
  math::vector2d velocity = math::vector2d(0, 0);
  math::vector2d heading_ = math::vector2d(0,0);
  
  double mass = 1;
  double maxSpeed = 5;
  double wanderRadius = 5;
  double wanderDistance = 1;
  double wanderJitter = .1;

  std::map<Forces, double> dna_;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
