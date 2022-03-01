/*
  ==============================================================================

 WaveformDisplay.cpp
    Created: 12 Feb 2022 9:43:23pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================

WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse,
AudioThumbnailCache & cacheToUse)
:
audioThumbnail(1000, formatManagerToUse, cacheToUse),
fileLoaded(false),
position(0)
{
    audioThumbnail.addChangeListener(this);
}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::setColor(Colour color)
{
    waveformColor = color;
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    g.setColour (waveformColor);
    if(fileLoaded)
    {
        audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1);
        g.setColour(Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont (20.0f);
        g.drawText ("File not loaded...", getLocalBounds(), Justification::centred, true); // draw some placeholder text
    }
}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    DBG("wfd: change received! " );
    repaint();
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}
