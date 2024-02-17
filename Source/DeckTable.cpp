/*
  ==============================================================================

    DeckTable.cpp
    Created: 17 Feb 2024 1:48:47pm
    Author:  miyuki

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckTable.h"

//==============================================================================
DeckTable::DeckTable()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(deckTable);

    deckTable.getHeader().addColumn("Column 1", 1, 100);
    deckTable.getHeader().setStretchToFitActive(true);

    deckTable.setModel(this);

}

DeckTable::~DeckTable()
{
}

void DeckTable::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckTable", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckTable::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    // Fill the whole parent component spaces
    deckTable.setBounds(getLocalBounds());

}

int DeckTable::getNumRows()
{
    return 25;
}

void DeckTable::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.fillAll(juce::Colours::lightblue);
	}
}

void DeckTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	g.setColour(juce::Colours::black);
	g.setFont(14.0f);

	g.drawText("Cell", 2, 0, width - 4, height, juce::Justification::centredLeft, true);
}
