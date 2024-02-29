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
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    volSlider.setLookAndFeel(customLookAndFeel);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    speedSlider.setLookAndFeel(customLookAndFeel);
    positionSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    positionSlider.setLookAndFeel(customLookAndFeel);

    // Font labelFont = Font(BinaryData::SmoochSansMedium_ttf);
    // labelFont.setHeight(12.0f);
    volDialLabel.setJustificationType(Justification::centred);
    // volDialLabel.setFont(labelFont);
    speedDialLabel.setJustificationType(Justification::centred);
	// speedDialLabel.setFont(labelFont);
    positionDialLabel.setJustificationType(Justification::centred);
	// positionDialLabel.setFont(labelFont);

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

 //    g.drawRect(volSlider.getBounds(), 1);
 //    g.drawRect(volDialLabel.getBounds(), 1);
	// g.drawRect(speedSlider.getBounds(), 1);
 //    g.drawRect(speedDialLabel.getBounds(), 1);
	// g.drawRect(positionSlider.getBounds(), 1);
	// g.drawRect(positionDialLabel.getBounds(), 1);

    // g.setColour (juce::Colours::white);
    // g.setFont (14.0f);
    // g.drawText ("DeckGUI", getLocalBounds(),
    //             juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const double buttonHeight = getHeight() / 3;
    constexpr int buttonWidthPx = 100;
    constexpr int dialWidthPx = 120;
    constexpr float dialLabelHeightRatio = 0.2f;
    constexpr int buttonMargin = 8;

    // Divide the area into 3 columns:   buttons, dials, waveform display
    auto bounds = getLocalBounds();
    auto buttonsBounds = bounds.removeFromLeft(buttonWidthPx);
    auto dialsBounds = bounds.removeFromLeft(dialWidthPx * 2);
    waveformDisplay.setBounds(bounds);

    // Each button takes one third of the height, with a margin
    playButton.setBounds(buttonsBounds.removeFromTop(buttonHeight).reduced(buttonMargin));
    stopButton.setBounds(buttonsBounds.removeFromTop(buttonHeight).reduced(buttonMargin));
    loadButton.setBounds(buttonsBounds.reduced(buttonMargin));

    // Divide the dials area into two equal columns
    auto dialsFirstColumnBounds = dialsBounds.removeFromLeft(dialWidthPx);
    auto dialsSecondColumnBounds = dialsBounds;

    // Each dial takes half the height of the column
    auto dialNum1Bounds = dialsFirstColumnBounds.removeFromTop(dialsFirstColumnBounds.getHeight() / 2);
    auto dialNum2Bounds = dialsFirstColumnBounds;
    // Third dial placed in the middle of the second column
    auto dialNum3Bounds = dialsSecondColumnBounds.reduced(0, getHeight() / 4);

    volSlider.setBounds(dialNum1Bounds.removeFromTop(dialNum1Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    volDialLabel.setBounds(dialNum1Bounds);
    speedSlider.setBounds(dialNum2Bounds.removeFromTop(dialNum2Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    speedDialLabel.setBounds(dialNum2Bounds);
    positionSlider.setBounds(dialNum3Bounds.removeFromTop(dialNum3Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    positionDialLabel.setBounds(dialNum3Bounds);


    // waveformDisplay.setBounds(buttonWidthPx + dialWidthPx * 2, 0, getWidth() - buttonWidthPx - dialWidthPx * 2, getHeight());
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