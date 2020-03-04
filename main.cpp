/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some. 
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}


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

    while(targetFrequency <= frequency || frequency <= targetFrequency)
    {
        std::cout << "Transitioning... frequency is: " << frequency << std::endl;

        if(frequency < targetFrequency && targetFrequency - frequency > incrementAmount)
        {
            frequency += incrementAmount;
        }
        else if(frequency > targetFrequency && targetFrequency - frequency < incrementAmount)
        {
            frequency -= incrementAmount;
        }
        else
        {
            double remainder = targetFrequency - frequency;
            frequency += remainder; // making sure we hit that final increment without exceeding target
            
            std::cout << "Frequency transition completed. Current frequency is: " << frequency << ".\n" << std::endl;
            return frequency;
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
        for(float i = volumeLevel; i >= 0; i -= incrementAmount)
        {
            volumeLevel -= incrementAmount;
            std::cout << "Current oscillator volume is: " << volumeLevel << "." << std::endl;
            if(volumeLevel <= 0)
            {
                std::cout << "Finished fading out!\n" << std::endl;
                return volumeLevel;
            }
        }
        
        return volumeLevel;
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

    double setNextDryWet(double nextDryWetValue)
    {
        double epsilon = 0.0001;

        std::cout << "\nAdjusting reverb dryWet!" << std::endl;
        double incrementPolarity;

        if(dryWet < nextDryWetValue) incrementPolarity = 0.1;
        else incrementPolarity = -0.1;

        if(nextDryWetValue > 1) 
        {
            std::cout << "dryWet cannot be higher than 1.0!" << std::endl;
            return dryWet;
        }

        for(double instancedDryWet = dryWet; std::abs(instancedDryWet - nextDryWetValue) > epsilon; instancedDryWet += incrementPolarity)
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
    if(newVerbSettings.decayTime == decayTime)
    {
        decayTime = 0;
        std::cout << "Setting reverb decay time to: " << decayTime << ".\n" << std::endl;
    }
    else
    {
        decayTime = newVerbSettings.decayTime;
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
        thisOscillator.fadeOutVolume(0.1f);
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
        rackFilter.transitionToNextFrequency(5000.0, 100);

        rackReverb.setNextDryWet(0.5);

        std::cout << "Destroying effects rack!\n" << std::endl;
    }
};

int main()
{
	Example::main();
    Synthesizer mySynth;
    EffectsRack myRack;

    std::cout << "good to go!" << std::endl;
}
