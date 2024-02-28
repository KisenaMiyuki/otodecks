/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Feb 2024 2:30:31pm
    Author:  miyuki

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager* format_manager, AudioThumbnailCache* thumbnail_cache)
					: thumbnail(512, *format_manager, *thumbnail_cache)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    thumbnail.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    if (fileLoaded)
	{
        // draw waveform
		g.setColour(findColour(Slider::rotarySliderFillColourId));
		thumbnail.drawChannel(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 0, 1.0f);

        // draw play head
        g.setColour(juce::Colours::white);
        g.drawRect(playhead_position_relative * getWidth(), 0, getWidth() / 50, getHeight());
	}
	else
	{
        g.setColour(juce::Colours::orange);
        g.setFont(20.0f);
        g.drawText("File not loaded", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
	}
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}



void WaveformDisplay::loadURL(const juce::URL& url)
{
    thumbnail.clear();
	fileLoaded = thumbnail.setSource(new URLInputSource(url));
    
}


void WaveformDisplay::setPositionRelative(double positionRelative)
{
	playhead_position_relative = positionRelative;
    repaint();
}