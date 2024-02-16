/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Feb 2024 2:30:31pm
    Author:  miyuki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, public juce::ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager* format_manager, AudioThumbnailCache* thumbnail_cache);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;


    void loadURL(const juce::URL& url);


    void changeListenerCallback(juce::ChangeBroadcaster* source) override
    {
    	if (source == &thumbnail) repaint();
	}

 //    void mouseDown(const MouseEvent& event) override
 //    {
	//     if (fileLoaded)
	//     {
	//     	auto clickPosition = event.position.x;
	// 		auto duration = thumbnail.getTotalLength();
	// 		auto proportion = clickPosition / getWidth();
	// 		auto newPosition = duration * proportion;
	// 		audioPlayer->setPosition(newPosition);
	// 	}
	// }

    // change play head position
    void setPositionRelative(double positionRelative);

private:
    AudioThumbnail thumbnail;
    bool fileLoaded = false;

    double playhead_position_relative = 0.0;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
