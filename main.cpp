/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

 Destructors

 If you didn't do Project3, write 3 UDTs below (where it asks for Copied UDTs) that have: 
        member functions,
        member variables, 
        constructors that initialize the members. 
        for() or while() loops that modify member variables
        
 Define your implementations of all functions OUTSIDE of the class. 
 Then do instruction 2)
 
 If you DID do Project 3, do instruction 1)
 
 1) Copy a few of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

	If you already did Chapter2 part 10 on Coliru and don't have a Project3, just grab some UDTs from your Coliru Ch2P10 submission. 
 
 3) add 2 new UDTs that use only the types you copied above.
 4) Add destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 5) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 6) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */
#include <iostream>
/*
 copied UDT 1:
 */
struct Filter
{
    double frequency;
    int filterType;
    float dryWet;

    Filter() : frequency(4000.0), filterType(2), dryWet (1.0f) 
    {
        std::cout << "Spawning Filter object!\n" << std::endl;
    }
    ~Filter()
    {
        std::cout << "Destroying Filter object!\n" << std::endl;
    }

    struct FilterKnob
    {
        float knobPosition;
        bool knobOverride;
        int knobID;

        FilterKnob()
        {
            knobPosition = 1.0f;
            knobOverride = false;
            knobID = 1;
        }

        void spawnKnob(int numberOfKnobs, float knobLocation);
    };

    void updateKnobPosition(FilterKnob knobOne, double nextKnobPosition);
    double transitionToNextFrequency(Filter, double, double);
};

double Filter::transitionToNextFrequency(Filter thisFilter, double targetFrequency, double incrementAmount)
{
    std::cout << "\nThe starting frequency before transitioning is: " << thisFilter.frequency << "." << std::endl;

    while(targetFrequency <= thisFilter.frequency || thisFilter.frequency <= targetFrequency)
    {
        std::cout << "Transitioning... frequency is: " << thisFilter.frequency << std::endl;

        if(thisFilter.frequency < targetFrequency && targetFrequency - thisFilter.frequency > incrementAmount)
        {
            thisFilter.frequency += incrementAmount;
        }
        else if(thisFilter.frequency > targetFrequency && targetFrequency - thisFilter.frequency < incrementAmount)
        {
            thisFilter.frequency -= incrementAmount;
        }
        else
        {
            double remainder = targetFrequency - thisFilter.frequency;
            thisFilter.frequency += remainder; // making sure we hit that final increment without exceeding target
            
            std::cout << "Frequency transition completed. Current frequency is: " << thisFilter.frequency << ".\n" << std::endl;
            return thisFilter.frequency;
        }  
    }
    
    return thisFilter.frequency;
}

void Filter::FilterKnob::spawnKnob(int numberOfKnobs, float knobLocation)
{
    FilterKnob newKnob;

    if(numberOfKnobs < 10) newKnob.spawnKnob(numberOfKnobs, knobLocation);
    std::cout << "You are trying to spawn too many knobs at once!\n\n";
}

void Filter::updateKnobPosition(FilterKnob knobToUpdate, double nextKnobPosition)
{
    int knobID = knobToUpdate.knobID;
    std::cout << "The knob to update is: " << knobID << ". The next knob position is: " << nextKnobPosition << ".\n" << std::endl;
    std::cout << "Your filter frequency is:" << frequency << std::endl;
}
/*
 copied UDT 2:
 */
struct WavetableOscillator
{
    double frequency;
    int waveShape;
    float volumeLevel;

    WavetableOscillator() : frequency(4000.0), waveShape(2), volumeLevel(1.0f) 
    {
        std::cout << "Spawning WavetableOscillator object!\n" << std::endl;
    }
    ~WavetableOscillator()
    {
        std::cout << "Destroying WavetableOscillator object!\n" << std::endl;
    }

    struct Wavetable
    {   
        int maxNumberOfWaveforms;
        bool interpolationOn;
        int currentWavetable;

        Wavetable()
        {
            maxNumberOfWaveforms = 100;
            interpolationOn = true;
            currentWavetable = 0;  
        }
                    
