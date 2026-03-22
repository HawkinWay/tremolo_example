namespace tremolo {
namespace {
    struct SerializableParameters {
        float rate;
        float gain;
        float modulationDepth;
        bool bypassed;
        juce::String waveform;

        static constexpr auto marshallingVersion = 1;   //or std::nullopt

        template<typename Archive, typename T>
        static void serialise(Archive& archive, T& t) {
            using namespace juce;

            if (archive.getVersion() != 1) {
                return;
            }

            std::string pluginName = TREMOLO_PLUGIN_NAME;
            archive(named("pluginName", pluginName));
            if (pluginName != TREMOLO_PLUGIN_NAME) {
                return;
            }
            archive(named("modulationRateHz", t.rate),
                named("gain", t.gain),
                named("modulationDepth", t.modulationDepth),
                named("bypassed", t.bypassed),
                named("modulationWaveform", t.waveform));
        }
    };

    SerializableParameters from(const tremolo::Parameters& parameters) {
        return {
        .rate = parameters.rate.get(),
        .gain = parameters.gain.get(),
        .modulationDepth = parameters.modulationDepth.get(),
        .bypassed = parameters.bypassed.get(),
        .waveform = parameters.waveform.getCurrentChoiceName(),
        };
    }
}
void JsonSerializer::serialize(const Parameters& parameters,
                               juce::OutputStream& output) {
  // juce::ignoreUnused(parameters, output);

  // serialize parameters to the output stream as JSON
    const auto parametersToSerialize = from(parameters);

    const auto json = juce::ToVar::convert(parametersToSerialize);

    if (!json.has_value()) {
        return;
    }

    juce::JSON::writeToStream(output, *json,               // json.value() is okay
        juce::JSON::FormatOptions{}.withSpacing(juce::JSON::Spacing::multiLine).withMaxDecimalPlaces(2));
    /*
       juce::JSON::FormatOptions options;
       options.withSpacing(juce::JSON::Spacing::multiLine);
       options.withMaxDecimalPlaces(2);
    */
}

juce::Result JsonSerializer::deserialize(juce::InputStream& input,
                                         Parameters& parameters) {
  juce::ignoreUnused(input, parameters);

  // deserialize parameters from the JSON input stream
    juce::var parsedResult;

    const auto result = juce::JSON::parse(input.readEntireStreamAsString(), parsedResult);
    if (result.failed()) {
        return result;
    }

    const auto parseParameters = juce::FromVar::convert<SerializableParameters>(parsedResult);
    if (!parseParameters.has_value()) {
        return juce::Result::fail("failed to parse parameters");
    }

    const auto modulationWaveformIndex = parameters.waveform.choices.indexOf(parseParameters->waveform);
    // 4.06. Assignment 2
    if (modulationWaveformIndex == -1) {
        return juce::Result::fail("modulation waveform doesn't exist");
    }

    parameters.waveform = modulationWaveformIndex;
    parameters.rate = parseParameters->rate;
    parameters.gain = parseParameters->gain;
    parameters.modulationDepth = parseParameters->modulationDepth;
    parameters.bypassed = parseParameters->bypassed;

  return juce::Result::ok();
}
}  // namespace tremolo
