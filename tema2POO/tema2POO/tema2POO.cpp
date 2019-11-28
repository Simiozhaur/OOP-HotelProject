#include <iostream>
#include <list>
#include <math.h>
#include <vector>
#include <utility>
#include <typeinfo>

using namespace std;


class Room {
protected:
	list<string> Cazati;
	string RoomType;
	int RoomNumber;
	int MaxSize;
	bool Disp[365] = { false };

public:

	void addCazat(string nume) { this->Cazati.push_back(nume); }
	bool getDisp(int i) { return this->Disp[i]; }
	int getMaxSize() { return this->MaxSize; }
	int getRoomNr() { return this->RoomNumber; }

	void setRoomNr(int nr)
	{
		this->RoomNumber = nr;
	}

	void setDisp(int ziinceput, int zifinal)
	{
		for (int i = ziinceput; i < zifinal; i++)
		{
			if (Disp[i] == false)
			{
				Disp[i] = true;
			}
			else if (Disp[i] == true)
				Disp[i] = false;
		}

	}

	Room(int rnum)
	{
		this->RoomNumber = rnum;
	}

	Room()
	{
		this->RoomNumber = 0;
		this->MaxSize = 0;
	}

	//Room(const Room& a)
	//{
	//	for (int i = 0; i < 365; i++)
	//	{
	//		this->Disp[i] = a.Disp[i];
	//	}
	//	this->MaxSize = a.MaxSize;
	//	this->RoomNumber = a.RoomNumber;
	//	this->RoomType = a.RoomType;
	//}

	friend ostream& operator<<(ostream&, Room&);

	//virtual ~Room();

};

ostream& operator<<(ostream& out, Room& r)
{
	out << "Room number: " << r.RoomNumber << " || " << "Room type: " << r.RoomType << endl;
	return out;
}


class Double : public Room {
public:
	Double(int i) : Room(i)
	{
		this->MaxSize = 2;
		this->RoomNumber = i;
		this->RoomType = "Double Room";
	}

	void checkin(int i, int f)
	{
		string nume;
		setDisp(i, f);
		cout << "Numele primului participant: ";
		cin >> nume;
		this->Cazati.push_back(nume);
		cout << "Numele celui de al doilea participant: ";
		cin >> nume;
		this->Cazati.push_back(nume);
	}
};


class Apartament : public Room {
public:
	Apartament(int i) : Room(i)
	{
		this->MaxSize = 4;
		this->RoomNumber = i;
		this->RoomType = "Apartament";
	}
};

class Restaurant : public Room {
public:
	Restaurant(int i) : Room(i)
	{
		this->MaxSize = 20;
		this->RoomNumber = i;
		this->RoomType = "Restaurant";
	}
};

class ConfRoom : public Room {
protected:
	int confType;
public:

	int getType() { return this->confType; }
	void setType(int i) { this->confType = i; }

	ConfRoom(int i, int size, int type) : Room(i)
	{
		this->MaxSize = size;
		this->RoomNumber = i;
		this->confType = type;

		switch (type)
		{
		case 0:
			this->RoomType = "Sala cu videoproiector";
			break;
		case 1:
			this->RoomType = "Sala cu mese individuale";
			break;
		case 2:
			this->RoomType = "Sala cu scena";
			break;
		default:
			this->RoomType = "Sala de conferinta neidentificata";
		}
	}

	friend ostream& operator<<(ostream&, ConfRoom&);

};

ostream& operator<<(ostream& out, ConfRoom& r)
{
	out << "Room number: " << r.RoomNumber << " || " << "Room type: " << r.RoomType << " || Max Capacity:" << r.MaxSize << endl;
	return out;
}

Double availabledbl(vector<Double> a, Double b)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].getRoomNr() == b.getRoomNr())
			return a[i];
	}
}

Apartament availableapts(vector<Apartament> a, Apartament b)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].getRoomNr() == b.getRoomNr())
			return a[i];
	}
}

ConfRoom availableConf(vector<ConfRoom> a, int tip)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].getType() == tip)
		{
			return a[i];
		}
	}
}



class Reservation {
protected:
	list<Room> ResRooms;
	int inceput;
	int final;
	int nrpersoane;
	bool confirmare;
	static int id;
	int thisId;
public:
	Reservation(vector<Room>, int, int, int);

	list<Room> const& getRes() const { return ResRooms; }
	void setConfirmare(bool a) { this->confirmare = a; }
	void setRes(const list<Room>& y) { ResRooms = y; }
	int getNrPersoane() { return this->nrpersoane; }
	int getInceput() { return this->inceput; }
	int getFinal() { return this->final; }

	bool CheckAv(Room test)
	{
		for (int i = this->inceput; i < this->final; i++)
		{
			if (test.getDisp(i) == true)
				return false;
		}
		return true;
	}

	Reservation()
	{
		id++;
		thisId = id;
		confirmare = false;
	}

