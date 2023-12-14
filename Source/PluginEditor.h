/* =================================================================
| PluginEditor.h  --  Source/PluginEditor.h
|
| Created by Jack on 12/03, 2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include <components/RotaryKnob/include/RotaryKnob.h>
#include <utilities/DBConverter.h>
#include <utilities/Colors.h>


class HeavenlyDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HeavenlyDistortionAudioProcessorEditor (HeavenlyDistortionAudioProcessor&);
    ~HeavenlyDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ComboBox algorithmSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> algoSelectorAttachment;
    
    // ~~~~~~~~ main sliders ~~~~~~~~
    RotaryKnob gainSlider;
    RotaryKnob outputLevelSlider;
    RotaryKnob toneSlider;
    RotaryKnob qSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> qAttachment;
    
    // ~~~~~~~~ algo specific sliders ~~~~~~~~
    RotaryKnob thresholdSlider;
    RotaryKnob kneeWidthSlider;
    RotaryKnob driveSlider;
    RotaryKnob ratioSlider;
    RotaryKnob bitSlider;
    RotaryKnob algotoneSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> kneeWidthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bitAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> algotoneAttachment;

private:
    juce::Image logoImage;
    juce::Label algorithmLabel;

    void algorithmChanged();

    /** This reference is provided as a quick way for your editor to access the processor object that created it. */
    HeavenlyDistortionAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeavenlyDistortionAudioProcessorEditor)
};
