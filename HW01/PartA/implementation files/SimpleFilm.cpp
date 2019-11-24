#include "SimpleFilm.h"
#include <ostream>

Film::Film(const string fTitle, const string fDirector,
			const unsigned int fYear, const unsigned int fDuration){
	title = fTitle;
	director = fDirector;
	year = fYear;
	duration = fDuration;

	cout<< "constructor      " << title<< endl;
}

Film::Film( const Film &fToCopy){
	title = fToCopy.getTitle();
	director = fToCopy.getDirector();
	year = fToCopy.getYear();
	duration = fToCopy.getDuration();

	cout<< "copy constructor      " << title<< endl;
}

Film::~Film(){
	cout<< "distruct      " << title<< endl;
}

string Film::getTitle() const{
	return title;
}

string Film::getDirector() const{
	return director;
}

unsigned int Film::getYear() const{
	return year;
}

unsigned int Film::getDuration() const{
	return duration;
}

void Film::operator=(const Film &right){
	title = right.getTitle();
	director = right.getDirector();
	year = right.getYear();
	duration = right.getDuration();

	cout<< "assign      " << title<< endl;
}

ostream& operator<<(ostream& out, const Film& f){
	out << f.getTitle() << ", "
		<< f.getDirector() << ", "
		<< f.getYear() << ", "
		<< f.getDuration() << endl;

	return out;
}
