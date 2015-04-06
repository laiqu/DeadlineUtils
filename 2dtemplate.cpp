#include <iostream>
#include <unordered_map>
#include <thread>
#include "2dvis/Globals.h"
#include "2dvis/GridWorld.h"
#include "conn/Connections.h"
int main(int argc, char* argv[]) {
    // init globals (font)
    Globals::init();
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D");
    // SFML returns cursor with weird offest, so it's better to draw our own
    window.setMouseCursorVisible(false);  
    sf::RectangleShape mousecursor({5, 5});
    mousecursor.setFillColor(sf::Color::Red);

    // Create grid
    GridWorld world = GridWorld (&window, Globals::FONT);
    std::unordered_map<sf::Vector2i, sf::Color> colorMap;
    world.addCellContent([&colorMap](sf::Vector2i index, float scale, float cell_size) {
                auto color_it = colorMap.find(index);
                if (color_it != colorMap.end()) {
                    sf::RectangleShape* colorRect = new sf::RectangleShape(
                            {cell_size * scale, cell_size * scale});
                    colorRect->setFillColor(color_it->second);
                    return Content(colorRect);
                }
                return Content();
            });
    // Draw indexes on cells
    world.addCellContent(Contents::indexNumber);
    // Draw index of cell under mouse cursor. 
    world.addOnHover([&window](sf::Vector2i index) {
                sf::Text index_text(std::to_string(index.x) + " " +
                                    std::to_string(index.y), Globals::FONT);
                index_text.setCharacterSize(20);
                index_text.setColor(sf::Color::Yellow);
                index_text.move(sf::Vector2f(Globals::relMousePos(window)));
                window.draw(index_text);
            });
    // Mark clicked cells as green.
    world.addOnClick([&window, &colorMap](sf::Vector2i index) {
                colorMap[index] = sf::Color(0,255,0);
             }, sf::Mouse::Button::Left);

    // Erase green when right mouse button is clicked.
    world.addOnHover([&window, &colorMap](sf::Vector2i index) {
                if (window.hasFocus()) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                        colorMap.erase(index);
                    } 
                }
            });
    // Start draw loop in seperate thread
    std::thread draw_thread([&window, &mousecursor, &world](){
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            mousecursor.setPosition(sf::Vector2f(Globals::relMousePos(window)));
            window.clear();
            world.update();
            window.draw(mousecursor);
            window.display();
        }
    });
    if (argc < 3) {
        std::cerr << "need host and port\n";
        return -1;
    }
    auto conn_ptr = get_connection(argv[1], argv[2]);
    Connection& conn = *conn_ptr;
    if (!login(conn, "mirek", "mirabelka")) {
        return -1;
    }
    conn << "COMMAND";
    precommand(conn);
    // Block on drawing
    draw_thread.join();
    return 0;
}

