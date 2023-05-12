#include "Singleton.h"

// Initialization of static const
template<typename T>
T Singleton<T>::Instance;


#include "Game.h"

template
class Singleton<Game>;

template
Game Singleton<Game>::Instance;


#include "ResourceManager.h"

template
class Singleton<ResourceManager>;

template
Game Singleton<Game>::Instance;

