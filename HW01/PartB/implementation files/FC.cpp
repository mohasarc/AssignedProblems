#include <string>
#include <math.h>
#include "FC.h"

FC::FC(){
	noOfFilms = 0;
	size = 0;
	films = NULL;
}

FC::FC(const FC &fcToCopy){
	if (&fcToCopy != this){
		Film* tmp;
		// obtaining the information about the films array in the other object
		//size = noOfFilms = fcToCopy.getFilms(tmp);
		size = fcToCopy.size;
		noOfFilms = fcToCopy.noOfFilms;
		tmp = fcToCopy.films;

		if (size > 0){
			if (films != NULL)
				delete []films;
			films = new Film[size];

			// this will use the assignment function in the film class
			for (int i = 0; i < size; i++){
				films[i] = tmp[i];
			}
		}
	}
}

FC::~FC(){
	delete []films;
}

void FC::operator=(const FC &right){
	if (&right != this){
		Film* tmp;
		// obtaining the information about the films array in the other object
		//size = noOfFilms = right.getFilms(tmp);
		noOfFilms = right.noOfFilms;
		size = right.size;
		tmp = right.films;

		if (size > 0){
			if (films != NULL)
				delete []films;
			films = new Film[size];

			// this will use the assignment function in the film class
			for (int i = 0; i < size; i++){
				films[i] = tmp[i];
			}
		}
	}
}

bool FC::addFilm(const string fTitle, const string fDirector, const unsigned int fYear, 
	const unsigned int fDuration){

	if (isThere(fTitle, fDirector) < 0){

		if ( size > noOfFilms){
				Film tmpF(fTitle, fDirector, fYear, fDuration);
				films[noOfFilms] = tmpF;
				noOfFilms ++;

				return true;
		} else {
			unsigned int newSize = (int)ceil(noOfFilms * 1.5) + 1; // +1 to solve the problem of empty array
			Film* tmpFArray = new Film[newSize];

			for (int i = 0; i < size; i++){
				tmpFArray[i] = films[i];
			}

			size = newSize;
			if (films) // very Important!!
				delete []films;
			films = tmpFArray;

			// add the new film
			Film tmpF(fTitle, fDirector, fYear, fDuration);

			films[noOfFilms] = tmpF;
			noOfFilms ++;


			return true;
		}
	}

	return false;
}

bool FC::removeFilm(const string fTitle, const string fDirector){
	int indexToRemove = isThere(fTitle, fDirector);

	if(indexToRemove >= 0){
		unsigned int newSize = (int)ceil((noOfFilms - 1) * 1.5);

		Film* tmpFArray = new Film[newSize];

		int tmpCounter = 0;
		for (int i = 0; i < indexToRemove; i++){
			tmpFArray[tmpCounter++] = films[i];
		}

		for (int i = indexToRemove + 1; i < size; i++){
			tmpFArray[tmpCounter++] = films[i];
		}

		size = newSize;
		noOfFilms --;

		// clean memory
		if (films)
			delete []films;
		films = tmpFArray;

		return true;
	}

	return false;
}

unsigned int FC::getFilms( Film *&allFilms ) const{
	Film* tmp = new Film[noOfFilms];

	for (int i = 0; i < noOfFilms; i++){
		tmp[i] = films[i];
	}

	allFilms = tmp;
	return noOfFilms;
}

bool FC::addActor(const string fTitle, const string fDirector,
	const string aName, const string aBirthPlace,
	const unsigned int aBirthYear){

	unsigned int indexOfFilm = isThere(fTitle, fDirector);
	if ( indexOfFilm >= 0 ){
		bool stat = films[indexOfFilm].addActor(aName, aBirthPlace, aBirthYear);
		return stat;
	}

	return false;
}

bool FC::removeActors(const string fTitle, const string fDirector){
	unsigned int indexOfFilm = isThere(fTitle, fDirector);

	if (indexOfFilm >= 0){
		bool stat = films[indexOfFilm].removeActors();
	}

	return false;
}

unsigned int FC::calculateAverageDuration() const{
	if (noOfFilms > 0){
		int totalDuration = 0;

		for (int i = 0; i < noOfFilms; i++){
			totalDuration += films[i].getFilmDuration();
		}

		return (int)round(totalDuration / noOfFilms);
	}
	
	return 0;
}

// return the index if found// return -1 if not found
int FC::isThere(const string fTitle, const string fDirector){
	if (size > 0){
		for (int i = 0; i < size; i++){
			if ((films[i].getFilmTitle().compare(fTitle)) == 0 
				&& (films[i].getFilmDirector().compare(fDirector)) == 0)
				return i;
		}
	}

	return -1;
}