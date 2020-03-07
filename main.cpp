/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main to use your wrapper classes, which have your UDTs as pointer member variables.
 
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example
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

    FilterKnob myKnob;

    void updateKnobPosition(double nextKnobPosition);
    double transitionToNextFrequency(double, double);
};

double Filter::transitionToNextFrequency(double targetFrequency, double incrementAmount)
{
    std::cout << "\nThe starting frequency before transitioning is: " << frequency << "." << std::endl;

    while(targetFrequency <= this->frequency || this->frequency <= targetFrequency)
    {
        std::cout << "Transitioning... frequency is: " << this->frequency << std::endl;

        if(this->frequency < targetFrequency && targetFrequency - this->frequency > incrementAmount)
        {
            this->frequency += incrementAmount;
        }
        else if(this->frequency > targetFrequency && targetFrequency - this->frequency < incrementAmount)
        {
            this->frequency -= incrementAmount;
        }
        else
        {
            double remainder = targetFrequency - this->frequency;
            this->frequency += remainder; // making sure we hit that final increment without exceeding target
            
            std::cout << "Frequency transition completed. Current frequency is: " << frequency << ".\n" << std::endl;
            return this->frequency;
        }  
    }
    
    return frequency;
}

void Filter::FilterKnob::spawnKnob(int numberOfKnobs, float knobLocation)
{
    FilterKnob newKnob;

    if(numberOfKnobs < 10) newKnob.spawnKnob(numberOfKnobs, knobLocation);
    std::cout << "You are trying to spawn too many knobs at once!\n\n";
}

void Filter::updateKnobPosition(double nextKnobPosition)
{
    std::cout << "The knob to update is: " << myKnob.knobID << ". The next knob position is: " << nextKnobPosition << ".\n" << std::endl;
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

    float fadeOutVolume(float incrementAmount)
    {
        for(float i = this->volumeLevel; i >= 0; i -= incrementAmount)
        {
            this->volumeLevel -= incrementAmount;
            std::cout << "Current oscillator volume is: " << this->volumeLevel << "." << std::endl;
            if(volumeLevel <= 0)
            {
                std::cout << "Finished fading out!\n" << std::endl;
                return this->volumeLevel;
            }
        }
        
        return this->volumeLevel;
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

    double setNextDryWet(double nextDryWetValue)
    {
        double epsilon = 0.0001;

        std::cout << "\nAdjusting reverb dryWet!" << std::endl;
        double incrementPolarity;

        if(this->dryWet < nextDryWetValue) incrementPolarity = 0.1;
        else incrementPolarity = -0.1;

        if(nextDryWetValue > 1) 
        {
            std::cout << "dryWet cannot be higher than 1.0!" << std::endl;
            return this->dryWet;
        }

        for(double instancedDryWet = this->dryWet; std::abs(instancedDryWet - nextDryWetValue) > epsilon; instancedDryWet += incrementPolarity)
        {
            std::cout << "Current dryWet is: " << instancedDryWet << "." << std::endl;

            if(instancedDryWet <= nextDryWetValue)
            {
                std::cout << "Finished! New dryWet is: " << instancedDryWet << ".\n" << std::endl;
                return this->dryWet;
            }
        }
        return dryWet;
    }
};


/*
 new UDT 4:
 */
struct Synthesizer
{
    WavetableOscillator thisOscillator;

    ~Synthesizer()
    {
        thisOscillator.fadeOutVolume(0.1f);
        std::cout << "Fading volume and destroying synthesizer" << std::endl;
    }

    void printVolumeLevel()
    {
        std::cout << "The synthesizer volume level is: "<<  this->thisOscillator.volumeLevel << std::endl;
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
        rackFilter.transitionToNextFrequency(5000.0, 100);

        rackReverb.setNextDryWet(0.5);

        std::cout << "Destroying effects rack!\n" << std::endl;
    }

    void printFilterFrequencyLevel()
    {
        std::cout << "The effects rack filter frequency is: " << this->rackFilter.frequency << std::endl;
    }

    void printReverbDecayTime()
    {
    std::cout << "The effects rack decay time is: " << this->rackReverb.decayTime << std::endl;
    }
};

int main()
{
	Example::main();
    Synthesizer mySynth;
    EffectsRack myRack;

    std::cout << "The synthesizer volume level is: " <<  mySynth.thisOscillator.volumeLevel << std::endl;
    mySynth.printVolumeLevel();
    
    std::cout << "The effects rack filter frequency is: " << myRack.rackFilter.frequency << std::endl;
    myRack.printFilterFrequencyLevel();

    std::cout << "The effects rack decay time is: " << myRack.rackReverb.decayTime << std::endl;
    myRack.printReverbDecayTime();

    std::cout << "good to go!" << std::endl;
}


//        int maxNumberOfWaveforms;
///        bool interpolationOn;
//        int currentWavetable;
