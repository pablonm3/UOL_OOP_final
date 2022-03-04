/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "LookAndFeelSlider.h"
#include "Filename.h"
#include "FxButtons.h"



//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget,
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
    AudioFormatManager & formatManagerToUse,
    AudioThumbnailCache & cacheToUse,
    Colour color1,
    Colour color2,
    Colour color3,
    bool _is_left);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override;
    void timerCallback() override;



private:

    ImageButton playButton;
    ImageButton pauseButton;
    ImageButton loadButton;
    
    LookAndFeelSlider lookAndFeel{true};
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    juce::Label posLabel;
    juce::Label speedLabel;

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;
    FileName filenameScreen;
    FxButtons fxButtons;
    
    bool is_left;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
