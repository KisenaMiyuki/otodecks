/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "CustomLookAndFeel.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;


private:
    //==============================================================================
    // Your private member variables go here...

    // Custom LookAndFeel
    CustomLookAndFeel customLookAndFeel;

    // For audio thumbnail
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache{50};

    // GUI components
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
  
    Slider volSlider; 
    Slider speedSlider;
    Slider positionSlider;


    // Audio
    DJAudioPlayer player1{formatManager, reverb};
    DJAudioPlayer player2{formatManager, reverb};

    DeckGUI deck1{ &player1, &formatManager, &thumbnailCache, &customLookAndFeel };
    DeckGUI deck2{ &player2, &formatManager, &thumbnailCache, &customLookAndFeel };

    MixerAudioSource mixer;

    // Reeeeeeeeeverb
    Reverb reverb;


    // Playlist
    PlaylistComponent playlist;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
