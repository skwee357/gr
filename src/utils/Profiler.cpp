/**
* @file Profiler.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of Profiler class.
*/

#include <iostream>
#include <iomanip>

#include <SDL/SDL.h>

#include "Profiler.hpp"

Profiler::Profiler()
{
  _saved = false;
}

Profiler::~Profiler()
{
}

void Profiler::start(const std::string& pfName)
{
  ProfileInfo_t pfInfo;
  if(_profileMap.find(pfName) == _profileMap.end()) {
    pfInfo.numIterations = 0;
    pfInfo.total = 0;
    pfInfo.current = 0;
    pfInfo.max = 0;
    pfInfo.endTime = 0;
    pfInfo.startTime = SDL_GetTicks();
  }

  _profileMap.insert(ProfileMapPair(pfName, pfInfo));
}

void Profiler::stop(const std::string& pfName)
{
  ProfileMapIter iter = _profileMap.find(pfName);
  if(iter != _profileMap.end()) {
    iter->second.endTime = SDL_GetTicks();
    iter->second.current = iter->second.endTime - iter->second.startTime;
    iter->second.startTime = iter->second.endTime;
    iter->second.total += iter->second.current;
    iter->second.numIterations ++;
    if(iter->second.current > iter->second.max)
      iter->second.max = iter->second.current;
    iter->second.current = 0;
  }
}

void Profiler::print()
{
  if(!_saved) {
    ProfileMapIter iter;
    static std::streamsize size = std::cout.width();
    std::streamsize name = 20, time = 16, niters = 10, maxtime = 16, total = 16;

    std::cout.flags(std::ios::left);

    std::cout << "| " << std::setw(name) << "Profile Name"
              << std::setw(size) << " | " << std::setw(time) << "Avg Time(ms)"
              << std::setw(size) << " | " << std::setw(niters) << "Iters"
              << std::setw(size) << " | " << std::setw(maxtime) << "Max Time(ms)"
              << std::setw(size) << " | " << std::setw(total) << "Total Time(ms)"
              << std::setw(size) << " | " << std::endl;

    std::cout << "| " << std::setw(name) << " "
              << std::setw(size) << " | " << std::setw(time) << " "
              << std::setw(size) << " | " << std::setw(niters) << " "
              << std::setw(size) << " | " << std::setw(maxtime) << " "
              << std::setw(size) << " | " << std::setw(total) << " "
              << std::setw(size) << " | " << std::endl;

    float avg;
    for(iter = _profileMap.begin(); iter != _profileMap.end(); ++iter) {
      avg = static_cast<float>(iter->second.total) / static_cast<float>(iter->second.numIterations);
      std::cout << "| " << std::setw(name) << iter->first
                << std::setw(size) << " | " << std::setw(time) << avg
                << std::setw(size) << " | " << std::setw(niters) << iter->second.numIterations
                << std::setw(size) << " | " << std::setw(maxtime) << iter->second.max
                << std::setw(size) << " | " << std::setw(total) << iter->second.total
                << std::setw(size) << " | " << std::endl;
    }
    _saved = true;
  }
}

bool Profiler::saved()
{
  return _saved;
}
