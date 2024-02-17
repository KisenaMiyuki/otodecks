﻿/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Feb 2024 2:10:19pm
    Author:  miyuki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
				 public juce::Button::Listener,
				 public juce::Slider::Listener,
				 public juce::FileDragAndDropTarget,
				 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player, AudioFormatManager* format_manager, AudioThumbnailCache* thumbnail_cache, LookAndFeel* customLookAndFeel);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement pure virtual function in Button::Listener */
    void buttonClicked(Button* button) override;
    
    /** implement pure virtual function in Slider::Listener */
    void sliderValueChanged(Slider* slider) override;

    /** implement pure virtual function in FileDragAndDropTarget */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** implement pure virtual function in Timer */
    void timerCallback() override;

private:

    TextButton playButton{ "P" };
    TextButton stopButton{ "S" };
    TextButton loadButton{ "L" };

    Slider volSlider;
    Label volDialLabel{ "volDialLabel", "Volume" };
    Slider speedSlider;
    Label speedDialLabel{ "speedDialLabel", "Speed" };
    Slider positionSlider;
    Label positionDialLabel{ "positionDialLabel", "Position" };

    WaveformDisplay waveformDisplay;


    // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
    juce::FileChooser fChooser{ "Select a file..." };

    DJAudioPlayer* audioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
