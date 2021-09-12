#ifndef LAB1_MENU
#define LAB1_MENU

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class Menu
{
public:
    Menu(sf::RenderWindow& aRenderWindow, unsigned int aWidth, unsigned int aHeight, float aMargin = 10.0f);

    void addSlider(const std::string& aText, float* aChangeableValue, float aMinVal, float aMaxVal);
    void handleEvent(sf::Event aEvent);
    void draw();

private:
    tgui::Gui mGui;

    unsigned int mWidth;
    unsigned int mHeight;

    float mCurHeightPointer;
    float mMargin;

    struct SliderInfo
    {
        tgui::Slider::Ptr mSlider;
        tgui::Label::Ptr mLabel;
        std::string mText;
        float* mChangeableValue;
    };
    std::vector<SliderInfo> mSliders;
};

#endif //LAB1_MENU
