/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "BalanceController.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer fxPlayer1{formatManager};
    DeckGUI deckGUI1{&player1, &fxPlayer1, formatManager, thumbCache, {Colour(0xFFFF1832)}, {Colour(0xFFB40A14)},  {Colour(0xFFA00508)}, true};
    DJAudioPlayer player2{formatManager};
    DJAudioPlayer fxPlayer2{formatManager};
    DeckGUI deckGUI2{&player2, &fxPlayer2, formatManager, thumbCache, {Colour(0xFF0A14C8)}, {Colour(0xFF0A14AA)}, {Colour(0xFF0A1496)}, false};
    MixerAudioSource mixerSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    Viewport viewportPlaylist;
    PlaylistComponent playlistComponent{&viewportPlaylist};
    BalanceController balanceController{&player1, &fxPlayer1, &player2, &fxPlayer2};
};
