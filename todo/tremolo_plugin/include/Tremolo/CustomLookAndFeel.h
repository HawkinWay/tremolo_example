#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawToggleButton(juce::Graphics &,
                          juce::ToggleButton &,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;
    
    static juce::FontOptions getSideLabelsFont(){
        return SairaStencilMedium().withPointHeight(10.f);
    }

    void drawRotarySlider(juce::Graphics&,
                          int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider&) override;
private:
    static juce::FontOptions SairaStencilMedium();
};
}  // namespace tremolo