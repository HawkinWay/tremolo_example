namespace tremolo {
class LfoVisualizer : public juce::Component {
public:
    void paint(juce::Graphics& g) override {
        /* juce::Path line;
        // line.startNewSubPath(0,0);
        // line.lineTo(getWidth(),getHeight());
        // g.strokePath(line, juce::PathStrokeType{4.f});
        // juce::Path sine;
        //
        // const auto strokeWidth = 4.f;
        // const auto halfHeight = getHeight() / 2;
        // const auto amplitude = halfHeight - strokeWidth / 2.f;
        //
        // const auto extra = getWidth();
        //
        // sine.startNewSubPath(-extra,halfHeight + amplitude * std::sin(0.1 * (-extra)));
        //
        // for (const auto i : std::views::iota(1 - extra,getWidth() + extra)) {
        //     sine.lineTo(i,halfHeight + amplitude * std::sin(0.1 * i));
        */
        g.setColour((juce::Colours::lightpink));
        g.strokePath(sine,juce::PathStrokeType{strokeWidth});
    }

    void resized() override {
        sine.clear();
        const auto halfHeight = getHeight() / 2;
        const auto amplitude = halfHeight - (strokeWidth / 2.f);
        const auto extra = getWidth();
        sine.startNewSubPath(-extra, halfHeight + amplitude * std::sin(0.1 * (-extra)));
        for (const auto i : std::views::iota(1 - extra, getWidth() + extra)) {
            sine.lineTo(i, halfHeight + amplitude * std::sin(0.1 * i));
        }
    }

private:
    juce::Path sine;
    float strokeWidth = 4.f;
};
}