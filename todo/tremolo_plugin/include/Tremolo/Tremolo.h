#pragma once

namespace tremolo {
class Tremolo {
public:
  enum class LfoWaveform : size_t {
    sine = 0,
    triangle = 1,
  };

  Tremolo() {
    for (auto &lfo : lfos) {
      lfo.setFrequency(5.f, true);
    }
  }

  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    //juce::ignoreUnused(sampleRate, expectedMaxFramesPerBlock);
    juce::dsp::ProcessSpec processSpec{
        .sampleRate = sampleRate,
        .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
        .numChannels = 1u,
    };
    for (auto &lfo : lfos) {
      lfo.prepare(processSpec);
    }
    smoothWaveform.reset(sampleRate, 0.02);     //20ms
    smoothWaveform.setCurrentAndTargetValue(0.f);

    smoothModulationDepth.reset(sampleRate, 0.02);
    smoothModulationDepth.setCurrentAndTargetValue(modulationDepth);
  }

  void setLfoWaveform(LfoWaveform waveform) {
    jassert(waveform == LfoWaveform::sine || waveform == LfoWaveform::triangle);
    lfoToSet = waveform;
  }

  void setModulationRate(float rateHz) {
    for (auto &lfo : lfos) {
      lfo.setFrequency(rateHz);
    }
  }

  void setModulationDepth(float depth) {
    modulationDepth = juce::jlimit(0.f,1.f,depth);
    smoothModulationDepth.setTargetValue(modulationDepth);
  }

  void process(juce::AudioBuffer<float>& buffer) noexcept {
    // for each frame
    updateLfoWaveform();
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
      // generate the LFO value
      const auto lfoValue = getNextLfoValue();

      // calculate the modulation value
      // constexpr auto modulationDepth = 0.4f;
      const auto modulationDepthValue = smoothModulationDepth.getNextValue();
      const auto modulationValue = (modulationDepthValue * lfoValue) + 1.f;

      // for each channel sample in the frame
      for (const auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        // modulate the sample
        const auto outputSample = inputSample * modulationValue;

        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }
    }
  }

  void reset() noexcept {
    for (auto &lfo : lfos) {
      lfo.reset();
    }
  }

  static float triangle(float phase) {
    const auto ft = phase / juce::MathConstants<float>::twoPi;
    return 4.f * std::abs(ft - std::floor(ft + 0.5f)) - 1.f;
  }

private:
  // You should put class members and private functions here

  std::array<juce::dsp::Oscillator<float>, 2u> lfos{
    juce::dsp::Oscillator<float>{ [](auto phase){ return std::sin(phase); }},
    juce::dsp::Oscillator<float>{ triangle },
  };

  void updateLfoWaveform() {
    if (currentLfo != lfoToSet) {
      currentLfo = lfoToSet;
      if (currentLfo == LfoWaveform::sine) {
        smoothWaveform.setTargetValue(0.f);
      }
      else {
        smoothWaveform.setTargetValue(1.f);
      }
    }
  }

  LfoWaveform currentLfo = LfoWaveform::sine;
  LfoWaveform lfoToSet = currentLfo;

  float getNextLfoValue() {
    const auto sineValue = lfos[0].processSample(0.f);
    const auto triangleValue = lfos[1].processSample(0.f);

    const auto waveformMix = smoothWaveform.getNextValue();

    //return lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
    return ((1.f - waveformMix) * sineValue) + ( waveformMix * triangleValue) ;
  }

  // Stretch Assignment 3.01. Implement smoothing when switching the LFO waveform
  juce::SmoothedValue<float> smoothWaveform;

  // Stretch Assignment 4.03. Implement a modulation depth parameter
  float modulationDepth = 0.4f;
  juce::SmoothedValue<float> smoothModulationDepth;

};
}  // namespace tremolo
