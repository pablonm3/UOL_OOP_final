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
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //addAndMakeVisible(tableComponent);
    addAndMakeVisible(addButton);
    addAndMakeVisible(viewport);
    addAndMakeVisible(searchLabel);
    searchLabel.setEditable(true);
    searchLabel.onTextChange = [this] {
        searchQuery = searchLabel.getText().toLowerCase();
        DBG("searchQuery: " + searchQuery);
        refresh();
    };

    

    viewport.setViewedComponent(&tableComponent, false);
    
    addButton.addListener(this);
    
    tableComponent.getHeader().addColumn("Track title", 1, 250);
    tableComponent.getHeader().addColumn("Lenght", 2, 150);
    tableComponent.getHeader().addColumn("Actions", 3, 400);
    tableComponent.setModel(this);
    
    formatManager.registerBasicFormats();
}

PlaylistComponent::~PlaylistComponent()
{
}

int PlaylistComponent::getNumRows ()
{
    DBG("getNumRows - filesFiltered size: "+ to_string(filesFiltered.size()));
    return filesFiltered.size();
    
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
    //tableComponent.setBounds(0, 0, getWidth(), getHeight());
    searchLabel.setBounds(0, tableSize, (getWidth()/2) - 3, rowH);
    addButton.setBounds(getWidth()/2, tableSize, getWidth()/2, rowH);
    viewport.setBounds(0, 0, getWidth(), tableSize);

    tableComponent.setSize(viewport.getWidth(), viewport.getHeight()+1); // with this size you will be able to scroll around with 1x1 pixel offset
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
        g.drawText (filesFiltered[rowNumber]->getFileName(), // the important bit
                    2, 0,
                    width - 4, height,
                    Justification::centredLeft,
                    true);
    }
    if(columnId ==2){
        // render song lenght
        URL * audioURL = filesFiltered[rowNumber];
        auto* reader = formatManager.createReaderFor(audioURL->createInputStream(false));
        int durationInSecs = reader->lengthInSamples/reader->sampleRate;
        int mins = durationInSecs / 60;
        int secs = durationInSecs -(mins*60);
        g.drawText (to_string(mins) + " Mins, " + to_string(secs)+ " Secs", // the important bit
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
        refresh();
    }
}


void PlaylistComponent::refresh(){
    filesFiltered.clear();


    for(URL &f: files) {
        std::string filename = f.getFileName().toLowerCase().toStdString();
        int match = filename.rfind(searchQuery.toLowerCase().toStdString());
        if(searchQuery=="" or match != string::npos ){
            filesFiltered.push_back(&f);
        }
    }


    tableComponent.updateContent();
    tableComponent.repaint();
    viewport.componentMovedOrResized(*this, false, true);
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
        addSong();
    }
}
