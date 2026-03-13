
namespace tremolo {
  namespace {
    juce::AudioParameterFloat& creatModulationRateParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      auto parameter = std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"modulation.rate", versionHint},
        "modulation rate",
        juce::NormalisableRange<float>{
          0.1f,
          20.f,
          0.01f,
          0.4f,
        },
        5.f,
        juce::AudioParameterFloatAttributes{}.withLabel("Hz")
        );
      auto& parameterReference = *parameter;
      processor.addParameter(parameter.release());
      return parameterReference;
    }
  }
Parameters::Parameters(juce::AudioProcessor& processor) : rate{creatModulationRateParameter((processor))}
// TODO: create parameters
// TODO: retrieve references to parameters
// TODO: add parameters to the processor
{
  // juce::ignoreUnused(processor);
}
}  // namespace tremolo
