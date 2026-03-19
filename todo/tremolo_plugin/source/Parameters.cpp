
namespace tremolo {
  namespace {
    auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
      auto& parameterReference = *parameter;
      processor.addParameter(parameter.release());
      return parameterReference;
    }
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
      // auto& parameterReference = *parameter;
      // processor.addParameter(parameter.release());
      // return parameterReference;
      return addParameterToProcessor(processor, std::move(parameter));
    }

    juce::AudioParameterFloat* createGainParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      auto parameter = new juce::AudioParameterFloat(
        juce::ParameterID{"gain", versionHint},
        "Gain",
        juce::NormalisableRange<float>{-12.f,12.f,0.1f},
        0.f,
        juce::AudioParameterFloatAttributes{}.withLabel("dB")
        );
      //auto& parameterReference = *parameter;
      processor.addParameter(parameter);
      return parameter;
    }

    juce::AudioParameterBool& createBypassedParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      auto parameter = std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{"bypassed", versionHint},
        "Bypass",
        false
        );
      return addParameterToProcessor(processor, std::move(parameter));
    }

    juce::AudioParameterChoice& createWaveformParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      auto parameter = std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"modulation.waveform", versionHint},
        "Modulation waveform",
        juce::StringArray{"Sine", "Triangle"},
        0
        );
      return addParameterToProcessor(processor, std::move(parameter));
    }
  }

  Parameters::Parameters(juce::AudioProcessor& processor) : rate{creatModulationRateParameter((processor))},
  gain{createGainParameter(processor)}, bypassed{createBypassedParameter(processor)}, waveform{createWaveformParameter(processor)}
  // create parameters
  // retrieve references to parameters
  // add parameters to the processor
  {
    // juce::ignoreUnused(processor);
  }
}  // namespace tremolo
