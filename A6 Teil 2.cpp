/***********************************************************************
Matr.-Nr:                     3071014
Nachname/Surname:             Bhuyan
Vorname/Given name:           Mohammad Rakib
Uni-Email:                    mohammad.bhuyan@stud.uni-due.de
Studiengang/Course of studis: ISE Computer Engineering
***********************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

enum struct Frequency {once, daily, weekly, monthly};

ostream &operator << (ostream &out, const enum Frequency &f)
{
    switch(f)
    {
        case Frequency::once:
        {
            return out << "once";
            break;
        }
        case Frequency::daily:
        {
            return out << "daily";
            break;
        }
        case Frequency::weekly:
        {
            return out << "weekly";
            break;
        }
        case Frequency::monthly:
        {
            return out << "monthly";
            break;
        }
    }
}

class CO2Emission
{
private:
    CO2Emission *next;

public:
    CO2Emission()
    {
        next = nullptr;
    }

    virtual ~CO2Emission()
    {
        cout << "destructor CO2Emission: done" << endl << endl;
    }

    CO2Emission* get_next()
    {
        return next;
    }

    void set_next(CO2Emission *e)
    {
        next = e;
    }

    virtual float get_co2()
    {
        // nothing
    }

    virtual void print()
    {
        // nothing
    }
};

class Transport: public CO2Emission
{
private:
    float km;
    Frequency f;
    virtual float get_co2_pkm()
    {
        // nothing
    }

public:
    Transport()
    {
        cout << "transport distance kilometers: ";
        cin >> km;
        cout << "frequency input:" << endl
             << "(o) once" << endl
             << "(d) daily" << endl
             << "(m) monthly" << endl
             << "(w) weekly" << endl
             << "your choice: ";
            string input;
            cin >> input;
            if (input == "o")
            {
                f = Frequency::once;
            }
            else if (input == "d")
            {
                f = Frequency::daily;
            }
            else if (input == "m")
            {
                f = Frequency::monthly;
            }
            if (input == "w")
            {
                f = Frequency::weekly;
            }
    }
    Transport(float km, Frequency f = Frequency::once):
        km(km),
        f(f)
        {}

    virtual ~Transport()
    {
        cout << " destructor Transport: " << f << " " << fixed << setprecision(1) << km << " km done" << endl;
    }

    float get_co2()
    {
        if(f == Frequency::once)
        {
            return get_co2_pkm() * km;
        }
        if(f == Frequency::daily)
        {
            return get_co2_pkm() * km * 365;
        }
        if(f == Frequency::weekly)
        {
            return get_co2_pkm() * km * 52;
        }
        if(f == Frequency::monthly)
        {
            return get_co2_pkm() * km * 12;
        }
    }

    void print()
    {
        cout << "transport ";
        if (f == Frequency::once)
        {
            cout << km << " km (" << fixed << setprecision(3) << get_co2_pkm() << " kg CO2/pkm) " << fixed << setprecision(1) << get_co2() << " kg CO2" << endl;
        }
        else
        {
            cout << f << " " << fixed << setprecision(1) << km << " km (" << fixed << setprecision(3) << get_co2_pkm() << " kg CO2/pkm) " << fixed << setprecision(1) << get_co2() << " kg CO2" << endl;
        }
    }
};

class Bus: public Transport
{
private:
    bool local_transport;

    float get_co2_pkm()
    {
        if(local_transport == true)
        {
            return 0.111;
        }
        else if(local_transport == false)
        {
            return 0.036;
        }
    }
public:
    Bus()
    {
        char choice;
        cout << "(1) local transport" << endl
             << "(2) long distance" << endl
             << "your choice: ";
        cin >> choice;
        cout << endl;
        if(choice == '1')
        {
            local_transport = true;
        }
        else if(choice == '2')
        {
            local_transport = false;
        }
    }

    Bus(bool local_transport, float km):
        Transport(km),
        local_transport(local_transport)
        {}

    void print()
    {
        if (local_transport == false)
        {
            cout << "long distance bus ";
        }
        else if (local_transport == true)
        {
            cout << "local bus ";
        }
        Transport::print();
    }
    ~Bus()
    {
        cout << "  destructor Bus: ";
        print();
    }
};

class Car: public Transport
{
private:
    float l_fuel_km; // liters consumption of fuel per 100 km

    float get_co2_pkm() // changed to "pkm" so that it is recognized as an overriding function
    {
        return l_fuel_km / 100 * 2.3; // l_fuel_km / 100 = liter consumption per 1 km
    }
public:
    Car()
    {
        cout << "passenger car consumption liter petrol per 100 km: ";
        cin >> l_fuel_km;
    }

    Car(float l_fuel_km, float km):
        l_fuel_km(l_fuel_km),
        Transport(km)
        {}

    void print()
    {
        cout << "passenger car ";
        Transport::print();
    }
    ~Car()
    {
        cout << "  destructor Car: ";
        print();
    }
};

class Flight: public Transport
{
private:
    float get_co2_pkm()
    {
        return 0.27;
    }

public:
    Flight()
    {}

    Flight(float km):
        Transport(km)
        {}

    void print()
    {
        cout << "flight ";
        Transport::print();
    }
    ~Flight()
    {
        cout << "destructor Flight: done";
        print();
    }
};

class Train: public Transport
{
private:
    bool local_transport;
    bool one_way;

    float get_co2_pkm()
    {
        if(local_transport == true)
        {
            return 0.085;
        }
        else if(local_transport == false)
        {
            return 0.035;
        }
    }
public:
    Train()
    {
        int choice_local_transport;
        cout << "(1) local transport train" << endl
             << "(2) long distance train" << endl
             << "your choice: ";
        cin >> choice_local_transport;
        if(choice_local_transport == 1)
        {
            local_transport = true;
        }
        else if(choice_local_transport == 2)
        {
            local_transport = false;
        }
        int choice_one_way;
        cout << "(1) one-way" << endl
             << "(2) return" << endl
             << "your choice: ";
        cin >> choice_one_way;
        if(choice_one_way == 1)
        {
            one_way = true;
        }
        else if(choice_one_way == 2)
        {
            one_way = false;
        }
    }

    Train(bool local_transport, bool one_way, float km):
        local_transport(local_transport),
        one_way(one_way),
        Transport(km)
        {}

    float get_co2()
    {
        if (one_way == false)
        {
            return 2 * Transport::get_co2();
        }
        else if (one_way == true)
        {
            return Transport::get_co2();
        }
    }

    void print()
    {
        if (one_way == false)
        {
            cout << "return ";
        }
        else if (one_way == true)
        {
            cout << "one way ";
        }
        if (local_transport == false)
        {
            cout << "long distance train ";
        }
        else if (local_transport == true)
        {
            cout << "local train ";
        }
        Transport::print();
    }
    ~Train()
    {
        cout << "  destructor Train: ";
        print();
    }
};

class Cruise: public CO2Emission
{
private:
    float days;
    float sea_days;

    float get_co2_day(bool is_sea_day)
    {
        if(is_sea_day == true)
        {
            return 280;
        }
        else if(is_sea_day == false)
        {
            return 190;
        }
    }
public:
    Cruise()
    {
        cout << "cruise holiday data input: " << endl
             << "number of days of the whole cruise: ";
        cin >> days;
        cout << "number of sea days: ";
        cin >> sea_days;
    }

    Cruise(float days, float sea_days):
        days(days),
        sea_days(sea_days)
        {}

    float get_co2()
    {
        return get_co2_day(true)*sea_days + get_co2_day(false)*(days - sea_days);
    }

    void print()
    {
        cout << "cruise holiday (without flights): " << fixed << setprecision(0) << days << " days duration with " << fixed << setprecision(0) << sea_days << " sea days (sea day) " << fixed << setprecision(3) << get_co2_day(true) << " kg CO2/pkm, harbour day " << fixed << setprecision(3) << get_co2_day(false) << " kg CO2/pkm) " << fixed << setprecision(1) << get_co2() << " kg CO2" << endl;
    }
    virtual ~Cruise()
    {
        cout << "  destructor Cruise: ";
        print();
    }
};

class CO2Footprint
{
private:
    string name;
    CO2Emission *emissions;

public:
    CO2Footprint(string name):
        name(name),
        emissions(nullptr)
        {}
    ~CO2Footprint()
    {
        cout << "destructor for CO2Footprint for: " << name << " started..." << endl;
        CO2Emission *toDelete;
        while (toDelete->get_next() != nullptr)
        {
            toDelete = emissions;
            emissions = emissions->get_next();
            delete toDelete;
        }
        cout << "destructor CO2Footprint: done";
    }
    string get_name()
    {
        return name;
    }
    void add(CO2Emission *e)
    {
        e->set_next(emissions);
        emissions = e;
    }

    float get_sum_co2()
    {
        CO2Emission *head = emissions;
        float sum = 0;
        while(head != nullptr)
        {
            sum = sum + head->get_co2();
            head = head->get_next();
        }
        return sum;
    }
    virtual void print()
    {
        cout << "CO2 FOOTPRINT FOR: " << name << endl;
        CO2Emission *e = emissions;
        while(e != nullptr)
        {
            e->print();
            e = e->get_next();
        }
        cout << "TOTAL CO2 EMISSIONS: " << endl;
        cout << fixed << setprecision(1) << get_sum_co2() << " kg = "<< fixed << setprecision(1) << get_sum_co2()/1000 << " tons" << endl << endl;
    }
};

class Power: public CO2Emission
{
private:
    float kWh;

    virtual float get_co2_kWh()
    {
        // nothing
    }
public:
    Power()
    {
        cout << "power data input kilo Watt hours: ";
        cin >> kWh;
    }

    Power(float kWh):
        kWh(kWh)
        {}

    virtual ~Power()
    {
        cout << "  destructor Power: " << kWh << " kWh done" << endl;
    }
    float get_co2()
    {
        return get_co2_kWh() * kWh;
    }
    void print()
    {
        cout << "power " << kWh << " kWh (" << fixed << setprecision(3) << get_co2_kWh() << " kg CO2/kWh) " << fixed << setprecision(1) << get_co2() << " kg CO2" << endl;
    }
};

class Solar: public Power
{
private:
    float get_co2_kWh()
    {
        return 0.143;
    }
public:

    Solar()
    {}

    Solar(float kWh):
        Power(kWh)
        {}

    virtual ~Solar()
    {
        cout << "  destructor Solar: ";
        print();
    }

    void print()
    {
        cout << "solar ";
        Power::print();
    }
};

class Gas: public Power
{
private:
    bool bio;
    float get_co2_kWh()
    {
        if(bio == true)
        {
            return 0.230;
        }
        else if(bio == false)
        {
            return 0.819;
        }
    }

public:
    Gas()
    {
        char choice;
        cout << "gas power data input: " << endl
         << "(b) bio gas" << endl
         << "(f) fossil natural gas" << endl
         << "your choice: ";
        cin >> choice;
        if(choice == 'b')
        {
            bio = true;
        }
        else if(choice == 'f')
        {
            bio = false;
        }
    }

    Gas(bool bio, float kWh):
        bio(false),
        Power(kWh)
        {}

    virtual ~Gas()
    {
        cout << "  destructor Gas: ";
        print();
    }

   void print()
    {
        if(bio == true)
        {
            cout << "bio gas ";
        }
        else if(bio == false)
        {
            cout << "fossil natural gas ";
        }
        Power::print();
    }
};

int main()
{
    Bus *b2 = new Bus(true, 2200);
    Car *c2 = new Car(7.5, 5500);
    Cruise *h2 = new Cruise(14, 3);
    Flight *f2 = new Flight(2669.9);
    Train *t2 = new Train(false, false, 628.8);
    Solar *s2 = new Solar(1500);
    Gas *g2 = new Gas(false, 1500);
    string name;
    cout << "Please input your name for CO2 footprint: ";
    cin >> name;
    cout << endl;
    CO2Footprint f(name);
    f.add(b2);
    f.add(c2);
    f.add(h2);
    f.add(f2);
    f.add(t2);
    f.add(s2);
    f.add(g2);
    char choice;
    do
    {
        cout << "CO2 footprint input for: " << name << endl
             << "(e) end" << endl
             << "(b) bus transport" << endl
             << "(c) car transport" << endl
             << "(f) flight transport" << endl
             << "(h) holiday cruise" << endl
             << "(t) train transport" << endl
             << "(s) power from solar" << endl
             << "(g) power from gas" << endl
             << "(p) print all" << endl
             << ">> ";
        cin >> choice;
        switch (choice)
        {
            case 'e':
                break;
            case 'b':
            {
                Bus *bus = new Bus;
                f.add(bus);
                break;
            }
            case 'c':
            {
                Car *car = new Car;
                f.add(car);
                break;
            }
            case 'f':
            {
                Flight *flight = new Flight;
                f.add(flight);
                break;
            }
            case 'h':
            {
                Cruise *holidayCruise = new Cruise;
                f.add(holidayCruise);
                break;
            }
            case 't':
            {
                Train *train  = new Train;
                f.add(train);
                break;
            }
            case 's':
            {
                Solar *solar = new Solar;
                f.add(solar);
                break;
            }
            case 'g':
            {
                Gas *gas = new Gas;
                f.add(gas);
                break;
            }
            case 'p':
            {
                f.print();
                break;
            }
            default: cerr << "Sorry, wrong choice. Please choose e, b, c, f, h, t, or p. " << endl;
        }
    } while(choice != 'e');
    return 0;
}
