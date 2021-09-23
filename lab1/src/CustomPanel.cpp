#include "CustomPanel.h"

CustomPanel::CustomPanel(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin)
        : tgui::Panel()
        , mPadding(aMargin)
        , mCurHeightPointer(10.0f)
{
    setWidgetName(aName);
    setPosition(aPosition.x, aPosition.y);
    setSize(aSize.x, aSize.y);
}

CustomPanel::Ptr CustomPanel::create(const std::string &aName, const sf::Vector2i &aPosition, const sf::Vector2i &aSize, float aMargin)
{
    return std::make_shared<CustomPanel>(aName, aPosition, aSize, aMargin);
}

void CustomPanel::addSlider(const std::string &aText, float *aChangeableValue, float aMinVal, float aMaxVal, float aStep)
{
    *aChangeableValue = aMinVal + (aMaxVal - aMinVal)/2.0f;

    const auto slider = tgui::Slider::create(aMinVal, aMaxVal);
    slider->setPosition(getPosition().x + mPadding, getPosition().y + mPadding + mCurHeightPointer);
    slider->setSize(static_cast<float>(getSize().x) - mPadding * 2.0f, mPadding);
    slider->setValue(*aChangeableValue);
    slider->setStep(aStep);
    slider->setChangeValueOnScroll(true);
    add(slider);

    const auto label = tgui::Label::create(aText + std::to_string(*aChangeableValue));
    label->setPosition(getPosition().x + getSize().x / 2.0f - label->getSize().x / 2.0f,
                       getPosition().y + mPadding * 3.0f + mCurHeightPointer);
    add(label);

    mCurHeightPointer += mPadding * 6.0f;

    mSliders.push_back({slider, label, aText, aChangeableValue});
}

void CustomPanel::addCheckbox(const std::string &aText, bool* aIsChecked)
{
    *aIsChecked = false;
    const auto checkbox = tgui::CheckBox::create(aText);
    checkbox->setPosition(getPosition().x + getSize().x / 2.0f - checkbox->getFullSize().x / 2.0f,
                          getPosition().y + mPadding + mCurHeightPointer);
    add(checkbox);

    mCurHeightPointer += mPadding * 3.0f;

    mCheckBoxes.push_back({checkbox, aText, aIsChecked});
}

void CustomPanel::addKnob(const std::string &aText, float *aChangeableValue, float aStartValue)
{
    *aChangeableValue = aStartValue;
    const auto knob = tgui::Knob::create();
    knob->setValue(aStartValue);
    knob->setSize(getSize().x - 10.0f * mPadding, getSize().x - 10.0f * mPadding);
    knob->setPosition(getPosition().x + getSize().x / 2.0f - knob->getFullSize().x / 2.0f,
                      getPosition().y + mPadding + mCurHeightPointer);
    add(knob);

    mCurHeightPointer += mPadding * 10.0f;

    const auto label = tgui::Label::create(aText);
    label->setPosition(getPosition().x + getSize().x / 2.0f - label->getSize().x / 2.0f,
                       getPosition().y + mPadding + mCurHeightPointer);
    add(label);

    mCurHeightPointer += mPadding * 3.0f;

    mKnobs.push_back({knob, aText, aChangeableValue});
}

void CustomPanel::updateChangeableValues()
{
    for (const auto& sliderInfo : mSliders)
    {
        if (sliderInfo.mSlider->isMouseDown())
        {
            *sliderInfo.mChangeableValue = sliderInfo.mSlider->getValue();
            sliderInfo.mLabel->setText(sliderInfo.mText + std::to_string(*sliderInfo.mChangeableValue));
        }
    }
    for (const auto& checkboxInfo : mCheckBoxes)
    {
        if (checkboxInfo.mCheckBox->isMouseDown())
        {
            *checkboxInfo.mIsChecked = !checkboxInfo.mCheckBox->isChecked();
        }
    }
    for (const auto& knobInfo : mKnobs)
    {
        if (knobInfo.mKnob->isMouseDown())
        {
            *knobInfo.mChangeableValue = knobInfo.mKnob->getValue();
        }
    }
}



