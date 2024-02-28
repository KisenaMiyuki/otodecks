/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 22 Feb 2024 10:19:09pm
    Author:  miyuki

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Constructor
    CustomLookAndFeel();

    // Override the drawRotarySlider method
    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

    // Override the drawButtonBackground method
	void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour,
								bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    // Custom Typeface
    juce::Typeface::Ptr smoochsans {juce::Typeface::createSystemTypefaceFor(BinaryData::SmoochSansRegular_ttf, BinaryData::SmoochSansRegular_ttfSize)};
    juce::Typeface::Ptr smoochsansMedium {juce::Typeface::createSystemTypefaceFor(BinaryData::SmoochSansMedium_ttf, BinaryData::SmoochSansMedium_ttfSize)};
};
