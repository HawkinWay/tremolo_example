namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) :
  AudioProcessorEditor(&p),
  waveformAttachment{p.getParameterRefs().waveform, waveformComboBox},
  rateAttachment{p.getParameterRefs().rate, rateSlider},
  depthAttachment{p.getParameterRefs().modulationDepth, depthSlider},
  bypassAttachment{p.getParameterRefs().bypassed, bypassButton}{
  background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

  logo.setImage(juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
  /* logo2.setImage(
           juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
     logo3.setImage(
            juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));*/

  addAndMakeVisible(background);

  addAndMakeVisible(logo);
  /* addAndMakeVisible(logo2);
     addAndMakeVisible(logo3);*/

  waveformLabel.setFont(lookAndFeel.getSideLabelsFont());
  addAndMakeVisible(waveformLabel);

  waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformAttachment.sendInitialUpdate();
  addAndMakeVisible(waveformComboBox);

  rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0 ,0);
  rateSlider.setPopupDisplayEnabled(true, true, this);
//rateSlider.setRange(1.0,30.0,0.5);
//rateSlider.onValueChange = [this](){DBG("rateSlider value: " << rateSlider.getValue());};
  rateSlider.setTextValueSuffix("Hz");
  addAndMakeVisible(rateSlider);

  rateLabel.setFont(lookAndFeel.getSideLabelsFont());
  rateLabel.setInterceptsMouseClicks(false,false);
  addAndMakeVisible(rateLabel);

  bypassLabel.setFont(lookAndFeel.getSideLabelsFont());
  addAndMakeVisible(bypassLabel);

  bypassButton.onClick = [this]() {
    bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypassed" : "OFF");
  };
  bypassButton.onClick();
  addAndMakeVisible(bypassButton);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false,0,0);
    depthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(depthSlider);

    depthLabel.setFont(lookAndFeel.getSideLabelsFont());
    depthLabel.setInterceptsMouseClicks(false,false);
    addAndMakeVisible(depthLabel);

  widthLabel.setFont(lookAndFeel.getSideLabelsFont());
  addAndMakeVisible(widthLabel);

  lfoCurveWidthSlider.setRange(0,10,1);
  lfoCurveWidthSlider.onValueChange = [this]() {
      lfoVisualizer.setStrokeWidth(static_cast<float>(lfoCurveWidthSlider.getValue()));
      lfoVisualizer.repaint();
  };
  addAndMakeVisible(lfoCurveWidthSlider);

  addAndMakeVisible(lfoVisualizer);

  setLookAndFeel(&lookAndFeel);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 300);
}

PluginEditor::~PluginEditor() {
  setLookAndFeel(nullptr);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();

  // background.setBounds(bounds);
  auto backgroundBounds = bounds;
  backgroundBounds.removeFromTop(0);
  backgroundBounds.removeFromBottom(30);
  background.setBounds(backgroundBounds);


  logo.setBounds({16, 16, 105, 24});
  /* logo2.setBounds({218,16,105,24});
     logo3.setBounds({419,16,105,24}); */

  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(180);
  rateSliderBounds.removeFromRight(280);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(180);
  rateSlider.setBounds(rateSliderBounds);

  rateLabel.setJustificationType(juce::Justification::centred);
  rateLabel.setBounds(rateSliderBounds);

  auto bypassButtonBounds = bounds;
  bypassButtonBounds.removeFromLeft(392);
  bypassButtonBounds.removeFromRight(16);
  bypassButtonBounds.removeFromTop(81);
  bypassButtonBounds.removeFromBottom(191);
  bypassButton.setBounds(bypassButtonBounds);

  const auto bypassLabelBounds = bypassButtonBounds.translated(
                                             0,-bypassButtonBounds.getHeight());
  bypassLabel.setBounds(bypassLabelBounds);

    auto depthSliderBounds = bounds;
    depthSliderBounds.removeFromLeft(280);
    depthSliderBounds.removeFromRight(180);
    depthSliderBounds.removeFromTop(40);
    depthSliderBounds.removeFromBottom(180);
    depthSlider.setBounds(depthSliderBounds);

    depthLabel.setJustificationType(juce::Justification::centred);
    depthLabel.setBounds(depthSliderBounds);


  auto waveformComboBoxBounds = bounds;
  waveformComboBoxBounds.removeFromTop(81);
  waveformComboBoxBounds.removeFromBottom(191);
  waveformComboBoxBounds.removeFromLeft(16);
  waveformComboBoxBounds.removeFromRight(392);
  waveformComboBox.setBounds(waveformComboBoxBounds);

  const auto waveformLabelBounds = waveformComboBoxBounds.translated(
                                              0,-waveformComboBoxBounds.getHeight());
  waveformLabel.setBounds(waveformLabelBounds);

  auto lfoWidthBounds = juce::Rectangle<int>{0, 270, 270, 30};
  lfoCurveWidthSlider.setBounds(lfoWidthBounds);
  const auto widthLabelBounds = lfoWidthBounds.translated(
                                              lfoCurveWidthSlider.getWidth(),0);
  widthLabel.setBounds(widthLabelBounds);

  lfoVisualizer.setBounds({18,149,504,92});
}
}  // namespace tremolo
