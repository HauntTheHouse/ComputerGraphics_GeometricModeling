#include "Menu.h"

Menu::Menu(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aPosition, const sf::Vector2i& aSize)
    : mGui(aRenderWindow)
    , mPosition(aPosition)
    , mSize(aSize)
{
}

void Menu::addTabs(const std::vector<CustomPanel::Ptr>& aPanels)
{
    const auto tabContainer = tgui::TabContainer::create();
    tabContainer->setPosition(mPosition.x,mPosition.y);
    tabContainer->setSize(mSize.x, mSize.y);

    for (const auto& panel : aPanels)
    {
        tabContainer->addPanel(panel, panel->getWidgetName());
    }
    tabContainer->select(0);

    mGui.add(tabContainer, "TabContainer");
}

void Menu::handleEvent(sf::Event aEvent)
{
    mGui.handleEvent(aEvent);
}

void Menu::draw()
{
    mGui.draw();
}
