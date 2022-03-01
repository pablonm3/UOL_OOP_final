/*
  ==============================================================================

    LookAndFeelSlider.h
    Created: 1 Mar 2022 5:26:42pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LookAndFeelSlider  : public juce::LookAndFeel_V4
{
public:
    LookAndFeelSlider();
    ~LookAndFeelSlider() override;
    
    void drawLinearSliderThumb(Graphics& g,
                                int     x,
                                int     y,
                                int     width,
                                int     height,
                                float     sliderPos,
                                float     minSliderPos,
                                float     maxSliderPos,
                                const Slider::SliderStyle style,
                                Slider& slider) override;
    
    void drawRoundThumb (Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness);
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                               float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override;
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeelSlider)
};
