/*
  ==============================================================================

    DeckTable.h
    Created: 17 Feb 2024 1:48:47pm
    Author:  miyuki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include <vector>

//==============================================================================
/*
*/
class DeckTable  : public juce::Component, public juce::TableListBoxModel
{
public:
    DeckTable();
    ~DeckTable() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // TableListBoxModel must-have methods
    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

private:
    TableListBox deckTable;

    std::vector<DeckGUI> decksVector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckTable)
};
