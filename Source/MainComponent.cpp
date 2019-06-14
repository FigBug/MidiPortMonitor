/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    startTimer (500);

    addAndMakeVisible (text);
    text.setReadOnly (true);
    text.setMultiLine (true);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    text.setBounds (getLocalBounds().reduced (8));
}

void MainComponent::timerCallback()
{
    auto inputs = MidiInput::getAvailableDevices();
    auto outputs = MidiOutput::getAvailableDevices();

    StringArray inNames, inIDs, outNames, outIDs;

    for (auto input : inputs)
    {
        inNames.add (input.name);
        inIDs.add (input.identifier);
    }

    for (auto output : outputs)
    {
        outNames.add (output.name);
        outIDs.add (output.identifier);
    }

    inNames.sortNatural();
    inIDs.sortNatural();

    outNames.sortNatural();
    outIDs.sortNatural();

    if (inNames != lastInNames || inIDs != lastInIDs || outNames != lastOutNames || outIDs != lastOutIDs)
    {
        lastInNames  = inNames;
        lastInIDs    = inIDs;
        lastOutNames = outNames;
        lastOutIDs   = outIDs;

        dumpInfo();
    }
}

void MainComponent::dumpInfo()
{
    auto inputs = MidiInput::getAvailableDevices();
    auto outputs = MidiOutput::getAvailableDevices();

    String str;

    str += Time::getCurrentTime().toString (true, true) + "\n\n";
    str += "Inputs: \n";

    for (auto in : inputs)
        str += in.name + " (" + in.identifier + ") \n";
    str += "\n";

    str += "Outputs: \n";

    for (auto out : outputs)
        str += out.name + " (" + out.identifier + ") \n";
    str += "\n=======================================================\n\n";

    text.moveCaretToEnd();
    text.insertTextAtCaret (str);
}
