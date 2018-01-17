#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <random>
#include <chrono>
#include <memory>
#include <assert.h>

// large randomize number generator engine.
class RNG {
public:
  const static std::size_t maxRand;
  static RNG &getInstance()
  {
      static RNG instance;
      return instance;
    }
    std::size_t getInteger() noexcept{
         return (*dist)(*regen);
    }
private:
    RNG() noexcept
    {
        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();   // get time seed from system time.
        regen = std::make_shared<std::mt19937>(seed1);                  // init the randomize engine with the current time seed.
        dist = std::make_shared<std::uniform_int_distribution<std::size_t>> (0, maxRand);
    }
    std::shared_ptr<std::mt19937> regen;                                // randomize engine
    std::shared_ptr<std::uniform_int_distribution<std::size_t> > dist;  // distributive algorithm class.
};

const std::size_t RNG::maxRand = std::random_device::max();

// generate the random number from i ~ j. i <= j
int randInt(unsigned i, unsigned j)
{
    assert(i <= j);
    unsigned segment = j - i + 1;
    return i + RNG::getInstance().getInteger() % segment;
}

#endif