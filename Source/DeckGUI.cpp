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

    addAndMakeVisible(reverbRoomSizeSlider);
    addAndMakeVisible(reverbRoomSizeLabel);
    addAndMakeVisible(reverbDampingSlider);
    addAndMakeVisible(reverbDampingLabel);
    addAndMakeVisible(reverbWetLevelSlider);
    addAndMakeVisible(reverbWetLevelLabel);
    addAndMakeVisible(reverbDryLevelSlider);
    addAndMakeVisible(reverbDryLevelLabel);
    addAndMakeVisible(reverbWidthSlider);
    addAndMakeVisible(reverbWidthLabel);

    addAndMakeVisible(reverbSectionTitleLabel);
    addAndMakeVisible(sectionSeparator);

    addAndMakeVisible(waveformDisplay);


    volSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    positionSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);

    reverbRoomSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbRoomSizeSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    reverbDampingSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbDampingSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    reverbWetLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbWetLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    reverbDryLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbDryLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);
    reverbWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbWidthSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 14);

    // Font labelFont = Font(BinaryData::SmoochSansMedium_ttf);
    // labelFont.setHeight(12.0f);
    volDialLabel.setJustificationType(Justification::centred);
    // volDialLabel.setFont(labelFont);
    speedDialLabel.setJustificationType(Justification::centred);
	// speedDialLabel.setFont(labelFont);
    positionDialLabel.setJustificationType(Justification::centred);
	// positionDialLabel.setFont(labelFont);

    reverbRoomSizeLabel.setJustificationType(Justification::centred);
    reverbDampingLabel.setJustificationType(Justification::centred);
    reverbWetLevelLabel.setJustificationType(Justification::centred);
    reverbDryLevelLabel.setJustificationType(Justification::centred);
    reverbWidthLabel.setJustificationType(Justification::centred);

    reverbSectionTitleLabel.setJustificationType(Justification::centred);


    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);

    reverbRoomSizeSlider.addListener(this);
    reverbDampingSlider.addListener(this);
    reverbWetLevelSlider.addListener(this);
    reverbDryLevelSlider.addListener(this);
    reverbWidthSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    volSlider.setSkewFactor(0.5);   // make it easier to set lower values
    volSlider.setValue(0.1);
    speedSlider.setRange(0.0, 2.0);
    speedSlider.setValue(1.0);
    positionSlider.setRange(0.0, 1.0);

    reverbRoomSizeSlider.setRange(0.0, 1.0);
    reverbRoomSizeSlider.setValue(0.5);
    reverbDampingSlider.setRange(0.0, 1.0);
    reverbDampingSlider.setValue(0.5);
    reverbWetLevelSlider.setRange(0.0, 1.0);
    reverbWetLevelSlider.setValue(0);
    reverbDryLevelSlider.setRange(0.0, 1.0);
    reverbDryLevelSlider.setValue(0.4);
    reverbWidthSlider.setRange(0.0, 1.0);
    reverbWidthSlider.setValue(1.0);


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

    // g.setColour (juce::Colour(255, 0, 0));
    // g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // Draw only corners
    g.setColour(findColour(Slider::rotarySliderFillColourId));
    constexpr int cornerStrokeLengthPx = 20;
    constexpr int cornerStrokeWeightPx = 2;
    // auto topLeftCorner = getLocalBounds().getTopLeft();
	// auto topRightCorner = getLocalBounds().getTopRight();
	// auto bottomLeftCorner = getLocalBounds().getBottomLeft();
	// auto bottomRightCorner = getLocalBounds().getBottomRight();
    g.fillRect(getLocalBounds().removeFromTop(cornerStrokeWeightPx).removeFromLeft(cornerStrokeLengthPx));
	g.fillRect(getLocalBounds().removeFromLeft(cornerStrokeWeightPx).removeFromTop(cornerStrokeLengthPx));

	g.fillRect(getLocalBounds().removeFromBottom(cornerStrokeWeightPx).removeFromLeft(cornerStrokeLengthPx));
    g.fillRect(getLocalBounds().removeFromLeft(cornerStrokeWeightPx).removeFromBottom(cornerStrokeLengthPx));

    g.fillRect(getLocalBounds().removeFromTop(cornerStrokeWeightPx).removeFromRight(cornerStrokeLengthPx));
	g.fillRect(getLocalBounds().removeFromRight(cornerStrokeWeightPx).removeFromTop(cornerStrokeLengthPx));

    g.fillRect(getLocalBounds().removeFromBottom(cornerStrokeWeightPx).removeFromRight(cornerStrokeLengthPx));
    g.fillRect(getLocalBounds().removeFromRight(cornerStrokeWeightPx).removeFromBottom(cornerStrokeLengthPx));


    g.drawRect(sectionSeparator.getLocalBounds(), 2);

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
    constexpr int dialWidthPx = 100;
    constexpr float dialLabelHeightRatio = 0.15f;
    constexpr int buttonMargin = 8;

    // Divide the area into 3 columns:   buttons, dials, waveform display
    auto bounds = getLocalBounds();
    auto buttonsBounds = bounds.removeFromLeft(buttonWidthPx);
    auto dialsBounds = bounds.removeFromLeft(dialWidthPx * 4);
    waveformDisplay.setBounds(bounds.reduced(buttonMargin));

    // Each button takes one third of the height, with a margin
    playButton.setBounds(buttonsBounds.removeFromTop(buttonHeight).reduced(buttonMargin));
    stopButton.setBounds(buttonsBounds.removeFromTop(buttonHeight).reduced(buttonMargin));
    loadButton.setBounds(buttonsBounds.reduced(buttonMargin));

    // Divide the dials area into two columns of standard width (playback control)...
    auto dialsFirstColumnBounds = dialsBounds.removeFromLeft(dialWidthPx);
    auto dialsSecondColumnBounds = dialsBounds.removeFromLeft(dialWidthPx);
    // And three columns of reduced width (reverb control)
    // Section title spans all three columns
    auto reverbSectionTitleBounds = dialsBounds;
    reverbSectionTitleBounds = reverbSectionTitleBounds.removeFromTop(reverbSectionTitleBounds.getHeight() / 6);
    reverbSectionTitleLabel.setBounds(reverbSectionTitleBounds);
    auto sectionSeparatorBounds = dialsBounds;
	sectionSeparatorBounds = sectionSeparatorBounds.removeFromLeft(2);
    sectionSeparator.setBounds(sectionSeparatorBounds);

    auto dialsThirdColumnBounds = dialsBounds.removeFromLeft(dialsBounds.getWidth() / 3);
    auto dialsFourthColumnBounds = dialsBounds.removeFromLeft(dialsBounds.getWidth() / 2);
    auto dialsFifthColumnBounds = dialsBounds;

    // [ Playback control ]
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

    // [ Reverb control ]
    // Compress height headroom
    dialsThirdColumnBounds = dialsThirdColumnBounds.reduced(0, dialsThirdColumnBounds.getHeight() * 0.1);
    dialsFourthColumnBounds = dialsFourthColumnBounds.reduced(0, dialsFourthColumnBounds.getHeight() * 0.1);
    dialsFifthColumnBounds = dialsFifthColumnBounds.reduced(0, dialsFifthColumnBounds.getHeight() * 0.1);
    // Each dial takes half the height of the column
    auto dialNum4Bounds = dialsThirdColumnBounds.removeFromTop(dialsThirdColumnBounds.getHeight() / 2);
    auto dialNum5Bounds = dialsThirdColumnBounds;
    auto dialNum6Bounds = dialsFourthColumnBounds.reduced(0, dialsFourthColumnBounds.getHeight() / 4);
    auto dialNum7Bounds = dialsFifthColumnBounds.removeFromTop(dialsFifthColumnBounds.getHeight() / 2);
    auto dialNum8Bounds = dialsFifthColumnBounds;

    reverbRoomSizeSlider.setBounds(dialNum4Bounds.removeFromTop(dialNum4Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    reverbRoomSizeLabel.setBounds(dialNum4Bounds);
    reverbDampingSlider.setBounds(dialNum5Bounds.removeFromTop(dialNum5Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    reverbDampingLabel.setBounds(dialNum5Bounds);
    reverbWidthSlider.setBounds(dialNum6Bounds.removeFromTop(dialNum6Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    reverbWidthLabel.setBounds(dialNum6Bounds);
    reverbWetLevelSlider.setBounds(dialNum7Bounds.removeFromTop(dialNum7Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    reverbWetLevelLabel.setBounds(dialNum7Bounds);
    reverbDryLevelSlider.setBounds(dialNum8Bounds.removeFromTop(dialNum8Bounds.getHeight() * (1 - dialLabelHeightRatio)));
    reverbDryLevelLabel.setBounds(dialNum8Bounds);


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

    if (slider == &reverbRoomSizeSlider)
	{
		audioPlayer->setReverbRoomSize(slider->getValue());
	}

    if (slider == &reverbDampingSlider)
    {
        audioPlayer->setReverbDamping(slider->getValue());
    }

    if (slider == &reverbWetLevelSlider)
    {
        audioPlayer->setReverbWetLevel(slider->getValue());
    }

    if (slider == &reverbDryLevelSlider)
    {
        audioPlayer->setReverbDryLevel(slider->getValue());
    }

    if (slider == &reverbWidthSlider)
    {
        audioPlayer->setReverbWidth(slider->getValue());
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