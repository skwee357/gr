/**
* @file Manager.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of Manager class.
*/

#ifndef MANAGER_HPP_INCLUDED
#define MANAGER_HPP_INCLUDED

template <class T>
class Manager{
  public:
    /** Ctor. */
    Manager()
    {
      if(_numInstances == 0)
        _instance = new T();
      _numInstances++;
    }

    /** Dtor. */
    ~Manager()
    {
      _numInstances--;
      if(_numInstances == 0)
        delete _instance;
    }

    /** Get Instance. */
    static T& getInstance()
    {
      return *_instance;
    }

  private:
    static T* _instance; /**< Instance. */
    static int _numInstances; /**< Number of instances. */
};

template <class T> T* Manager<T>::_instance = 0;
template <class T> int Manager<T>::_numInstances = 0;
#endif // PROFILER_HPP_INCLUDED
