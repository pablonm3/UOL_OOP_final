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
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


using namespace std;

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
: deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(addButton);
    addAndMakeVisible(searchLabel);
    addAndMakeVisible(tableComponent);
    searchLabel.setEditable(true);
    searchLabel.onTextChange = [this] {
        searchQuery = searchLabel.getText().toLowerCase();
        DBG("searchQuery: " + searchQuery);
        refresh();
    };

    
    
    addButton.addListener(this);
    
    tableComponent.getHeader().addColumn("Track title", 1, 250);
    tableComponent.getHeader().addColumn("Lenght", 2, 150);
    tableComponent.getHeader().addColumn("", 3, 200);
    tableComponent.getHeader().addColumn("", 4, 200);
    tableComponent.setModel(this);
    
    
    formatManager.registerBasicFormats();
    state_file_path = File::getSpecialLocation(File::SpecialLocationType
::userApplicationDataDirectory).getFullPathName() + "/UOL_ottodecks_playlist.xml";
    DBG("state_file_path: "+ state_file_path);
    restoreLibrary();
}

PlaylistComponent::~PlaylistComponent()
{
    files.clear();
}

int PlaylistComponent::getNumRows ()
{
    return fileIndices.size();
}

void PlaylistComponent::paintRowBackground (Graphics & g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    g.fillAll(Colours::darkgrey);
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
    tableComponent.getViewport()->setScrollBarsShown(true, false, true);

}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    int tableSize = getHeight() * 0.7;
    int rowH = 20;
    tableComponent.setBounds(0, 0, getWidth(), tableSize);
    searchLabel.setBounds(0, tableSize, (getWidth()/2) - 3, rowH);
    addButton.setBounds(getWidth()/2, tableSize, getWidth()/2, rowH);

}

void PlaylistComponent::paintCell (Graphics & g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    int index = fileIndices[rowNumber];
    if(columnId ==1){
        // render filename
        g.drawText (files[index].getFileName(), // the important bit
                    2, 0,
                    width - 4, height,
                    Justification::centredLeft,
                    true);
    }
    if(columnId ==2){
        // render song lenght
        URL audioURL = files[index];
        auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
        int durationInSecs = reader->lengthInSamples/reader->sampleRate;
        int mins = durationInSecs / 60;
        int secs = durationInSecs -(mins*60);
        g.drawText (to_string(mins) + " Mins, " + to_string(secs)+ " Secs", // the important bit
                    2, 0,
                    width - 4, height,
                    Justification::centredLeft,
                    true);
        delete reader;
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
    saveLibraryToTile();
}

void PlaylistComponent::saveLibraryToTile(){
    
    XmlElement newElement{"paths"};

    for(URL &u: files) {
        String filename = u.getLocalFile().getFullPathName().toLowerCase();
        XmlElement* child = new XmlElement("path");
        child->setAttribute("path", filename);
        newElement.addChildElement(child);
    }
    File file{state_file_path};
    newElement.writeTo(file, XmlElement::TextFormat());
    
}

void PlaylistComponent::restoreLibrary(){
    File file{state_file_path};
    if(file.exists() == false){
        return;
    }
    files.clear();
    XmlDocument xmlDocument{file};

    std::unique_ptr<XmlElement> xmlElement = xmlDocument.getDocumentElement();
    XmlElement* cur_element = xmlElement->getFirstChildElement();
    while (cur_element != nullptr)
    {
        String file_path = cur_element->getStringAttribute("path");
        DBG("READ file_path: "+ file_path);
        File f{file_path};
        URL url = URL{f};
        files.push_back(url);
        cur_element = cur_element->getNextElement();
    }
    refresh();
}


void PlaylistComponent::refresh(){
    fileIndices.clear();

    int index =0;
    for(URL &f: files) {
        std::string filename = f.getFileName().toLowerCase().toStdString();
        int match = filename.rfind(searchQuery.toLowerCase().toStdString());
        if(searchQuery=="" or match != string::npos ){
            fileIndices.push_back(index);
        }
        index +=1;
    }

    tableComponent.updateContent();
    tableComponent.repaint();
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
            btn->setComponentID(id+"_1");
            existingComponentToUpdate = btn;
        }
    }
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Load deck 2");
            btn->addListener(this);
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id+"_2");
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
    else{
        // component id tells the row and wether to load song in deck 1 or 2
        string id = button->getComponentID().toStdString();
        char * char_id = new char [id.length()+1];
        strcpy (char_id, id.c_str());
        DBG("id: "+ id);

        String row{strtok(char_id, "_")};
        cout << "row: "<< row << endl;
        int row_num = stoi(row.toStdString());
        cout << "row_num: "<< row_num << endl;
        String deck_no{strtok (NULL, "-")};
        cout << "deck_no: "<< deck_no;
        int index = fileIndices[row_num];
        URL fileUrl = files[index];
 
        if(deck_no == "1"){
            cout << "loading song in deck1 "<< endl;
            deckGUI1->loadURL(fileUrl);
        }
        else if(deck_no == "2"){
            cout << "loading song in deck2 "<< endl;
            deckGUI2->loadURL(fileUrl);
        }
        delete[] char_id;
    }
}
