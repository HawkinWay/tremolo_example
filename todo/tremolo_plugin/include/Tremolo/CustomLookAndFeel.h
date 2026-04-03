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
private:
    static juce::FontOptions SairaStencilMedium();
};
}  // namespace tremolo