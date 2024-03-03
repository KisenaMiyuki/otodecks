/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 15 Feb 2024 10:18:08pm
    Author:  miyuki

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(table);

    // adding columns to table header row
    table.getHeader().addColumn("Title", 1, 250);
    table.getHeader().addColumn("Artist", 2, 150);
    table.getHeader().addColumn("Action", 3, 150);

    // add some placeholder data to playlistVector
    playlistVector.push_back("Song 1");
    playlistVector.push_back("Jesus");
    playlistVector.push_back("Mice on Venus");

    // set the model for the table
    table.setModel(this);   // because PlaylistComponent is itself a TableListBoxModel (through inheritance)
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    table.setBounds(getLocalBounds());
}


int PlaylistComponent::getNumRows()
{
    return playlistVector.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(findColour(Slider::rotarySliderFillColourId));
    }
    else
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));
    }

    // Draw lines on side of row
	g.setColour(findColour(Slider::rotarySliderFillColourId));
    g.fillRect(getLocalBounds().removeFromLeft(2));
    g.fillRect(getLocalBounds().removeFromRight(2));
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
	    g.setColour(findColour(ResizableWindow::backgroundColourId));
	}
	else
	{
        g.setColour(findColour(Slider::rotarySliderFillColourId));
	}

    g.setFont(14.0f);
    // Set font style bold
	g.setFont(g.getCurrentFont().withStyle(juce::Font::bold));


    if (columnId == 1)
    {
        g.drawText(playlistVector[rowNumber], 4, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 2)
    {
        g.drawText("Artist", 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
}


Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 3 && existingComponentToUpdate == nullptr)
    {
		TextButton* actionButton = new TextButton("Play");

        // [ Add a componentID to the button so that we can identify it in buttonClicked() method ]
        // - Convert rowNumber to a JUCE String
		const String rowNumberString{ std::to_string(rowNumber) };
        // - Add rowNumberString to button's componentID
        actionButton->setComponentID(rowNumberString);

        actionButton->addListener(this);
        existingComponentToUpdate = actionButton;
    }

    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    // [ Get the button's componentID to identify which button was clicked ]
    // - Convert button's componentID to an int
    const int rowNumber{ button->getComponentID().getIntValue() };

    DBG("Button clicked: " << playlistVector[rowNumber]);
}
