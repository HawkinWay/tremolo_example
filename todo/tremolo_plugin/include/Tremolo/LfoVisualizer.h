namespace tremolo {
class LfoVisualizer : public juce::Component {
public:
    enum class LfoWaveform : size_t {
        sine = 0,
        triangle = 1,
    };

    void setLfoWaveform(LfoWaveform lfoWaveform) {
        jassert(lfoWaveform == LfoWaveform::sine || lfoWaveform == LfoWaveform::triangle);
        lfoToSet = lfoWaveform;
    }

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
        if (lfoToSet == LfoWaveform::sine) {
            g.strokePath(sine,juce::PathStrokeType{strokeWidth});
        }
        else {
            g.strokePath(triangle,juce::PathStrokeType{strokeWidth});
        }
    }

    void resized() override {
        sine.clear();
        triangle.clear();
        const auto halfHeight = getHeight() / 2;
        const auto amplitude = halfHeight - (strokeWidth / 2.f);
        const auto extra = getWidth();

        sine.startNewSubPath(-extra, halfHeight + amplitude * std::sin(0.1 * (-extra)));
        triangle.startNewSubPath(-extra, halfHeight + amplitude * Tremolo::triangle(0.1 * (-extra)));

        for (const auto i : std::views::iota(1 - extra, getWidth() + extra)) {
            sine.lineTo(i, halfHeight + amplitude * std::sin(0.1 * i));
            triangle.lineTo(i, halfHeight + amplitude * Tremolo::triangle(0.1 * i));
        }
    }

    void setStrokeWidth(float strokeWidth) {
        this->strokeWidth = strokeWidth;
    }

private:
    juce::Path sine;
    juce::Path triangle;

    float strokeWidth = 4.f;
    LfoWaveform currentLfo = LfoWaveform::sine;
    LfoWaveform lfoToSet = currentLfo;
};
}