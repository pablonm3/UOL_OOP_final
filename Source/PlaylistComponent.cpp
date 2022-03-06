/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 25 Feb 2022 3:47:09pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <string>
using namespace std;

//==============================================================================
PlaylistComponent::PlaylistComponent(Viewport* _viewport)
: viewport(_viewport)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(addButton);
    
    addButton.addListener(this);
    
    tableComponent.getHeader().addColumn("Track title", 1, 250);
    tableComponent.getHeader().addColumn("Lenght", 2, 150);
    tableComponent.getHeader().addColumn("Actions", 3, 400);
    tableComponent.setModel(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

int PlaylistComponent::getNumRows ()
{
    return files.size();
}

void PlaylistComponent::paintRowBackground (Graphics & g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    // just highlight selected rows
    //if (rowIsSelected)
   // {
     //   g.fillAll(Colours::orange);
    //}
   // else{
    g.fillAll(Colours::darkgrey);
    //}
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

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
    int tableSize = getHeight() * 0.7;
    int rowH = 20;
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    addButton.setBounds(0, tableSize, getWidth(), rowH);
}

void PlaylistComponent::paintCell (Graphics & g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    if(columnId ==1){
        // render filename
        g.drawText (files[rowNumber].getFileName(), // the important bit
                    2, 0,
                    width - 4, height,
                    Justification::centredLeft,
                    true);
    }
    if(columnId ==2){
        // render song lenght
        g.drawText ("3 minutes", // the important bit
                    2, 0,
                    width - 4, height,
                    Justification::centredLeft,
                    true);
    }
 
}

void PlaylistComponent::cellClicked (int rowNumber, int columnId, const MouseEvent &)
{
    DBG("cellClicked rowNumber: " + to_string(rowNumber) + " - columnId: "+ to_string(columnId));
}

void PlaylistComponent::addSong ()
{
    FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen()){
        URL url = URL{chooser.getResult()};
        files.push_back(url);
        DBG("files size: "+ to_string(files.size()));
        tableComponent.updateContent();
        tableComponent.repaint();
        viewport->componentMovedOrResized(*this, false, true);
    }
}



Component* PlaylistComponent::refreshComponentForCell (
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component *existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Load deck 1");
            btn->addListener(this);
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    if (button == &addButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        addSong();
    }
}
