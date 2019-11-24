#ifndef __FILM_H
#define __FILM_H
#include "Actor.h"
class Film{
public:
	Film(const string fTitle = "", const string fDirector = "",
	const unsigned int fYear = 0,
	const unsigned int fDuration = 0);
	Film(const Film &fToCopy);
	~Film();
	void operator=(const Film &right);
	string getFilmTitle() const;
	string getFilmDirector() const;
	unsigned int getFilmYear() const;
	unsigned int getFilmDuration() const;
	unsigned int calculateAverageActorAge() const;
	unsigned int getActors(Actor *&actorsList) const; // added by me
	bool addActor(const string aName, const string aBirthPlace,
	const unsigned int aBirthYear); // added by me
	bool removeActors(); // added by me
	int doesActorExist(const string aName) const; // added by me
	friend ostream& operator<<(ostream& out, const Film& f);
private:
	string title;
	string director;
	unsigned int year;
	unsigned int duration;
	Actor *actors;
	unsigned int noOfActors;
	unsigned int size;
	//static unsigned int CURRENT_YEAR; // added by me
};
#endif