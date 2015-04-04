#include "Globals.h"
namespace Globals {
sf::Font FONT;
void init() {
    FONT.loadFromFile("pt-mono.ttf");
}
sf::Vector2i relMousePos(sf::RenderWindow& window) {
    return sf::Mouse::getPosition() - window.getPosition();
}
}
