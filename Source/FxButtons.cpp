/*
  ==============================================================================

    FxButtons.cpp
    Created: 2 Mar 2022 10:46:58pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxButtons.h"

//==============================================================================
FxButtons::FxButtons(Colour color1,
                     Colour color2,
                     Colour color3,
                     DJAudioPlayer* _player)
: player(_player)
{
    
    
    fx1Button.addListener(this);
    fx2Button.addListener(this);
    fx3Button.addListener(this);
    fx4Button.addListener(this);
    fx5Button.addListener(this);
    fx6Button.addListener(this);
    addAndMakeVisible(fx1Button);
    addAndMakeVisible(fx2Button);
    addAndMakeVisible(fx3Button);
    addAndMakeVisible(fx4Button);
    addAndMakeVisible(fx5Button);
    addAndMakeVisible(fx6Button);
    const auto fxImage = ImageCache::getFromMemory(BinaryData::fx_png, BinaryData::fx_pngSize);
    
    fx1Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    fx2Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    fx3Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    fx4Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    fx5Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    fx6Button.setImages (true, true, true, fxImage, 1.0f, color1, fxImage, 1.0f, color2, fxImage, 1.0f, color3);
    
    
}

FxButtons::~FxButtons()
{
}

void FxButtons::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void FxButtons::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight();
    double col = getWidth()/8;
    fx1Button.setBounds(0, 0, getWidth()/8, rowH*0.8);
    fx2Button.setBounds(col, 0, getWidth()/8, rowH*0.8);
    fx3Button.setBounds(col*2, 0, getWidth()/8, rowH*0.8);
    fx4Button.setBounds(col*3, 0, getWidth()/8, rowH*0.8);
    fx5Button.setBounds(col*4, 0, getWidth()/8, rowH*0.8);
    fx6Button.setBounds(col*5, 0, getWidth()/8, rowH*0.8);
}


void FxButtons::buttonClicked(Button* button)
{
    if (button == &fx1Button)
   {
       player->loadFromBinary(BinaryData::fx1_wav, BinaryData::fx1_wavSize);
       player->start();
   }
    if (button == &fx2Button)
   {
       player->loadFromBinary(BinaryData::fx2_wav, BinaryData::fx2_wavSize);
       player->start();
   }
    if (button == &fx3Button)
   {
       player->loadFromBinary(BinaryData::fx3_wav, BinaryData::fx3_wavSize);
       player->start();
   }
    if (button == &fx4Button)
   {
       player->loadFromBinary(BinaryData::fx4_wav, BinaryData::fx4_wavSize);
       player->start();
   }
    if (button == &fx5Button)
   {
       player->loadFromBinary(BinaryData::fx5_wav, BinaryData::fx5_wavSize);
       player->start();
   }
    if (button == &fx6Button)
   {
       player->loadFromBinary(BinaryData::fx6_wav, BinaryData::fx6_wavSize);
       player->start();
   }
    
}
