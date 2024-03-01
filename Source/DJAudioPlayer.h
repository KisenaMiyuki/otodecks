/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 11 Feb 2024 11:24:39pm
    Author:  miyuki

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
public:
    // Constructor
    DJAudioPlayer(AudioFormatManager& format_manager, Reverb& reverb);
	// Destructor
    ~DJAudioPlayer() override;

    // Must-have methods for AudioSource
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


    // Custom methods
    void loadURL(const juce::URL& audioURL);
    void setGain(float newGain);
    void setSpeed(float newSpeedRatio);
    void setPosition(float newPositionSecs);
    void setPositionRelative(float newPositionRatio);

    void setReverbRoomSize(float newRoomSize);
	void setReverbDamping(float newDamping);
    void setReverbWetLevel(float newWetLevel);
	void setReverbDryLevel(float newDryLevel);
	void setReverbWidth(float newWidth);

    void start();
    void stop();

    double getPositionRelative() const;


private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    Reverb& reverb;
    Reverb::Parameters reverbParameters;
    ReverbAudioSource reverbSource{ &resampleSource, false };
};