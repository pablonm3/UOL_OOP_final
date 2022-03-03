/*
  ==============================================================================

    FileName.h
    Created: 2 Mar 2022 7:49:35pm
    Author:  Pablo N. Marino

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FileName  : public juce::Component
{
public:
    FileName();
    ~FileName() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setFilename(String f);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileName)
    
    String filename="-";
    
};
