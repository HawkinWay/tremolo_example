#pragma once

namespace tremolo {
struct Parameters {
  explicit Parameters(juce::AudioProcessor&);   //explicit the single-argument construction is a good practice
                    //juce::AudioProcessor&: name can be omitted in function declarations
  juce::AudioParameterFloat& rate;

  juce::AudioParameterFloat& gain;

  juce::AudioParameterFloat& modulationDepth;

  juce::AudioParameterBool& bypassed;

  juce::AudioParameterChoice& waveform;

  JUCE_DECLARE_NON_COPYABLE(Parameters)

  JUCE_DECLARE_NON_MOVEABLE(Parameters)

};
}  // namespace tremolo
