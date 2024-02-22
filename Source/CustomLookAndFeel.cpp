/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 22 Feb 2024 10:19:09pm
    Author:  miyuki

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    // Get the outline and fill colours for the slider
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    // Define the bounds of the slider, reduced by 10 pixels on all sides
    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    // Calculate the radius of the slider, and the angle to which the slider is currently set
    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    // Define the width of the line used to draw the slider, and the radius of the arc of the slider
    auto lineW = jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    // Create a path for the background arc of the slider
    Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    // Draw the background arc with the outline colour
    g.setColour(outline);
    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

    // If the slider is enabled, draw the value arc of the slider
    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        // Draw the value arc with the fill colour
        g.setColour(fill);
        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    // Calculate the size and position of the thumb (the part of the slider that the user interacts with)
    auto thumbWidth = lineW * 2.0f;
    Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));

    // Draw the thumb with the thumb colour
    g.setColour(slider.findColour(Slider::thumbColourId));
    g.fillEllipse(Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
}
