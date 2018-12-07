#ifndef KMINT_PIGISLAND_RESOURCES_HPP
#define KMINT_PIGISLAND_RESOURCES_HPP

#include "kmint/graphics.hpp"
#include "kmint/map/map.hpp"

namespace kmint {
namespace pigisland {

map::map map();
graphics::image shark_image();
graphics::image pig_image();
graphics::image boat_image();

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_RESOURCES_HPP */
