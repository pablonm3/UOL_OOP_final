/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"
using namespace std;

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse,
                 Colour color1,
                 Colour color2,
                 Colour color3
                 ) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse) // call the constructor on wavefor
{

    playButton.addListener(this);
    loadButton.addListener(this);
    pauseButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.5, 100.0);
    posSlider.setRange(0.0, 1.0);
    
    volSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setNumDecimalPlacesToDisplay(2);
    
    

    addAndMakeVisible (volLabel);
    volLabel.setText ("Volume", juce::dontSendNotification);
    volLabel.attachToComponent (&volSlider, true); // [4]
    
    addAndMakeVisible (speedLabel);
    speedLabel.setText ("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent (&speedSlider, true); // [4]
    
    addAndMakeVisible (posLabel);
    posLabel.setText ("Position", juce::dontSendNotification);
    posLabel.attachToComponent (&posSlider, true); // [4]

    
    addAndMakeVisible(waveformDisplay);
    waveformDisplay.setColor(color1);
    
    startTimer(200);
    
    
   

    //Image playImage = ImageCache::getFromFile(f);
    const auto playImage = ImageCache::getFromMemory (BinaryData::play_png, BinaryData::play_pngSize);
    
    
    const auto loadImage = ImageCache::getFromMemory(BinaryData::upload_png, BinaryData::upload_pngSize);
    
    const auto pauseImage = ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize);

    
    playButton.setImages (true, true, true, playImage, 1.0f, color1, playImage, 1.0f, color2, playImage, 1.0f, color3);
    
    pauseButton.setImages (true, true, true, pauseImage, 1.0f, color1, pauseImage, 1.0f, color2, pauseImage, 1.0f, color3);
    
    loadButton.setImages (true, true, true, loadImage, 1.0f, color1, loadImage, 1.0f, color2, loadImage, 1.0f, color3);
    

    addAndMakeVisible(playButton);
    addAndMakeVisible(pauseButton);
    addAndMakeVisible(loadButton);
       
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    playButton.setBounds(0, rowH*0.1, getWidth()/8, rowH*0.8);
    pauseButton.setBounds(getWidth()/8, rowH*0.1, getWidth()/8, rowH*0.8);
    loadButton.setBounds((getWidth()/8)*2, rowH*0.1, getWidth()/8, rowH*0.8);
    volSlider.setBounds(60, rowH, getWidth()-60, rowH);
    speedSlider.setBounds(60, rowH * 2, getWidth()-60, rowH);
    posSlider.setBounds(60, rowH * 3, getWidth()-60, rowH);
    waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);

}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &pauseButton)
    {
        std::cout << "Pause button was clicked " << std::endl;
        player->stop();

    }
    if (button == &loadButton)
    {
        FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()});
        }
    }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
    

