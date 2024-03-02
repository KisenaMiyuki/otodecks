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

    // Override the drawTableHeaderBackground method (in V3)
    void drawTableHeaderBackground(Graphics&, TableHeaderComponent&) override;

    // Override the drawTableHeaderColumn method (in V2)
    void drawTableHeaderColumn(Graphics&, TableHeaderComponent&, const String& columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags) override;

    // Table row drawing is handled in paintRowBackground() & paintCell() at PlaylistComponent.cpp

    // Empty background drawing is probably handled in paintListBoxItem() at PlaylistComponent.cpp

    // Custom Typeface
    juce::Typeface::Ptr smoochsans {juce::Typeface::createSystemTypefaceFor(BinaryData::SmoochSansRegular_ttf, BinaryData::SmoochSansRegular_ttfSize)};
    juce::Typeface::Ptr smoochsansMedium {juce::Typeface::createSystemTypefaceFor(BinaryData::SmoochSansMedium_ttf, BinaryData::SmoochSansMedium_ttfSize)};
};
