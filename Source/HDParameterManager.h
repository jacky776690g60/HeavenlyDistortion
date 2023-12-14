/* =================================================================
| ParameterManager.h  --  Source/ParameterManager.h
|
| Created by Jack on 12/03, 2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */

# pragma once

#include <JuceHeader.h>

#include <utilities/managers/include/ParameterManager.h>

class HDParameterManager : public ParameterManager
{
public:
    /** 
     * inherits constructors from the ParameterManager class 
     * Without this declaration, only the constructors you explicitly define in HDParameterManager will be available.
     */
    using ParameterManager::ParameterManager;

    /** Explicitly define a consturctor */
    // HDParameterManager(
    //     juce::AudioProcessor& p,
    //     juce::UndoManager* undoManager = nullptr, 
    //     const juce::String& valueTreeID = "PARAMETERS"
    // ) : ParameterManager(p, undoManager, valueTreeID) {}
    
    virtual ~HDParameterManager() override = default;



    virtual juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() override
    {
        return {
            // ~~~~~~~~ main sliders ~~~~~~~~
            makeParam_int(  "distortionAlgo",     1,   1,         9,        1),
            makeParam_float("gain",               1,   -36.0f,    36.0f,    0.0f),
            makeParam_float("outputLevel",        1,   -36.0f,    36.0f,    -3.0f),
            makeParam_float("tone",               1,   -1.0f,     1.0f,     0.0f),
            makeParam_float("Q",                  1,   0.3f,      12.0f,    1.0f),
            // ~~~~~~~~ algo specific sliders ~~
            makeParam_float("threshold",          1,   0.01f,     1.0f,     .85f),
            makeParam_float("kneeWidth",          1,   0.01f,     1.0f,     .25f),
            makeParam_float("drive",              1,   0.01f,     6.0f,     1.00f),
            makeParam_float("ratio",              1,   0.01f,     1.0f,     1.0f),
            makeParam_int(  "bit",                1,   1,         13,       2),
            makeParam_float("algoTone",           1,   0.00f,      1.0f,     .5f),
        };
    }
};