#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;
  void resized() override;

private:
  /*class RateSliderListener : public juce::Slider::Listener {
  public:
    RateSliderListener(juce::AudioParameterFloat& p,juce::Slider& s) : parameter(p), slider(s) {
      s.addListener(this);
    }
    ~RateSliderListener() override {
      slider.removeListener(this);
    }
    void sliderValueChanged(juce::Slider* s) override {
      parameter = static_cast<float>(s->getValue());
    }
  private:
    juce::AudioParameterFloat& parameter;
    juce::Slider& slider;
  };*/
  juce::ImageComponent background;
  juce::ImageComponent logo;
  // assignment 5.0.2
  // juce::ImageComponent logo2;
  // juce::ImageComponent logo3;

  //RateSlider rateSlider;
  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::ToggleButton bypassButton{"Bypassed"};
  juce::ButtonParameterAttachment bypassAttachment;

  // Stretch Assignment 5.03. Add a modulation depth slider
  juce::Slider depthSlider;
  juce::SliderParameterAttachment depthAttachment;
  // Stretch Assignment 5.02. Add a slider to control the width of the LFO curve
  juce::Slider lfoCurveWidthSlider;
  LfoVisualizer lfoVisualizer;

  CustomLookAndFeel lookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
