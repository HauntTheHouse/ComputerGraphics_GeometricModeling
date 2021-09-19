#include "CustomPanel.h"

CustomPanel::CustomPanel(const std::string& aName, const sf::Vector2i& aPosition, const sf::Vector2i& aSize, float aMargin)
        : tgui::Panel()
        , mMargin(aMargin)
        , mCurHeightPointer(0.0f)
{
    setWidgetName(aName);
    setPosition(aPosition.x, aPosition.y);
    setSize(aSize.x, aSize.y);
}

CustomPanel::Ptr CustomPanel::create(const std::string &aName, sf::Vector2i &aPosition, const sf::Vector2i &aSize, float aMargin)
{
    return std::make_shared<CustomPanel>(aName, aPosition, aSize, aMargin);
}

void CustomPanel::addSlider(const std::string &aText, float *aChangeableValue, float aMinVal, float aMaxVal, float aStep)
{
    *aChangeableValue = aMinVal + (aMaxVal - aMinVal)/2.0f;

    const auto slider = tgui::Slider::create(aMinVal, aMaxVal);
    slider->setPosition(getPosition().x + mMargin, getPosition().y + mMargin + mCurHeightPointer);
    slider->setSize(static_cast<float>(getSize().x) - mMargin * 2.0f, mMargin);
    slider->setValue(*aChangeableValue);
    slider->setStep(aStep);
    slider->setChangeValueOnScroll(true);
    add(slider);

    const auto label = tgui::Label::create(aText + std::to_string(*aChangeableValue));
    const auto textSize = label->getSize();
    label->setPosition(tgui::Vector2f(getPosition().x + getSize().x/2.0f - textSize.x/2.0f, getPosition().y + mMargin * 3.0f + mCurHeightPointer));
    add(label);

    mCurHeightPointer += mMargin * 6.0f;

    mSliders.push_back({slider, label, aText, aChangeableValue});
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
}

