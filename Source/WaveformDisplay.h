/*
  ==============================================================================

    WaveformDIsplay.h
    Created: 12 Feb 2022 9:43:23pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & formatManagerToUse,
    AudioThumbnailCache & cacheToUse );
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void loadURL(URL audioURL);
    void changeListenerCallback (ChangeBroadcaster *source) override;
    /** set the relative position of the play head*/
    void setPositionRelative(double pos);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay);
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;
};
