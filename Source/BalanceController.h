/*
  ==============================================================================

    BalanceController.h
    Created: 28 Feb 2022 8:17:07pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BalanceController  : public juce::Component,
public Slider::Listener
{
public:
    BalanceController();
    ~BalanceController() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

private:
    Slider slider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceController)
};
