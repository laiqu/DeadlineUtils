#pragma once 
#include <memory>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Content.h"
class GridWorld {
    sf::RenderWindow* window;
    sf::Vector2f view_position;    
    std::vector<std::function<void(sf::Vector2i)>> onHovers;
    std::map<sf::Mouse::Button, std::function<void(sf::Vector2i)>> onClicks;
    std::map<sf::Mouse::Button, bool> pushed;
protected:
    sf::Color default_color;
    sf::Color default_outline;
    sf::Font font;
    float cell_size;
    float scale;
    std::vector<std::function<Content(sf::Vector2i, float, float)>> cellContents;
private:
    sf::Vector2i pos2index (sf::Vector2f pos) {
        float curr_cell_size = cell_size * scale;     
        pos /= curr_cell_size;
        return sf::Vector2i({(int)std::floor(pos.x), -(int)std::ceil(pos.y)});
    }
    void draw ();
    void handleMouse (sf::Vector2i index) {
        if (window->hasFocus()) {
            for (auto& cb : onHovers) {
               cb(index); 
            }
            for (auto& kv : pushed) {
                bool button_push = sf::Mouse::isButtonPressed(kv.first);
                if (button_push == false && kv.second == true) {
                    onClicks[kv.first](index); 
                }
                kv.second = button_push;
            }
        }
    }
    void handleKeys () {
        float move_speed = 5.0f;
        if (window->hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                move_speed *= 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { 
                move_speed *= 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                move({-move_speed, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                move({move_speed, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                move({0, move_speed});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                move({0, -move_speed});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
                increaseScale(0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
                decreaseScale(0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
                setScale(1);
            }
        }
    }
public:
    GridWorld (sf::RenderWindow* window,
            sf::Font font,
            sf::Vector2f view_position = sf::Vector2f({0, 0}),
            sf::Color default_color = sf::Color(0, 0, 0),
            sf::Color default_outline = sf::Color::Cyan,
            float cell_size = 30.0f,
            float scale = 1.0f) :
        window (window),
        font (font),
        view_position (view_position),
        default_color (default_color),
        default_outline (default_outline),
        cell_size (cell_size),
        scale (scale) { }

    void move (sf::Vector2f vec) {
        view_position += vec * (1/scale);  
    }

    void increaseScale (float inc) {
        scale += inc;
    }

    void decreaseScale (float dec) {
       scale -= dec;
    }

    void setScale (float new_scale) {
       scale = new_scale;
    }

    void update () {
        handleKeys();
        draw();
    }

    /*  Provided function is called per every visible cell.
     *  Function args:
     *      sf::Vector2i - cell index,
     *      float        - current grid scale,
     *      float        - cell size
     *  Function return value:
     *      Content      - Shape/Text/Sprite... which will be moved to
     *                     cell position.
     *  Order of adding callbacks, is the order of drawing.
     */
    void addCellContent(std::function<Content(sf::Vector2i, float, float)> content) {
        cellContents.push_back(content);
    }

    /* Function is called with index of cell which is currently under
     * mouse cursor.
     * Function args:
     *      sf::Vector2i - cell index
     * Function return value:
     *      void
     */
    void addOnHover (std::function<void(sf::Vector2i)> cb) {
        onHovers.push_back(cb);
    }

    /* Function is called with index of cell which was clicked by given
     * mouse key
     * Function args:
     *      sf::Vector2i - cell index
     * Function return value:
     *      void
     * Note: because I'm lazy it's actually onMouseRelease, not real on click
     */
    void addOnClick (std::function<void(sf::Vector2i)> cb, sf::Mouse::Button button) {
        onClicks[button] = cb;
        pushed[button] = sf::Mouse::isButtonPressed(button); 
    }
};

namespace Contents {
Content indexNumber(sf::Vector2i index, float scale, float cell_size);
}
namespace Callbacks {
void cellIndex(sf::Vector2i index);
}
