#ifndef LAB1_CUSTOM_PANEL
#define LAB1_CUSTOM_PANEL

#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/Label.hpp>

class CustomPanel : public tgui::Panel
{
public:
    using Ptr = std::shared_ptr<CustomPanel>;

    static CustomPanel::Ptr create(const std::string& aName, sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin);
    CustomPanel(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin = 10.0f);

    void addSlider(const std::string& aText, float* aChangeableValue, float aMinVal, float aMaxVal, float aStep);
    void updateChangeableValues();

private:
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

#endif //LAB1_CUSTOM_PANEL
