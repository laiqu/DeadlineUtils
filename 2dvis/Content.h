#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
class Content {
    Content(const Content& c) = delete;
    sf::Drawable* draw_ptr;
    sf::Transformable* trans_ptr; 
public:
    Content() : draw_ptr(nullptr), trans_ptr(nullptr) {}
    Content(Content&& other) : draw_ptr(std::move(other.draw_ptr)),
        trans_ptr(std::move(other.trans_ptr)) {} 
    template<typename T>
    Content(T content) : draw_ptr((sf::Drawable*) content),
            trans_ptr((sf::Transformable*) content) {}
    sf::Drawable* getDrawable() {
        return draw_ptr;
    }
    sf::Transformable* getTransformable() {
        return trans_ptr;
    }
    bool hasContent() {
        return draw_ptr != nullptr && trans_ptr != nullptr;
    }
    virtual ~Content() {
        delete draw_ptr;
    }
};
