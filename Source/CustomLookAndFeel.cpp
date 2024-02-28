/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 22 Feb 2024 10:19:09pm
    Author:  miyuki

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    // Colors
    const Colour backgroundColour = Colour::Colour(218, 218, 218);
    const Colour foregroundColour = Colour::Colour(56, 56, 58);


    // Set the general background colour
	setColour(ResizableWindow::backgroundColourId, backgroundColour);

	// Set the colours for the slider
	setColour(Slider::rotarySliderFillColourId, foregroundColour);
	setColour(Slider::rotarySliderOutlineColourId, Colour::Colour());
    setColour(Slider::thumbColourId, backgroundColour);

    // Set the colours for the buttons
    setColour(TextButton::buttonColourId, foregroundColour);
    setColour(TextButton::buttonOnColourId, Colour::Colour(0, 0, 0));
    setColour(TextButton::textColourOffId, Colour::Colour(0, 0, 0));
    setColour(TextButton::textColourOnId, Colour::Colour(255, 255, 255));

    // Set the colours for the labels
    setColour(Label::textColourId, foregroundColour);


    // Set default font
	// setDefaultSansSerifTypeface(smoochsansMedium);
}


void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    // Get the outline and fill colours for the slider
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto darkFill = slider.findColour(Slider::rotarySliderFillColourId);
    auto lightFill = slider.findColour(Slider::thumbColourId);

    // Define the bounds of the slider, reduced by 10 pixels on all sides
    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    // Calculate the radius of the slider
    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    // Calculate the angle to which the slider is currently set
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    // Define the width of the line used to draw the slider
    auto lineW = jmin(4.0f, radius * 0.5f);
    // Define the radius of the arc of the slider
    auto arcRadius = radius - lineW * 0.5f;
    // Define the radius of the knob
    auto knobRadius = arcRadius * 0.9f;

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
        g.setColour(darkFill);
        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    // Calculate the size and position of the endpoints of knob marker
    auto markerWidth = lineW * 0.9f;
    constexpr auto markerStartProportion = 0.3f;
    constexpr auto markerEndProportion = 0.8f;
    Point<float> markerStartPoint(
        bounds.getCentreX() + knobRadius * markerStartProportion * std::cos(toAngle - MathConstants<float>::halfPi),
        bounds.getCentreY() + knobRadius * markerStartProportion * std::sin(toAngle - MathConstants<float>::halfPi)
    );
    Point<float> markerEndPoint(
		bounds.getCentreX() + knobRadius * markerEndProportion * std::cos(toAngle - MathConstants<float>::halfPi),
		bounds.getCentreY() + knobRadius * markerEndProportion * std::sin(toAngle - MathConstants<float>::halfPi)
	);

    // Draw the knob with darkFill colour
    g.setColour(darkFill);
    g.fillEllipse(Rectangle<float>(knobRadius * 2, knobRadius * 2).withCentre(bounds.getCentre()));

    // Draw the knob marker
    g.setColour(lightFill);
    Path markerPath;
    markerPath.addLineSegment(Line<float>(markerStartPoint, markerEndPoint), 1);
    g.strokePath(markerPath, PathStrokeType(markerWidth, PathStrokeType::curved, PathStrokeType::rounded));
}

void CustomLookAndFeel::drawButtonBackground(Graphics& g,
										     Button& button,
										     const Colour& backgroundColour,
										     bool shouldDrawButtonAsHighlighted,
										     bool shouldDrawButtonAsDown)
{
    auto cornerSize = 6.0f;
    auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

    auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

    g.setColour(baseColour);

    auto flatOnLeft = button.isConnectedOnLeft();
    auto flatOnRight = button.isConnectedOnRight();
    auto flatOnTop = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();

    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
        Path path;
        path.addRoundedRectangle(bounds.getX(), bounds.getY(),
            bounds.getWidth(), bounds.getHeight(),
            cornerSize, cornerSize,
            !(flatOnLeft || flatOnTop),
            !(flatOnRight || flatOnTop),
            !(flatOnLeft || flatOnBottom),
            !(flatOnRight || flatOnBottom));

        g.fillPath(path);

        g.setColour(button.findColour(ComboBox::outlineColourId));
        g.strokePath(path, PathStrokeType(1.0f));
    }
    else
    {
        g.fillRoundedRectangle(bounds, cornerSize);

        g.setColour(button.findColour(ComboBox::outlineColourId));
        g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
    }
}
