namespace tremolo {
    CustomLookAndFeel::CustomLookAndFeel() {
        setColour(juce::PopupMenu::backgroundColourId,juce::Colour{0xFF153245});
        setColour(juce::PopupMenu::textColourId,getColour(Colours::PaleBlue));
        setColour(juce::PopupMenu::highlightedBackgroundColourId,getColour(Colours::LightPink));
        setColour(juce::PopupMenu::highlightedTextColourId,juce::Colours::black);
        setColour(juce::ComboBox::textColourId,getColour(Colours::PaleBlue));
        setColour(juce::Label::textColourId,getColour(Colours::PaleBlue));
    }

    juce::Colour CustomLookAndFeel::getColour(Colours colourName) {
        static const std::array colours{juce::Colour{0xFFDDECFF}, juce::Colours::lightpink};
        return colours.at(juce::toUnderlyingType(colourName));
    }

    void CustomLookAndFeel::drawToggleButton(juce::Graphics &g,
                                                 juce::ToggleButton & button,
                                                 bool shouldDrawButtonAsHighlighted,
                                                 bool shouldDrawButtonAsDown) {
        juce::ignoreUnused (shouldDrawButtonAsDown);
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
                g.setColour(getColour(Colours::PaleBlue));
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

    void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                      int x, int y, int width, int height,
                      float sliderPosProportional, float rotaryStartAngle,
                      float rotaryEndAngle, juce::Slider&) {
        auto bounds = juce::Rectangle{x,y,width,height}.toFloat().reduced(3.75f);
        g.setColour(juce::Colour{0xFF2A3A3B});
        g.fillEllipse(bounds);

        auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        juce::Path valueArc;
        valueArc.addPieSegment(bounds.reduced(0.25f), rotaryStartAngle,
                                toAngle,0.f);
        g.setColour(juce::Colours::pink);
        g.fillPath(valueArc);

        // 5.13. Assignment 2
        auto bounds2 = juce::Rectangle{x,y,width,height}.toFloat().reduced(8.f);
        auto bounds2Gradient = juce::ColourGradient::vertical(juce::Colour{0xFF324358},
                                                        juce::Colour{0xFF1A2634}, bounds2);
        g.setGradientFill(bounds2Gradient);
        g.fillEllipse(bounds2);

        auto bounds3 = juce::Rectangle{x,y,width,height}.toFloat().reduced(15.f);
        auto bounds3Gradient = juce::ColourGradient::vertical(juce::Colour{0xFF5A7A9A},
                                                        juce::Colour{0xFF334471}, bounds3);
        g.setGradientFill(bounds3Gradient);
        g.fillEllipse(bounds3);
    }

    juce::FontOptions CustomLookAndFeel::SairaStencilMedium(){
            static const auto result = juce::Typeface::createSystemTypefaceFor(assets::SairaStencil_ExpandedMedium_ttf, assets::SairaStencil_ExpandedMedium_ttfSize);
            return juce::FontOptions{result};
    }

}  // namespace tremolo