	void citire(vector<Double>& dbl, vector<Apartament>& apts, vector<ConfRoom>& conf) {

		vector<Double> tempdbl;
		vector<Apartament> tempapts;
		vector<ConfRoom> tempconf;

		cout << "Pentru cate persoane este rezervarea? ";
		cin >> this->nrpersoane;

		try {
			if (nrpersoane > 24) {
				throw "Peste capacitatea hotelului ";
			}
			else if (nrpersoane < 0)
			{
				throw "Nu poate fi un numar negativ ";
			}
		}
		catch (const char* exp) {
			cout << "Error: " << exp << endl; return;
		}


		cout << "In ce zi a anului este check-inul? ";
		cin >> this->inceput;
		try {
			if (inceput > 365) {
				throw "Valoarea trebuie sa fie mai mica decat 365";
			}
			else if (nrpersoane < 0)
			{
				throw "Nu poate fi un numar negativ ";
			}
		}
		catch (const char* exp) {
			cout << "Error: " << exp << endl; return;
		}

		cout << "In ce zi a anului este check-outul? ";
		cin >> this->final;
		try {
			if (final > 365) {
				throw "Valoarea trebuie sa fie mai mica decat 365";
			}
			else if (final < 0)
			{
				throw "Nu poate fi un numar negativ ";
			}
			else if (final <= inceput)
			{
				throw "Nu se poate face check-out inainte de check-in";
			}
			else if (final - inceput > 10)
			{
				throw "Perioada de sedere prea mare";
			}
		}

		catch (const char* exp) {
			cout << "Error: " << exp << endl; return;
		}

		for (int i = 0; i < dbl.size(); i++)
		{
			if (CheckAv(dbl[i]) == true)
				tempdbl.push_back(dbl[i]);
		}

		for (int i = 0; i < apts.size(); i++)
		{
			if (CheckAv(apts[i]) == true)
				tempapts.push_back(apts[i]);
		}

		for (int i = 0; i < conf.size(); i++)
		{
			if (CheckAv(conf[i]) == true)
				tempconf.push_back(conf[i]);
		}


		try {
			if (tempdbl.size() == 0 && tempapts.size() == 0) {
				throw "Nu exista disponibilitate in perioada respectiva";
			}
			else if (((tempdbl.size()) * 2 + (tempapts.size() * 4)) < nrpersoane) {
				throw "Locuri insuficiente";
			}
		}
		catch (const char* exp) {
			cout << "Error: " << exp << endl; return;
		}

		int ramasdecazat = nrpersoane;
		for (int i = 0; ramasdecazat > 0 && i < tempdbl.size(); i++)
		{
			ResRooms.push_back(availabledbl(dbl, tempdbl[i]));
			ramasdecazat = ramasdecazat - 2;
		}

		for (int i = 0; ramasdecazat > 0 && i < tempapts.size(); i++)
		{
			ResRooms.push_back(availableapts(apts, tempapts[i]));
			ramasdecazat = ramasdecazat - 2;
		}

		cout << "Camere in care au fost cazati participantii:" << endl;

		for (std::list<Room>::iterator i = ResRooms.begin(); i != ResRooms.end(); ++i)
		{
			cout << *i << endl;
		}

		int raspuns;
		cout << "Doriti camera de conferinte?" << endl;
		cout << "0 - NU |||||| 1 - DA" << endl;
		cin >> raspuns;
		if (raspuns == 1)
		{
			cout << "Ce fel de camera de conferinta? " << endl;
			cout << "0 - Cu proiector || 1 - Mese individuale || 2 - Sala cu scena" << endl;
			cin >> raspuns;
			switch (raspuns)
			{
			case 0:
				ResRooms.push_back(availableConf(tempconf, raspuns));
				break;
			case 1:
				ResRooms.push_back(availableConf(tempconf, raspuns));
				break;
			case 2:
				ResRooms.push_back(availableConf(tempconf, raspuns));
				break;
			default:
				cout << "Invalid" << endl;
			}

		}

		string tempname;
		int rms = nrpersoane;

		for (std::list<Room>::iterator i = ResRooms.begin(); i != ResRooms.end(); ++i)
		{
			i->setDisp(this->inceput, this->final);
			for (int j = 0; j < dbl.size(); j++)
			{
				if (i->getRoomNr() == dbl[j].getRoomNr())
				{
					dbl[j].setDisp(inceput, final);
					if (rms > 0) {
						cout << "Nume primului participant: ";
						cin >> tempname;
						dbl[j].addCazat(tempname);
						rms--;
					}
					if (rms > 0) {
						cout << "Numele celui de al doilea participant: ";
						cin >> tempname;
						dbl[j].addCazat(tempname);
						rms--;
					}
				}
			}

			for (int j = 0; j < apts.size(); j++)
			{
				if (i->getRoomNr() == apts[j].getRoomNr())
				{
					apts[j].setDisp(inceput, final);
					if (rms > 0) {
						cout << "Nume primului participant: ";
						cin >> tempname;
						apts[j].addCazat(tempname);
						rms--;
					}
					if (rms > 0) {
						cout << "Nume celui de al doilea participant: ";
						cin >> tempname;
						apts[j].addCazat(tempname);
						rms--;
					}
					if (rms > 0) {
						cout << "Nume celui de al treilea participant: ";
						cin >> tempname;
						apts[j].addCazat(tempname);
						rms--;
					}
					if (rms > 0) {
						cout << "Nume celui de al patrulea participant: ";
						cin >> tempname;
						apts[j].addCazat(tempname);
						rms--;
					}
				}
			}

			for (int j = 0; j < conf.size(); j++)
			{
				if (i->getRoomNr() == conf[j].getRoomNr())
				{
					conf[j].setDisp(inceput, final);
				}
			}

		}

		if (ResRooms.size() == 0)
		{
			this->confirmare = true;
		}
	}

