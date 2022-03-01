/*
  ==============================================================================

    BalanceController.cpp
    Created: 28 Feb 2022 8:17:07pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BalanceController.h"

//==============================================================================
BalanceController::BalanceController(DJAudioPlayer* p1, DJAudioPlayer* p2)
: player1(p1),
player2(p2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
  

    slider.setRange(-1.0, 1.0);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setLookAndFeel (&lookAndFeel);
    addAndMakeVisible(slider);
    slider.addListener(this);
    


}

BalanceController::~BalanceController()
{
}

void BalanceController::sliderValueChanged (Slider *slider)
{
    double balance = slider->getValue();
    double p1_gain = 1;
    double p2_gain = 1;
    DBG("BALANCE: " + std::to_string(balance));
    
    if(balance > 0){
        p1_gain = 1- balance;
    }
    else if(balance < 0){
        p2_gain = 1 - (balance * -1);
    }
    player1->setGain(p1_gain);
    player2->setGain(p2_gain);
    
}

void BalanceController::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

}

void BalanceController::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    int SLIDER_WIDTH = getWidth()/2;
    slider.setBounds(getWidth()/2 - SLIDER_WIDTH/2, 0, SLIDER_WIDTH, getHeight());
}
