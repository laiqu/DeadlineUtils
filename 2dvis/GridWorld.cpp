#include "Globals.h"
#include "GridWorld.h"
#include <iostream>
inline float realmod(float x, float y) {
    float t = std::fmod(x, y);
    return t >= 0 ? t : t + y;
}
void GridWorld::draw () {
    float curr_cell_size = cell_size * scale;
    sf::Vector2f curr_view = view_position * scale;
    sf::Vector2f window_size = window->getView().getSize(); 
    int x_cells = (int)window_size.x / curr_cell_size + 3;
    int y_cells = (int)window_size.y / curr_cell_size + 3;
    for (int i = -3; i < x_cells; i++) {
        for (int j = -3; j < y_cells; j++) {
            sf::Vector2f rel_pos({i * curr_cell_size, j * curr_cell_size});
            sf::Vector2f pos = rel_pos;
            pos.x += curr_view.x;
            pos.y += -curr_view.y;
            sf::RectangleShape cell({curr_cell_size, curr_cell_size});
            cell.setPosition(rel_pos);
            cell.setFillColor(default_color);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(default_outline);
            cell.move(-realmod(curr_view.x, curr_cell_size),
                     realmod(curr_view.y, curr_cell_size));
            sf::Vector2i index = pos2index(pos);
            window->draw(cell);
            for (auto& cellContent : cellContents) {
                Content content(cellContent(index, scale, cell_size));
                if (content.hasContent()) {
                    content.getTransformable()->move(cell.getPosition());
                    window->draw(*content.getDrawable());
                }
            }
        }
    }
    sf::Vector2i rel_mouse = Globals::relMousePos(*window);
    sf::Vector2i mouse_index(pos2index(
                curr_view +
                sf::Vector2f(rel_mouse.x, -rel_mouse.y) 
            ));
    mouse_index.y *= -1;
    handleMouse(mouse_index);
}

Content Contents::indexNumber(sf::Vector2i index, float scale, float cell_size) {
    sf::Text* index_text = new sf::Text(std::to_string(index.x) + " " +
                  std::to_string(index.y), Globals::FONT);
    float font_size = cell_size / 3 * scale;
    font_size = font_size > 12 ? 12 : font_size;
    index_text->setCharacterSize(font_size);
    return Content(index_text);
} 

