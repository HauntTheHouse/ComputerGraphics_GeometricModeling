#ifndef LAB1_CUSTOM_PANEL
#define LAB1_CUSTOM_PANEL

#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/CheckBox.hpp>

class CustomPanel : public tgui::Panel
{
public:
    using Ptr = std::shared_ptr<CustomPanel>;

    static CustomPanel::Ptr create(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin);
    CustomPanel(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin = 10.0f);

    void addSlider(const std::string& aText, float* aChangeableValue, float aMinVal, float aMaxVal, float aStep);
    void addCheckbox(const std::string& aText, bool* aIsChecked);

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

    struct CheckboxInfo
    {
        tgui::CheckBox::Ptr mCheckBox;
        std::string mText;
        bool* mIsChecked;
    };
    std::vector<CheckboxInfo> mCheckBoxes;
};

#endif //LAB1_CUSTOM_PANEL
