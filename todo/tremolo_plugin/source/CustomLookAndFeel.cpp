namespace tremolo {
    void CustomLookAndFeel::drawToggleButton(juce::Graphics &g,
                                                 juce::ToggleButton & button,
                                                 bool shouldDrawButtonAsHighlighted,
                                                 bool shouldDrawButtonAsDown) {
        const auto bounds = button.getLocalBounds().reduced(2);

        if (button.getToggleState()) {
            if (shouldDrawButtonAsHighlighted == true) {
                auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xB2FF901A},
                                                                 juce::Colour{0xB2FFC300},bounds);
                g.setGradientFill(buttonGradient);
                g.fillRoundedRectangle(bounds.toFloat(),4.f);
                g.setColour(juce::Colour{0xB250180B});
            }
            else {
                auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFFFF901A},
                                                                 juce::Colour{0xFFFFC300},bounds);
                g.setGradientFill(buttonGradient);
                g.fillRoundedRectangle(bounds.toFloat(),4.f);
                g.setColour(juce::Colour{0xFF50180B});
            }
        }
        else {
            if (shouldDrawButtonAsHighlighted == true) {
                auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xB24A7090},
                                                                 juce::Colour{0xB2324358},bounds);
                buttonGradient.addColour(0.73,juce::Colour{0xFF315160});
                g.setGradientFill(buttonGradient);
                g.fillRoundedRectangle(bounds.toFloat(),4.f);
                g.setColour(juce::Colour{0xB2DDECFF});
            }
            else {
                auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFF4A7090},
                                                                 juce::Colour{0xFF324358},bounds);
                buttonGradient.addColour(0.73,juce::Colour{0xFF315160});
                g.setGradientFill(buttonGradient);
                g.fillRoundedRectangle(bounds.toFloat(),4.f);
                g.setColour(juce::Colour{0xFFDDECFF});
            }
        }
        const auto outlineBounds = button.getLocalBounds().reduced(2);
      //g.setColour(juce::Colour{0xFF042D4E});
        g.setColour(juce::Colour{0xFF000000});
        g.drawRoundedRectangle(outlineBounds.toFloat(),4.f,2.f);

        // g.setFont(juce::FontOptions{
        //     juce::Typeface::createSystemTypefaceFor(assets::SairaStencil_CondensedMedium_ttf, assets::SairaStencil_CondensedMedium_ttfSize)
        // }.withPointHeight(12.f));
        g.setFont(SairaStencilMedium().withPointHeight(12.f));
        DBG(g.getCurrentFont().getTypefacePtr()->getName());
        g.drawText(button.getButtonText(),bounds,juce::Justification::centred, false);

    }

    juce::FontOptions CustomLookAndFeel::SairaStencilMedium(){
            static const auto result = juce::Typeface::createSystemTypefaceFor(assets::SairaStencil_ExpandedMedium_ttf, assets::SairaStencil_ExpandedMedium_ttfSize);
            return juce::FontOptions{result};
    }

}  // namespace tremolo