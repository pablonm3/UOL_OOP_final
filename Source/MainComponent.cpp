/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    formatManager.registerBasicFormats();

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    viewportPlaylist.setViewedComponent(&playlistComponent, false);
    
    addAndMakeVisible(deckGUI1); 
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(viewportPlaylist);
    addAndMakeVisible(balanceController);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    fxPlayer1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    fxPlayer2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
//    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    mixerSource.addInputSource(&fxPlayer1, false);
    mixerSource.addInputSource(&fxPlayer2, false);

 }
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    fxPlayer1.releaseResources();
    fxPlayer2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    // You can add your drawing code here!
}

void MainComponent::resized()
{    
    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight() / 2);
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight() / 2);
    balanceController.setBounds(0, getHeight()/2, getWidth(), getHeight()/10);
   // playlistComponent.setBounds(0, getHeight() * 0.6, getWidth(), getHeight()/2);
    viewportPlaylist.setBounds(0, getHeight() * 0.6, getWidth(), getHeight()/2);

    playlistComponent.setSize(viewportPlaylist.getWidth() + 1, viewportPlaylist.getHeight() + 1); // with this size you will be able to scroll around with 1x1 pixel offset

}


