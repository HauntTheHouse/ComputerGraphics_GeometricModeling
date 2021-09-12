#include "Menu.h"

Menu::Menu(sf::RenderWindow& aRenderWindow, unsigned int aWidth, unsigned int aHeight, float aMargin)
    : mGui(aRenderWindow)
    , mWidth(aWidth)
    , mHeight(aHeight)
    , mMargin(aMargin)
    , mCurHeightPointer(0.0f)
{
}

void Menu::addSlider(const std::string& aText, float* aChangeableValue, float aMinVal, float aMaxVal)
{
    *aChangeableValue = aMinVal + (aMaxVal - aMinVal)/2.0f;

    tgui::Slider::Ptr slider = tgui::Slider::create(aMinVal, aMaxVal);
    slider->setPosition(mMargin, mMargin + mCurHeightPointer);
    slider->setSize(static_cast<float>(mWidth) - mMargin * 2.0f, mMargin);
    slider->setValue(*aChangeableValue);
    slider->setChangeValueOnScroll(true);
    mGui.add(slider);

    tgui::Label::Ptr label = tgui::Label::create(aText + std::to_string(*aChangeableValue));
    const auto textSize = label->getSize();
    label->setPosition(tgui::Vector2f(mWidth/2.0f - textSize.x/2.0f, mMargin * 3.0f + mCurHeightPointer));
    mGui.add(label);

    mCurHeightPointer += mMargin * 6.0f;

    mSliders.push_back({slider, label, aText, aChangeableValue});
}

void Menu::handleEvent(sf::Event aEvent)
{
    mGui.handleEvent(aEvent);

    for (const auto& sliderInfo : mSliders)
    {
        if (sliderInfo.mSlider->isFocused())
        {
            *sliderInfo.mChangeableValue = sliderInfo.mSlider->getValue();
            sliderInfo.mLabel->setText(sliderInfo.mText + std::to_string(*sliderInfo.mChangeableValue));
        }
    }
}

void Menu::draw()
{
    mGui.draw();
}
