#ifndef MENU
#define MENU

#include "CustomPanel.h"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class Menu
{
public:
    Menu(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aPosition, const sf::Vector2i& aSize);

    void addTabs(const std::vector<CustomPanel::Ptr>& aPanels);
    void handleEvent(sf::Event aEvent);
    void draw();

private:
    tgui::Gui mGui;

    sf::Vector2i mSize;
    sf::Vector2i mPosition;
};

#endif //MENU
