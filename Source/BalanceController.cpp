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
BalanceController::BalanceController()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(slider);
    slider.addListener(this);

    slider.setRange(-1.0, 1.0);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


}

BalanceController::~BalanceController()
{
}

void BalanceController::sliderValueChanged (Slider *slider)
{
  
    
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
