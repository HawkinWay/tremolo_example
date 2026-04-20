namespace tremolo {
class LfoVisualizer : public juce::Component {
public:
    enum class LfoWaveform : size_t {
        sine = 0,
        triangle = 1,
        square = 2,
        sawtooth = 3,
    };

    void setLfoWaveform(LfoWaveform lfoWaveform) {
        jassert(lfoWaveform == LfoWaveform::sine || lfoWaveform == LfoWaveform::triangle ||
            lfoWaveform == LfoWaveform::square || lfoWaveform == LfoWaveform::sawtooth);
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
        // if (lfoToSet == LfoWaveform::sine) {
        //     g.strokePath(lfosPath[0],juce::PathStrokeType{strokeWidth});
        // }
        // else if (lfoToSet == LfoWaveform::triangle) {
        //     g.strokePath(lfosPath[1],juce::PathStrokeType{strokeWidth});
        // }
        // else if (lfoToSet == LfoWaveform::square) {
        //     g.strokePath(lfosPath[2],juce::PathStrokeType{strokeWidth});
        // }
        // else if (lfoToSet == LfoWaveform::sawtooth) {
        //     g.strokePath(lfosPath[3], juce::PathStrokeType{strokeWidth});
        // }
        auto idx = static_cast<size_t>(lfoToSet);
        if (idx < lfosPath.size()) {
            g.strokePath(lfosPath[idx], juce::PathStrokeType{strokeWidth});
        }
    }

    void resized() override {
        for (auto &lfo : lfosPath) {
            lfo.clear();
        }
        const auto halfHeight = getHeight() / 2;
        const auto amplitude = halfHeight - (strokeWidth / 2.f);
        const auto extra = getWidth();

        // sine.startNewSubPath(-extra, halfHeight + amplitude * std::sin(0.1 * (-extra)));
        // triangle.startNewSubPath(-extra, halfHeight + amplitude * Tremolo::triangle(0.1 * (-extra)));
        // square.startNewSubPath(-extra, halfHeight + amplitude * Tremolo::square(0.1 * (-extra)));
        // sawtooth.startNewSubPath(-extra, halfHeight + amplitude * Tremolo::sawtooth(0.1 * (-extra)));
        for (auto i = 0; i < lfosPath.size(); i++) {
            lfosPath[i].startNewSubPath(-extra, halfHeight + amplitude * waveFunctions[i](0.1 * (-extra)));
        }

        for (const auto i : std::views::iota(1 - extra, getWidth() + extra)) {
            // sine.lineTo(i, halfHeight + amplitude * std::sin(0.1 * i));
            // triangle.lineTo(i, halfHeight + amplitude * Tremolo::triangle(0.1 * i));
            // square.lineTo(i, halfHeight + amplitude * Tremolo::square(0.1 * i));
            // sawtooth.lineTo(i, halfHeight + amplitude * Tremolo::sawtooth(0.1 * i));
            for (auto j = 0; j < lfosPath.size(); j++) {
                lfosPath[j].lineTo(i, halfHeight + amplitude * waveFunctions[j](0.1 * i));
            }
        }
    }

    void setStrokeWidth(float strokeWidth) {
        this->strokeWidth = strokeWidth;
    }

private:
    using waveformFunc = float(*)(float);

    // ERROR!!
    // std::array<juce::Path, 4u> lfosPath{
    //     juce::Path sine,
    //     juce::Path triangle,
    //     juce::Path square,
    //     juce::Path sawtooth,
    // }；

    std::array<juce::Path, 4u> lfosPath;

    const std::array<waveformFunc, 4u> waveFunctions{
        std::sin,
        Tremolo::triangle,
        Tremolo::square,
        Tremolo::sawtooth,
    };

    float strokeWidth = 4.f;
    LfoWaveform currentLfo = LfoWaveform::sine;
    LfoWaveform lfoToSet = currentLfo;
};
}