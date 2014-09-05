#ifndef GAMECACHE_H
#define GAMECACHE_H

#include <QString>
#include <QHash>

class GameCache
{
	public:
		static void insertInCache(const QString & key, std::pair<int, int> choice);
		static bool getChoice(const QString & key, std::pair<int, int> & choice);

	private:
		static QHash<QString, std::pair<int, int> > _choicesCache;
};
#endif //GAMECACHE_H