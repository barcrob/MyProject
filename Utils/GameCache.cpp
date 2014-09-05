#include "GameCache.h"

#include <iostream>

QHash<QString, std::pair<int, int> > GameCache::_choicesCache;

void GameCache::insertInCache(const QString & key, std::pair< int, int > choice)
{
	_choicesCache[key] = choice;

	std::cout << "cache size after insert = " << _choicesCache.size() << std::endl;
}

bool GameCache::getChoice(const QString& key, std::pair< int, int > & choice)
{
	if(_choicesCache.empty())
		return false;

	if(!_choicesCache.contains(key))
		return false;

	choice = _choicesCache[key];
	return true;
}
