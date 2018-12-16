#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  explicit pig(math::vector2d location, kmint::map::map_graph& graph);
  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceptive() const override { return true; }
  scalar range_of_perception() const override { return 30.0f; }

  kmint::map::map_node* const getClosestNode() const;

private:
  play::image_drawable drawable_;
  kmint::map::map_graph& _graph;

  double calculateDistance(const kmint::map::map_node& mapNode) const;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
