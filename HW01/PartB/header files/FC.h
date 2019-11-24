#ifndef __FC_H
#define __FC_H
#include "Film.h"
class FC{
public:
	FC();
	FC(const FC &fcToCopy);
	~FC();
	void operator=(const FC &right);
	bool addFilm(const string fTitle, const string fDirector,
	const unsigned int fYear,
	const unsigned int fDuration);
	bool removeFilm(const string fTitle, const string fDirector);
	unsigned int getFilms(Film *&allFilms) const;
	bool addActor(const string fTitle, const string fDirector,
	const string aName, const string aBirthPlace,
	const unsigned int aBirthYear);
	bool removeActors(const string fTitle, const string fDirector);
	unsigned int calculateAverageDuration() const;
private:
	Film *films;
	unsigned int noOfFilms;
	unsigned int size;
	int isThere(const string fTitle, const string fDirector); // added by me
};
#endif