        int cycleToTargetWavetable(WavetableOscillator::Wavetable table, int targetTable);   
        void loadWavetable(int wavetableToLoad, float loadTimeOffset);
    };

    int getNextFrequencyInSequence(float nextFrequency)
    {
        std::cout << "The next frequency is: " << nextFrequency << ".\n" << std::endl;

        std::cout << "Waveshape is: " << waveShape << ". Volume Level is: " << volumeLevel << ".\n" << std::endl;
        return{};
    }

    float fadeOutVolume(WavetableOscillator osc, float incrementAmount)
    {
        for(float i = osc.volumeLevel; i >= 0; i -= incrementAmount)
        {
            osc.volumeLevel -= incrementAmount;
            std::cout << "Current oscillator volume is: " << osc.volumeLevel << "." << std::endl;
            if(osc.volumeLevel <= 0)
            {
                std::cout << "Finished fading out!\n" << std::endl;
                return osc.volumeLevel;
            }
        }
        
        return osc.volumeLevel;
    }
};
/*
 copied UDT 3:
 */
struct Reverb
{
    int decayTime;
    float roomSize;
    double inputVolume;
    double outputVolume;
    double dryWet;

    Reverb() : decayTime(1), roomSize(3.5f), inputVolume(1.0), outputVolume(1.0), dryWet(1.0) 
    {
        std::cout << "Spawning Reverb object!\n" << std::endl;
    }

    ~Reverb()
    {
        std::cout << "Destroying Reverb object!\n" << std::endl;
    }

    int setNextReverbSettings(Reverb newVerbSettings);

    double setNextDryWet(Reverb targetVerb, double nextDryWetValue)
    {
        double epsilon = 0.0001;

        std::cout << "\nAdjusting reverb dryWet!" << std::endl;
        double incrementPolarity;

        if(targetVerb.dryWet < nextDryWetValue) incrementPolarity = 0.1;
        else incrementPolarity = -0.1;

        if(nextDryWetValue > 1) 
        {
            std::cout << "dryWet cannot be higher than 1.0!" << std::endl;
            return dryWet;
        }

        for(double instancedDryWet = targetVerb.dryWet; std::abs(instancedDryWet - nextDryWetValue) > epsilon; instancedDryWet += incrementPolarity)
        {
            std::cout << "Current dryWet is: " << instancedDryWet << "." << std::endl;

            if(instancedDryWet <= nextDryWetValue)
            {
                std::cout << "Finished! New dryWet is: " << instancedDryWet << ".\n" << std::endl;
                return dryWet;
            }
        }
        return dryWet;
    }
};

int Reverb::setNextReverbSettings(Reverb newVerbSettings)
{
    Reverb oldVerbSettings;
    if(newVerbSettings.decayTime == oldVerbSettings.decayTime)
    {
        decayTime = 0;
        std::cout << "Setting reverb decay time to: " << decayTime << ".\n" << std::endl;
    }
    else
    {
        newVerbSettings.decayTime = oldVerbSettings.decayTime;
        std::cout << "Setting reverb decay time to old verb settings: (" << newVerbSettings.decayTime << ").\n\n" << std::endl;
    }
    return {};
}

/*
 new UDT 4:
 */
struct Synthesizer
{
    WavetableOscillator thisOscillator;

    ~Synthesizer()
    {
        thisOscillator.fadeOutVolume(thisOscillator, 0.1f);
        std::cout << "Fading volume and destroying synthesizer" << std::endl;
    }
};
/*
 new UDT 5:
 */
struct EffectsRack
{
    Filter rackFilter;
    Reverb rackReverb;

    ~EffectsRack()
    {
        rackFilter.transitionToNextFrequency(rackFilter, 5000.0, 100);

        rackReverb.setNextDryWet(rackReverb, 0.5);

        std::cout << "Destroying effects rack!\n" << std::endl;
    }
};

int main()
{
    Synthesizer mySynth;
    EffectsRack myRack;

    std::cout << "good to go!" << std::endl;
}
