#include <math.h>
#include <string>
#include "Film.h"

Film::Film(const string fTitle, const string fDirector,
			const unsigned int fYear, const unsigned int fDuration){
	title = fTitle;
	director = fDirector;
	year = fYear;
	duration = fDuration;
	actors = NULL;
	noOfActors = 0;
	size = 0;
	//CURRENT_YEAR = 2019;
}

Film::Film( const Film &fToCopy){
	if (&fToCopy != this){
		title = fToCopy.getFilmTitle();
		director = fToCopy.getFilmDirector();
		year = fToCopy.getFilmYear();
		duration = fToCopy.getFilmDuration();
		Actor* tmp;

		//noOfActors = fToCopy.getActors(tmp); // there can be a memory problem
		noOfActors = fToCopy.noOfActors;
		tmp = fToCopy.actors;

		if (actors != NULL)
			delete []actors;
		actors = new Actor[noOfActors];

		for (int i = 0; i < noOfActors; i++){
			actors[i] = tmp[i];
		}
	}
}

Film::~Film(){
	delete []actors;
}

string Film::getFilmTitle() const{
	return title;
}

string Film::getFilmDirector() const{
	return director;
}

unsigned int Film::getFilmYear() const{
	return year;
}

unsigned int Film::getFilmDuration() const{
	return duration;
}

unsigned int Film::calculateAverageActorAge() const{

	if (noOfActors > 0){
		int totalYears = 0;

		for (int i = 0; i < noOfActors; i++){
			totalYears += actors[i].getBirthYear();
		}
		return (int)round(2019 - (totalYears / noOfActors));
	}
	
	return 0;
}

void Film::operator=(const Film &right){
	if (&right != this){
		title = right.getFilmTitle();
		director = right.getFilmDirector();
		year = right.getFilmYear();
		duration = right.getFilmDuration();
		Actor* tmp;
		//noOfActors = right.getActors(tmp); // there can be a memory problem
		noOfActors = right.noOfActors;
		tmp = right.actors;

		if (actors != NULL)
			delete actors;
		actors = new Actor[noOfActors];

		for (int i = 0; i < noOfActors; i++){
			actors[i] = tmp[i];
		}
	}
}

unsigned int Film::getActors(Actor *&actorsList) const{
	if (actors) // actors can be null
		actorsList = actors;
	return noOfActors;
}

bool Film::addActor(const string aName, const string aBirthPlace,
	const unsigned int aBirthYear){
	if (doesActorExist(aName) < 0){
		Actor* tmp = new Actor[(noOfActors + 1)];

		for (int i = 0; i < noOfActors; i++){
			tmp[i] = actors[i];
		}

		Actor tempActor(aName, aBirthPlace, aBirthYear);
		tmp[noOfActors] = tempActor;

		if (actors)
			delete []actors;
		actors = tmp;
		noOfActors++;

		return true;
	}

	return false;
}

bool Film::removeActors(){
	if (actors){
		delete []actors;
		actors = NULL;
		noOfActors = 0;
	}

	return true;
}

int Film::doesActorExist(const string aName) const{
	if (noOfActors > 0){
		for (int i = 0; i < noOfActors; i++){
			if ((actors[i].getName().compare(aName)) == 0)
				return i;
		}
	}

	return -1;
}

ostream& operator<<(ostream& out, const Film& f){
	out << f.getFilmTitle() << ", "
		<< f.getFilmDirector() << ", "
		<< f.getFilmYear() << ", "
		<< f.getFilmDuration();

		Actor* tmp;
		int noOfActors = f.getActors(tmp);
		for (int i = 0; i < noOfActors; i++){
			out<<"\n\t" << tmp[i];
		}

	cout<<"\n";

	return out;
}