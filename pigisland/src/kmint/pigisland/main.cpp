#include "kmint/main.hpp" // voor de main loop
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/wall.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/island.hpp"

#include "kmint/play.hpp"
#include "kmint/ui.hpp"


using namespace kmint;
int main() {
  // een app object is nodig om
  ui::app app{};

  //  maak een venster aan
  ui::window window{app.create_window({1024, 768}, "hello")};

  // maak een podium aan
  play::stage s{};

  auto map = pigisland::map();
  map.graph()[0].tagged(true);
  s.build_actor<play::background>(math::size(1024, 768),
                                  graphics::image{map.background_image()});

  

  auto& shark = s.build_actor<pigisland::shark>(map.graph());
  auto& boat = s.build_actor<pigisland::boat>(map.graph());

  
  s.build_actor<play::map_actor>(math::vector2d{ 0.f, 0.f }, map.graph());

  //borders
  s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 750.0f },pigisland::wall::Face::NORTH);
  s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 10.0f }, pigisland::wall::Face::SOUTH);
  s.build_actor<pigisland::wall>(math::vector2d{ .0f, 325.0f }, pigisland::wall::Face::EAST);
  s.build_actor<pigisland::wall>(math::vector2d{ 1020.0f, 325.0f }, pigisland::wall::Face::WEST);

  //right top island
  s.build_actor<pigisland::island>(math::vector2d{ 990.0f, 0.0f }, 80);
  s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 100.0f }, 30);
  s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 50.0f }, 30);

  //bottom right island
  s.build_actor<pigisland::island>(math::vector2d{ 925.0f, 750.0f }, 125);
  s.build_actor<pigisland::island>(math::vector2d{ 1010.0f, 625.0f }, 50);
  s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 625.0f }, 30);
  s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 575.0f }, 30);

  //bottom left island
  s.build_actor<pigisland::island>(math::vector2d{ 125.0f, 625.0f }, 75);
  s.build_actor<pigisland::island>(math::vector2d{ 125.0f, 625.0f }, 75);
  s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 575.0f }, 15);

  //top left island
  s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 0.0f }, 100);
  s.build_actor<pigisland::island>(math::vector2d{ 100.0f, 0.0f }, 100);
  s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 45.0f }, 30);
  s.build_actor<pigisland::island>(math::vector2d{ 225.0f, 45.0f }, 30);
  s.build_actor<pigisland::island>(math::vector2d{ 275.0f, 45.0f }, 30);

  //statue
  s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 680.0f }, 50);





  for (int i = 0; i < 100; ++i) {
    s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f),1,1,1,.05,-1,1, map.graph(),shark,boat);
	//s.build_actor<pigisland::pig>(math::vector2d(1010.0f, 625.0f), 1, 1, 1, .05, -1, 1, map.graph(), shark, boat);
  }
  

  // Maak een event_source aan (hieruit kun je alle events halen, zoals
  // toetsaanslagen)
  ui::events::event_source event_source{};

  // main_loop stuurt alle actors aan.
  main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
    // gebruik dt om te kijken hoeveel tijd versterken is
    // sinds de vorige keer dat deze lambda werd aangeroepen
    // loop controls is een object met eigenschappen die je kunt gebruiken om de
    // main-loop aan te sturen.

    for (ui::events::event &e : event_source) {
      // event heeft een methode handle_quit die controleert
      // of de gebruiker de applicatie wilt sluiten, en zo ja
      // de meegegeven functie (of lambda) aanroept om met het
      // bijbehorende quit_event
      //
      e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
    }
  });
}
