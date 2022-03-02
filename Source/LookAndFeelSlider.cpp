/*
  ==============================================================================

    LookAndFeelSlider.cpp
    Created: 1 Mar 2022 5:26:42pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LookAndFeelSlider.h"

//==============================================================================
LookAndFeelSlider::LookAndFeelSlider(bool _isSmall)
: isSmall(_isSmall)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
   // setColour (juce::Slider::thumbColourId, juce::Colours::red);
}

LookAndFeelSlider::~LookAndFeelSlider()
{
}

void LookAndFeelSlider::drawRoundThumb (Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness, bool isVertical)
    {
        auto halfThickness = outlineThickness * 0.5f;
        double thumb_height = (diameter - outlineThickness) * 1.5;
        double thumb_width = (diameter - outlineThickness) * 0.8;
        if(isSmall){
            thumb_height = thumb_height * 0.8;
            thumb_width = thumb_width * 0.8;
        }
        Path p;
        Path p_line;
        if(isVertical == true){
            double aux = thumb_height;
            thumb_height = thumb_width;
            thumb_width = aux;
            p.addRectangle (x+thumb_width-thumb_width/2,
                            y-thumb_height/5,
                            thumb_width,
                            thumb_height);
        
            p_line.addRectangle (x-thumb_width/6,
                        y-thumb_height/4,
                        thumb_width,
                        2);
        }
        else{
            p.addRectangle (x,
                            y-thumb_height/6,
                            thumb_width,
                            thumb_height);
        
            p_line.addRectangle (x+(thumb_width/2) -1,
                        y-thumb_height/6,
                        2,
                        thumb_height);
        }
       // const auto thumbImage = ImageCache::getFromMemory(BinaryData::thumb_png, BinaryData::thumb_pngSize);
       // g.drawImageAt(thumbImage, x + halfThickness,
         //                       y + halfThickness,
           //                     diameter - outlineThickness,
             //         diameter - outlineThickness);

        
        DropShadow (Colours::black, 1, {}).drawForPath (g, p);
        colour = Colour::fromRGB(170, 169, 173);
        g.setColour (colour);
        g.fillPath (p);
        g.setColour (colour.brighter());
        g.strokePath (p, PathStrokeType (outlineThickness));
    
        g.setColour (Colour::fromRGB(140, 139, 143));
        g.fillPath (p_line);
    }


void LookAndFeelSlider::drawLinearSliderThumb    (    Graphics& g,
int     x,
int     y,
int     width,
int     height,
float     sliderPos,
float     minSliderPos,
float     maxSliderPos,
const Slider::SliderStyle style,
Slider& slider
)
{
    auto sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

           auto isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());

           auto knobColour = slider.findColour (Slider::thumbColourId)
                                   .withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                                   .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f);

           if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
           {
               float kx, ky;

               if (style == Slider::LinearVertical)
               {
                   kx = (float) x + (float) width * 0.5f;
                   ky = sliderPos;
               }
               else
               {
                   kx = sliderPos;
                   ky = (float) y + (float) height * 0.5f;
               }

               auto outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;
              
               drawRoundThumb (g,
                               kx - sliderRadius,
                               ky - sliderRadius,
                               sliderRadius * 2.0f,
                               knobColour, outlineThickness,
                               style == Slider::LinearVertical);
               }
           else
           {
               // Just call the base class for the demo
               LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
           }
}

void LookAndFeelSlider::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider)
    {
       // g.fillAll (slider.findColour (Slider::backgroundColourId));

   
      drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
      drawLinearSliderThumb      (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
