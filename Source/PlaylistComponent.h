/*
  ==============================================================================

    PlaylistComponent.h
    Created: 25 Feb 2022 3:47:09pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public TableListBoxModel,
                           public Button::Listener
{
public:
    PlaylistComponent(Viewport* _viewport);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows () override;
    void paintRowBackground (Graphics &,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    void paintCell (Graphics &,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;
    
    void cellClicked (int rowNumber, int columnId, const MouseEvent &) override;
    
    Component* refreshComponentForCell (int rowNumber,
        int columnId,
        bool isRowSelected,
        Component *existingComponentToUpdate) override;
    
    void buttonClicked(Button* button) override;
    
    void addSong();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
    TableListBox tableComponent;
    std::vector<URL> files;
    TextButton addButton{"Add song"};
    
    Viewport* viewport;
  
};
