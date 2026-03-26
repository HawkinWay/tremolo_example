#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent logo;
  // assignment 5.0.2
  // juce::ImageComponent logo2;
  // juce::ImageComponent logo3;

  juce::Slider rateSlider;
  // Stretch Assignment 5.02. Add a slider to control the width of the LFO curve
  juce::Slider lfoCurveWidthSlider;
  LfoVisualizer lfoVisualizer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
