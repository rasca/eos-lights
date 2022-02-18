#ifndef COMPOSERS_H_INCLUDED
#define COMPOSERS_H_INCLUDED

#include <config.h>
#include <utils.h>

template <typename T, typename... Args>
class ApplyToAll : public BaseEffect {

    public:

    std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> &segments;

    std::vector<T> effects;

    ApplyToAll(std::array<std::array<CRGB, NUM_LEDS>, NUM_SEGMENTS> &segments, Args... args)
        : segments(segments)
        {
            for (auto& s : segments) {
                effects.emplace_back(s, args...);
            }
        }
    
    void setup() {
        for (auto& e : effects) {
            e.setup();
        }
    }

    void tick() {
        for (auto& e : effects) {
            e.tick();
        }
    }

};

#endif