/*
  ==============================================================================

    BalanceController.h
    Created: 28 Feb 2022 8:17:07pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "LookAndFeelSlider.h"

//==============================================================================
/*
*/
class BalanceController  : public juce::Component,
public Slider::Listener
{
public:
    BalanceController(DJAudioPlayer* p1, DJAudioPlayer* p2);
    ~BalanceController() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

private:
    LookAndFeelSlider lookAndFeel;
    Slider slider;
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceController)
};
