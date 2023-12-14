/* =================================================================
| PluginProcessor.h  --  HeavenlyDistortion
|
| Created by Jack on 21/09/2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */
#pragma once

#include <JuceHeader.h>

#include <DSP/ClippingAlgorithms/Clipping.h>
#include <DSP/DistortionAlgorithms/Distortion.h>
#include <DSP/MultiBandEQ/include/MultiBandEQ.h>

#include "HDParameterManager.h"

class HeavenlyDistortionAudioProcessor  :
    public juce::AudioProcessor
    #if JucePlugin_Enable_ARA
    , public juce::AudioProcessorARAExtension
    #endif
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    // ==============================
    // Constructor
    // ==============================
    HeavenlyDistortionAudioProcessor();
    ~HeavenlyDistortionAudioProcessor() override;


    // ==============================
    // Override
    // ==============================
    /** Name of this processor */
    const juce::String getName() const override;
    /** audio (optionally MIDI) processing */
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;


    // ~~~~~~~~ Default MIDI ~~~~~~~~
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    // ~~~~~ Program Handling ~~~~~
    // deal with saving/loading the plugin's state
    // ~~~~~
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    /** Tells the source to prepare for playing. An AudioSource has two states: `prepared` and `unprepared`. */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    /** Allows the source to release anything it no longer needs after playback has stopped. */
    void releaseResources() override;

    #ifndef JucePlugin_PreferredChannelConfigurations
    /** This callback is called when the host probes the supported bus layouts via the checkBusesLayoutSupported method */
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    #endif

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /** 
     * Called when a float parameter's value changes
     * 
     * @note - typically used in conjunction with `juce::AudioProcessorValueTreeState::Listener`. 
     * This listener interface provides a way to respond to changes in parameters 
     * that are managed by an instance of `juce::AudioProcessorValueTreeState`.
     * @note - can be overloaded. This function is part of the `juce::AudioProcessorValueTreeState::Listener`
     * interface, which is used to respond to changes in parameters managed by 
     * an instance of `juce::AudioProcessorValueTreeState`.
     */
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    // ==========================
    // Variables
    // ==========================
    /** Available clipping algorithms*/
    enum DistortionAlgorithm {
        Clamping = 1,
        SoftClipping,
        HardClipping,
        TanhDistortion,
        WaveShaping,
        FoldbackDistortion,
        BitCrushing,
        Cubic,
        Overdrive,
    };

    HDParameterManager paramManager;

    // ==========================
    // getters & setters
    // ==========================
    /** Set which distortion algorithm to use */
    void setDistortionAlgorithm(DistortionAlgorithm alg) { currentAlgorithm = alg; };
    
private:
    /** JUCE macro that makes the class non-copyable and also adds a leak detector*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeavenlyDistortionAudioProcessor)
    
    // ==========================
    // utility
    // ==========================
    void addParameterListeners(const std::vector<juce::String>& paramIds);
    void removeParameterListeners(const std::vector<juce::String>& paramIds);

    /** Used for setting up parameters and when deconstructing the class */
    std::vector<juce::String> paramIDs = {
        "gain", "outputLevel", "tone", "Q", 
        "threshold", "kneeWidth", "drive", "algoTone", "ratio", "bit",
        "distortionAlgo"
    };
    
    /** built-in multi-band EQ for processing audio
     * @note be mindful of computational complexity */
    std::unique_ptr<MultiBandEQ> mMultiBandEQ;
    
    float gain, outputLevel, tone, Q;
    float threshold, kneeWidth, drive, ratio, algoTone;
    int bit;
    DistortionAlgorithm currentAlgorithm = Clamping;
};
