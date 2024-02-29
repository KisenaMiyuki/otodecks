/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1000, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);
    // addAndMakeVisible(deckTable);

    // formatManager for waveform thumbnail
    formatManager.registerBasicFormats();

    addAndMakeVisible(playlist);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();

    LookAndFeel::setDefaultLookAndFeel(nullptr);    // Avoids memory leaks
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixer.addInputSource(&player1, false);
    mixer.addInputSource(&player2, false);
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);

}
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixer.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    mixer.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    // const double topHalf = getHeight() * 0.7;
    const double lowHalf = getHeight() * 0.3;
    const double deckGapPx = 5;

    auto bounds = getLocalBounds().reduced(10);

    playlist.setBounds(bounds.removeFromBottom(lowHalf));

    auto deck1Region = bounds.removeFromBottom(bounds.getHeight() / 2);
    auto deck2Region = bounds;

    deck1.setBounds(deck1Region.reduced(0, 5));
    deck2.setBounds(deck2Region.reduced(0, 5));

    // deck1.setBounds(0, 0, getWidth(), topHalf / 2);
    // deck2.setBounds(0, topHalf / 2, getWidth(), topHalf / 2);
	// deckTable.setBounds(0, 0, getWidth(), getHeight() * 0.6);

    // playlist.setBounds(0, getHeight() - lowHalf, getWidth(), lowHalf);

}


