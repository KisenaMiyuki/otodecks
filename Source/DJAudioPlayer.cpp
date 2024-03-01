/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 11 Feb 2024 11:24:39pm
    Author:  miyuki

  ==============================================================================
*/

#include "DJAudioPlayer.h"

// Constructor
DJAudioPlayer::DJAudioPlayer(AudioFormatManager& format_manager, Reverb& reverb)
	: formatManager(format_manager),
	  reverb(reverb)
{
};

// Destructor
DJAudioPlayer::~DJAudioPlayer() = default;


// Must-have methods
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate);
    resampleSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate);

    // Reverb
    reverbSource.setParameters(reverbParameters);
	reverbSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate);
};

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    reverbSource.getNextAudioBlock(bufferToFill);
};

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
};


// Custom methods
void DJAudioPlayer::loadURL(const juce::URL& audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
            true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
};

void DJAudioPlayer::setGain(float newGain)
{
    if (newGain < 0.0f || newGain > 1.0f)
	{
		DBG("Gain value should be within 0 and 1");
	}
    else
    {
		transportSource.setGain(newGain);
    }
};

void DJAudioPlayer::setSpeed(float newSpeed)
{
    if (newSpeed < 0.0f || newSpeed > 100.0f)
    {
        DBG("Playback speed ratio should be within 0 and 100");
    }
    else
    {
        resampleSource.setResamplingRatio(newSpeed);
    }
};

void DJAudioPlayer::setPosition(float newPositionSecs)
{
    transportSource.setPosition(newPositionSecs);
};

void DJAudioPlayer::setPositionRelative(float newPositionRatio)
{
    if (newPositionRatio < 0.0f || newPositionRatio > 1.0f)
	{
		DBG("Position ratio should be within 0 and 1");
	}
    else
    {
        double positionSecs = transportSource.getLengthInSeconds() * newPositionRatio;
        transportSource.setPosition(positionSecs);
    }
}

void DJAudioPlayer::setReverbRoomSize(float newRoomSize)
{
	reverbParameters.roomSize = newRoomSize;
	reverbSource.setParameters(reverbParameters);
};

void DJAudioPlayer::setReverbDamping(float newDamping)
{
    reverbParameters.damping = newDamping;
    reverbSource.setParameters(reverbParameters);
};

void DJAudioPlayer::setReverbWetLevel(float newWetLevel)
{
    reverbParameters.wetLevel = newWetLevel;
    reverbSource.setParameters(reverbParameters);
};

void DJAudioPlayer::setReverbDryLevel(float newDryLevel)
{
    reverbParameters.dryLevel = newDryLevel;
    reverbSource.setParameters(reverbParameters);
};

void DJAudioPlayer::setReverbWidth(float newWidth)
{
    reverbParameters.width = newWidth;
    reverbSource.setParameters(reverbParameters);
};


void DJAudioPlayer::start()
{
    transportSource.start();
};

void DJAudioPlayer::stop()
{
    transportSource.stop();
};


double DJAudioPlayer::getPositionRelative() const
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
};