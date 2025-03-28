#include <SFML/Graphics.hpp>
#include "layout.hpp"
#include "system_manager.hpp"
#include "game.hpp"

using namespace WVM;

std::shared_ptr<Layout> generate_random_layout(size_t x_size, size_t y_size);

void draw_layout(sf::RenderWindow& window, Layout& layout);

std::shared_ptr<Layout> setup_layout_big();
std::shared_ptr<Layout> setup_layout_smoll();
std::shared_ptr<Layout> setup_layout_huge();

void draw_entities(sf::RenderWindow& window, Game&);
void draw_castle_info(sf::RenderWindow& window, Castle& );