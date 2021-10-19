#ifndef CUSTOM_PANEL
#define CUSTOM_PANEL

#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/Knob.hpp>

class CustomPanel : public tgui::Panel
{
public:
    using Ptr = std::shared_ptr<CustomPanel>;

    static CustomPanel::Ptr create(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin = 10.0f);
    CustomPanel(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin = 10.0f);

    void addSlider(const std::string& aText, float* aChangeableValue, float aMinVal, float aMaxVal, float aStep);
    void addCheckbox(const std::string& aText, bool* aIsChecked);
    void addKnob(const std::string& aText, float* aChangeableValue, float aStartValue);
    void addLabel(const std::string& aText, float* aChangeableValue);

    void updateChangeableValues();

private:
    float mCurHeightPointer;
    float mPadding;

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

    struct KnobInfo
    {
        tgui::Knob::Ptr mKnob;
        std::string mText;
        float* mChangeableValue;
    };
    std::vector<KnobInfo> mKnobs;

    struct LabelInfo
    {
        tgui::Label::Ptr mLabel;
        std::string mText;
        float* mChangeableValue;
    };
    std::vector<LabelInfo> mLabels;
};

#endif //CUSTOM_PANEL
