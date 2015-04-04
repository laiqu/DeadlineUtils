#pragma once
#include <SFML/Graphics.hpp>
namespace Globals {
extern sf::Font FONT;
int V2I_HASH(sf::Vector2i const& vec);
void init();
sf::Vector2i relMousePos(sf::RenderWindow& window);
}
namespace std {
template<>
struct hash<sf::Vector2i>
{
    std::size_t operator()(const sf::Vector2i& vec) const {
        auto hash = std::hash<int>();
        return hash(hash(vec.x) + hash(vec.y));
    }
};
}
