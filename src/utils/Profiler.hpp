/**
* @file Profiler.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of Profiler class.
*/

#ifndef PROFILER_HPP_INCLUDED
#define PROFILER_HPP_INCLUDED

#include <string>
#include <map>

#include "Manager.hpp"

typedef struct{
  int startTime;
  int endTime;
  int current;
  int numIterations;
  int total;
  int max;
}ProfileInfo_t;

typedef std::map<std::string, ProfileInfo_t> ProfileMap;
typedef std::pair<std::string, ProfileInfo_t> ProfileMapPair;
typedef std::map<std::string, ProfileInfo_t>::iterator ProfileMapIter;

class Profiler{
  public:
    Profiler();
    ~Profiler();

    void start(const std::string& pfName);
    void stop(const std::string& pfName);

    void print();

    bool saved();

  private:
    ProfileMap _profileMap;
    bool _saved;
};

typedef Manager<Profiler> ProfileManager;

#endif // PROFILER_HPP_INCLUDED