	void PrintRezervare()
	{

		cout << endl;
		cout << "--------------------" << endl;
		cout << "Camerele rezervate: " << endl;
		cout << "--------------------" << endl;
		for (std::list<Room>::iterator i = ResRooms.begin(); i != ResRooms.end(); ++i)
			cout << *i;
		cout << "Id rezervare: " << thisId - 1 << endl;
		cout << "Check-in " << inceput << " Check-out " << final << endl;
		cout << "Numarul de persoane: " << nrpersoane << endl;
		cout << "--------------------" << endl;
		cout << endl;
	}

};

int Reservation::id;

void AnulareRezervare(Reservation& r, vector<Double>& dbl, vector<Apartament>& apts, vector<ConfRoom>& conf)
{
	list<Room> temp = r.getRes();
	for (std::list<Room>::iterator i = temp.begin(); i != temp.end(); ++i)
	{
		i->setDisp(r.getInceput(), r.getFinal());

		for (int i = 0; i < dbl.size(); i++)
		{
			if (typeid(dbl[i]) == (typeid(i)))
			{
				dbl[i].setDisp(r.getInceput(), r.getFinal());
			}
		}
		for (int i = 0; i < apts.size(); i++)
		{
			if (typeid(apts[i]) == (typeid(i)))
			{
				apts[i].setDisp(r.getInceput(), r.getFinal());
			}
		}
		for (int i = 0; i < conf.size(); i++)
		{
			if (typeid(conf[i]) == (typeid(i)))
			{
				conf[i].setDisp(r.getInceput(), r.getFinal());
			}
		}
	}
	temp.clear();
	r.setRes(temp);
	r.setConfirmare(true);


}

Reservation::Reservation(vector<Room> room, int inc, int fin, int participanti) {
	for (int i = 0; i < room.size(); i++)
	{
		this->ResRooms.push_back(room[i]);
	}
	this->inceput = inc;
	this->final = fin;
	this->nrpersoane = participanti;
}


int main()
{

	list<Room> HotelRooms;
	vector<Double> DoubleRooms;
	vector<Apartament> Apartments;
	vector<ConfRoom> ConffrenceRooms;

	Restaurant r10 = Restaurant(10);
	ConfRoom r100 = ConfRoom(100, 4, 0);
	ConfRoom r101 = ConfRoom(101, 8, 1);
	ConfRoom r102 = ConfRoom(102, 40, 2);
	Double r200 = Double(200);
	Double r201 = Double(201);
	Apartament r202 = Apartament(202);
	Double r300 = Double(300);
	Double r301 = Double(301);
	Double r302 = Double(302);
	Apartament r303 = Apartament(303);
	Double r400 = Double(400);
	Apartament r403 = Apartament(403);

	DoubleRooms = { r200, r201, r300, r301, r302, r400 };
	Apartments = { r202, r303 ,r403 };
	ConffrenceRooms = { r100, r101, r102 };

	HotelRooms = { r10 , r100, r101, r102, r200, r201, r202, r300, r301, r302, r303, r400, r403 };



	int Alegere = 1, ResSize = 0;
	Reservation r[10];

	cout << "------------" << endl;
	cout << "  MENIU  " << endl;
	cout << "------------" << endl;
	cout << "0 - Iesire din meniu" << endl;
	cout << "1 - Rezervare noua" << endl;
	cout << "2 - Anulare Rezervare" << endl;
	cout << "3 - Afisare Rezervari" << endl;

	/*while (Alegere != 0)
	{
		cin >> Alegere;
		switch (Alegere) {
		case 1:
			ResSize++;
			r = new Reservation[ResSize];
			r[ResSize].citire(DoubleRooms, Apartments, ConffrenceRooms);
			break;
		case 2:
			int tempid;
			cout << "Id-ul rezervarii care trebuie anulata: ";
			cin >> tempid;
			AnulareRezervare(r[ResSize], DoubleRooms, Apartments, ConffrenceRooms);
			break;
		case 3:
			for (int i = 1; i <= ResSize; i++)
			{
				r[i].PrintRezervare();
			}
			break;
		default:
			cout << "Input gresit ";

		}

	}*/

	r[0].citire(DoubleRooms, Apartments, ConffrenceRooms);



}

