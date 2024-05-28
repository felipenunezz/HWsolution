# include <iostream>
# include <string>

enum breed {
	Affenpinscher,
	Airedale_Terrier,
	Akita,
	Alaskan_Malamute,
	American_Bulldog,
	Australian_Shepherd,
	Basenji,
	Beagle,
	Bernese_Mountain_Dog,
	Boxer,
	Bullmastiff,
	Cavalier_King_Charles_Spaniel,
	Chihuahua,
	Cocker_Spaniel,
	German_Shepherd
};

class Name 
{
public:	
	std::string first;
	std::string patro;
	std::string last;

	Name() { first = ""; patro = ""; last = ""; }
	
	Name(std::string _last, std::string _first, std::string _patro) :
		first(_first), patro(_patro), last(_last) 
	{}
};

class Date
{
private:
	int day;
	int month;
	unsigned int year;
public:

	Date() { day = 1;  month = 1; year = 0; }
	Date(int setday) { day = setday;  month = 1; year = 0; }
	Date(int setmonth) { day = 1;  month = setmonth; year = 0; }
	Date(unsigned int setyear) { day = 1;  month = 1; year = setyear; }
	Date(int sday, int smonth, unsigned int syear) : day(sday), month(smonth), year(syear)
	{
		if (month == 2) { if (year % 4 == 0) { if (day > 29) { day == 29; } } }
		if (month == 2) { if (year % 4 != 0) { if (day > 28) { day == 28; } } }
		if (days31(month)) { if (day > 30) { day == 30; } }
		if (days31(month)) { if (day > 31) { day == 31; } }

		if (month > 12) { month = 12; }
		if (month < 1) { month = 1; }
		if (day < 1) { day = 1; }
	}

	bool days31(int smonth)
	{
		return smonth == 1 || smonth == 3 || smonth == 5 || smonth == 7 || smonth == 8 || smonth == 10 || smonth == 12;
	}
	bool days30(int smonth)
	{
		return smonth == 4 || smonth == 6 || smonth == 9 || smonth == 11;
	}

	int days() { return day; }
	int months() { return month; }
	int years() { return year; }

};

class Person : public Name, public Date
{
	Name name;
	Date birthday;
	unsigned int phone;

	Person() { ("Jhon", "Dou", "");  }
	Person(std::string _last, std::string _first, std::string _patro, int _day, int _month, int _year, unsigned int _phone) :
		name(_last, _first, _patro), birthday(_day, _month, _year), phone(_phone)
	{}
};

class Pet : public Name, public Date

{
private: 
	Name name;
	Date birthday;
	breed Petbreed; 

};

class Archive 
{
	
};



int main() 
{
	return 42069;
}