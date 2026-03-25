namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  /* logo2.setImage(
           juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
     logo3.setImage(
            juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));*/


  addAndMakeVisible(background);
  addAndMakeVisible(logo);
  /* addAndMakeVisible(logo2);
     addAndMakeVisible(logo3);*/
  addAndMakeVisible(lfoVisualizer);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 270);
}

void PluginEditor::resized() {
  const auto bounds = getLocalBounds();

  background.setBounds(bounds);

  logo.setBounds({16, 16, 105, 24});
  /* logo2.setBounds({218,16,105,24});
     logo3.setBounds({419,16,105,24}); */

  lfoVisualizer.setBounds(18,149,504,92);
}
}  // namespace tremolo
