/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Feb 2024 2:10:19pm
    Author:  miyuki

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* player, AudioFormatManager *format_manager, AudioThumbnailCache* thumbnail_cache, LookAndFeel* customLookAndFeel)
			: audioPlayer(player),
              waveformDisplay(format_manager, thumbnail_cache)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(volDialLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedDialLabel);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(positionDialLabel);

    addAndMakeVisible(waveformDisplay);

    volSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    volSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 14);
    volSlider.setLookAndFeel(customLookAndFeel);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 14);
    speedSlider.setLookAndFeel(customLookAndFeel);
    positionSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    positionSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 14);
    positionSlider.setLookAndFeel(customLookAndFeel);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    volSlider.setSkewFactor(0.5);   // make it easier to set lower values
    volSlider.setValue(0.1);
    speedSlider.setRange(0.0, 2.0);
    speedSlider.setValue(1.0);
    positionSlider.setRange(0.0, 1.0);


    startTimer(1000);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
};

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // g.setColour (juce::Colours::white);
    // g.setFont (14.0f);
    // g.drawText ("DeckGUI", getLocalBounds(),
    //             juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const double rowH = getHeight() / 7;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);

    waveformDisplay.setBounds(0, rowH * 2, getWidth(), rowH);

    volSlider.setBounds(0, rowH * 3, getWidth() / 3, rowH * 3);
    speedSlider.setBounds(getWidth() / 3, rowH * 3, getWidth() / 3, rowH * 3);
    positionSlider.setBounds(getWidth() / 3 * 2, rowH * 3, getWidth() / 3, rowH * 3);

    loadButton.setBounds(0, rowH * 6, getWidth(), rowH);

}



void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        DBG("Play button clicked");
        audioPlayer->start();
    }
     if (button == &stopButton)
    {
        DBG("Stop button clicked");
        audioPlayer->stop();
    
    }
    if (button == &loadButton)
    {
        
        // this does not appear to work in current version of JUCE 
        // (6.1) despite appearing in the docs
        // it might a macro that disables it. TBC
        //FileChooser chooser{"Select a file..."};
        // if (chooser.browseForFileToOpen())
        // {
        //     loadURL(URL{chooser.getResult()});
        // }
        // 
        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that. 
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFile = chooser.getResult();
            audioPlayer->loadURL(URL{chosenFile});
            waveformDisplay.loadURL(URL{chosenFile});
        });
    }
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
	if (slider == &volSlider)
	{
	   audioPlayer->setGain(slider->getValue());
	}

	if (slider == &speedSlider)
	{
		audioPlayer->setSpeed(slider->getValue());
	}

	if (slider == &positionSlider)
	{
		audioPlayer->setPositionRelative(slider->getValue());
	}

}


bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
	return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    audioPlayer->loadURL(URL{ File{files[0]} });
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(audioPlayer->getPositionRelative());
}