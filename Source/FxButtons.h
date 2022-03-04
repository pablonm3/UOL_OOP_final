/*
  ==============================================================================

    FxButtons.h
    Created: 2 Mar 2022 10:46:58pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FxButtons  : public juce::Component,
                   public Button::Listener
{
public:
    FxButtons(Colour color1,
              Colour color2,
              Colour color3);
    ~FxButtons() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
   void buttonClicked (Button *) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxButtons)
    
    ImageButton fx1Button;
    ImageButton fx2Button;
    ImageButton fx3Button;
    ImageButton fx4Button;
    ImageButton fx5Button;
    ImageButton fx6Button;
};
