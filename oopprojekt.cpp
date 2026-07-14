#include <iostream>
#include <string>
using std::string;
using namespace std;
#include <sstream>
#include <iomanip>

string formatDouble(double value)
{
    stringstream ss;
    ss << fixed << setprecision(2) << value;
    return ss.str();
}

class AbstractService
{
public:
    virtual ~AbstractService() {}

    virtual double calcPrice() = 0;
    virtual string textOutput() = 0;
    virtual string getName() = 0;
    virtual double getPrice() = 0;
    virtual int getDuration() = 0;
};

class BaseService : public AbstractService
{
private:
    string name;
    double price;
    int duration;

public:
    BaseService(string name, double price, int duration)
    {
        this->name = name;
        this->price = price;
        this->duration = duration;
    }

    string getName() override
    {
        return this->name;
    }

    double getPrice() override
    {
        return this->price;
    }

    int getDuration() override
    {
        return this->duration;
    }
};

class OilChange : public BaseService
{
private:
    string oil_type;
    double litres;
    double price_per_litre;

public:
    OilChange(string name, double price, int duration, string oil_type, double litres, double price_per_litre) : BaseService(name, price, duration)
    {
        this->oil_type = oil_type;
        this->litres = litres;
        this->price_per_litre = price_per_litre;
    }

    string getOilType()
    {
        return this->oil_type;
    }

    double getLitres()
    {
        return this->litres;
    }

    double getPricePerLitre()
    {
        return this->price_per_litre;
    }

    double calcPrice()
    {
        return this->getPrice() + this->getLitres() * this->getPricePerLitre();
    }

    string textOutput()
    {
        return this->getName() + ": " + this->getOilType() + ", litres: " + formatDouble(this->getLitres()) + ", duration: " + to_string(this->getDuration()) + " min, total price: " + formatDouble(this->calcPrice());
    }
};

class TireChange : public BaseService
{
private:
    int wheels;
    double price_per_wheel;

public:
    TireChange(string name, double price, int duration, int wheels, double price_per_wheel) : BaseService(name, price, duration)
    {
        this->wheels = wheels;
        this->price_per_wheel = price_per_wheel;
    }

    int getWheels()
    {
        return this->wheels;
    }

    double get_price_per_wheel()
    {
        return this->price_per_wheel;
    }

    double calcPrice()
    {
        return this->getPrice() + this->getWheels() * this->get_price_per_wheel();
    }

    string textOutput()
    {
        return this->getName() + ": " + to_string(this->getWheels()) + " wheels, duration: " + to_string(this->getDuration()) + " min, total price: " + formatDouble(this->calcPrice());
    }
};

class Diagnostics : public BaseService
{
private:
    int errorsFound;
    double pricePerError;

public:
    Diagnostics(string name, double price, int duration, int errorsFound, double pricePerError) : BaseService(name, price, duration)
    {
        this->errorsFound = errorsFound;
        this->pricePerError = pricePerError;
    }

    int getErrorsFound()
    {
        return this->errorsFound;
    }

    double getPricePerError()
    {
        return this->pricePerError;
    }

    double calcPrice()
    {
        return this->getPrice() + this->getErrorsFound() * this->getPricePerError();
    }

    string textOutput()
    {
        return this->getName() + ": " + to_string(this->errorsFound) + " errors found, duration: " + to_string(this->getDuration()) + " min, total price: " + formatDouble(this->calcPrice());
    }
};

class Customer
{
private:
    int id;
    string name;
    long phone;
    string email;

public:
    Customer(int id, string name, long phone, string email)
    {
        this->id = id;
        this->name = name;
        this->phone = phone;
        this->email = email;
    }

    int getID()
    {
        return this->id;
    }

    string getName()
    {
        return this->name;
    }

    long getPhone()
    {
        return this->phone;
    }

    string getEmail()
    {
        return this->email;
    }

    string textOutput()
    {
        return "Customer: " + this->getName() + " with ID " + to_string(this->getID()) + ", phone: " + to_string(this->getPhone()) + ", email: " + this->getEmail();
    }
};

class Car
{
private:
    string licensePlate;
    string brand;
    string model;
    int manufactureYear;
    Customer *owner;

public:
    Car(string licensePlate, string brand, string model, int manufactureYear, Customer *owner)
    {
        this->licensePlate = licensePlate;
        this->brand = brand;
        this->model = model;
        this->manufactureYear = manufactureYear;
        this->owner = owner;
    }

    string getLicensePlate()
    {
        return this->licensePlate;
    }

    string getBrand()
    {
        return this->brand;
    }

    string getModel()
    {
        return this->model;
    }

    int getManufactureYear()
    {
        return this->manufactureYear;
    }

    Customer *getOwner()
    {
        return this->owner;
    }

    string textOutput()
    {
        return "Car: " + this->getBrand() + " " + this->getModel() + ", plate: " + this->getLicensePlate() + ", year: " + to_string(this->getManufactureYear()) + ", owner: " + this->getOwner()->getName();
    }
};

class Mechanic
{
private:
    int id;
    string name;
    double hourlyRate;

public:
    Mechanic(int id, string name, double hourlyRate)
    {
        this->id = id;
        this->name = name;
        this->hourlyRate = hourlyRate;
    }

    int getID()
    {
        return this->id;
    }

    string getName()
    {
        return this->name;
    }

    double getRate()
    {
        return this->hourlyRate;
    }

    string textOutput()
    {
        return "Mechanic: " + this->getName() + " hourly rate : " + formatDouble(this->getRate());
    }
};

class ServiceOrder
{
private:
    int orderNum;
    Customer *customer;
    Car *car;
    Mechanic *mechanic;
    AbstractService **services;
    int servicesCount;
    int servicesSize;

public:
    ServiceOrder(int orderNum, Customer *customer, Car *car, Mechanic *mechanic, int servicesSize)
    {
        this->orderNum = orderNum;
        this->customer = customer;
        this->car = car;
        this->mechanic = mechanic;
        this->servicesSize = servicesSize;
        this->servicesCount = 0;
        this->services = new AbstractService *[this->servicesSize];
    }

    ~ServiceOrder()
    {
        for (int i = 0; i < servicesCount; i++)
        {
            delete this->services[i];
        }
        delete[] this->services;
    }

    void addService(AbstractService *service)
    {
        services[servicesCount] = service;
        servicesCount++;
    }

    double calcPrice()
    {
        double total = 0.0;
        for (int i = 0; i < servicesCount; i++)
        {
            total += this->services[i]->calcPrice();
        }
        return total;
    }

    string textOutput()
    {
        string text = "";
        text += "Service order #" + to_string(this->orderNum) + "\n";
        text += this->customer->textOutput() + "\n";
        text += this->car->textOutput() + "\n";
        text += this->mechanic->textOutput() + "\n";
        text += "Services:\n";
        for (int i = 0; i < servicesCount; i++)
        {
            text += this->services[i]->textOutput() + "\n";
        }

        text += "Total price: " + formatDouble(this->calcPrice());
        return text;
    }
};

class NumGenerator
{
private:
    static int nextCustomerID;
    static int nextMechanicID;
    static int nextOrderNum;

public:
    static int generateCustomerID()
    {
        nextCustomerID++;
        return nextCustomerID;
    }

    static int generateMechanicID()
    {
        nextMechanicID++;
        return nextMechanicID;
    }

    static int generateOrderNum()
    {
        nextOrderNum++;
        return nextOrderNum;
    }
};

int NumGenerator::nextCustomerID = 0;
int NumGenerator::nextMechanicID = 0;
int NumGenerator::nextOrderNum = 0;

class RepairShop
{
private:
    Customer **customers;
    Car **cars;
    Mechanic **mechanics;
    ServiceOrder **orders;

    int customersCount;
    int customersSize;

    int carsCount;
    int carsSize;

    int mechanicsCount;
    int mechanicsSize;

    int ordersCount;
    int ordersSize;

public:
    RepairShop(int customersSize, int carsSize, int mechanicsSize, int ordersSize)
    {
        this->customersSize = customersSize;
        this->customersCount = 0;
        this->carsSize = carsSize;
        this->carsCount = 0;
        this->mechanicsSize = mechanicsSize;
        this->mechanicsCount = 0;
        this->ordersSize = ordersSize;
        this->ordersCount = 0;
        this->customers = new Customer *[this->customersSize];
        this->cars = new Car *[this->carsSize];
        this->mechanics = new Mechanic *[this->mechanicsSize];
        this->orders = new ServiceOrder *[this->ordersSize];
    }

    ~RepairShop()
    {
        for (int i = 0; i < customersCount; i++)
        {
            delete this->customers[i];
        }
        delete[] this->customers;

        for (int i = 0; i < carsCount; i++)
        {
            delete this->cars[i];
        }
        delete[] this->cars;

        for (int i = 0; i < mechanicsCount; i++)
        {
            delete this->mechanics[i];
        }
        delete[] this->mechanics;

        for (int i = 0; i < ordersCount; i++)
        {
            delete this->orders[i];
        }
        delete[] this->orders;
    }

    //////////// PŘETÍŽENÍ METOD

    Customer *CreateCustomer(int id, string name, long phone, string email)
    {
        Customer *newCustomer = new Customer(id, name, phone, email);
        this->customers[this->customersCount] = newCustomer;
        this->customersCount++;
        return newCustomer;
    }

    Customer *CreateCustomer(string name, long phone, string email) //////// automatická generace ID pro zákazníka
    {
        Customer *newCustomer = new Customer(NumGenerator::generateCustomerID(), name, phone, email);
        this->customers[this->customersCount] = newCustomer;
        this->customersCount++;
        return newCustomer;
    }

    Car *CreateCar(string licensePlate, string brand, string model, int manufactureYear, Customer *owner)
    {
        Car *newCar = new Car(licensePlate, brand, model, manufactureYear, owner);
        this->cars[this->carsCount] = newCar;
        this->carsCount++;
        return newCar;
    }

    Mechanic *CreateMechanic(int id, string name, double hourlyRate)
    {
        Mechanic *newMechanic = new Mechanic(id, name, hourlyRate);
        this->mechanics[this->mechanicsCount] = newMechanic;
        this->mechanicsCount++;
        return newMechanic;
    }

    Mechanic *CreateMechanic(string name, double hourlyRate) ///////// Automaticky generuje ID pro mechanika
    {
        Mechanic *newMechanic = new Mechanic(NumGenerator::generateMechanicID(), name, hourlyRate);
        this->mechanics[this->mechanicsCount] = newMechanic;
        this->mechanicsCount++;
        return newMechanic;
    }

    ServiceOrder *CreateServiceOrder(int orderNum, Customer *customer, Car *car, Mechanic *mechanic, int servicesSize)
    {
        ServiceOrder *newServiceOrder = new ServiceOrder(orderNum, customer, car, mechanic, servicesSize);
        this->orders[this->ordersCount] = newServiceOrder;
        this->ordersCount++;
        return newServiceOrder;
    }

    ServiceOrder *CreateServiceOrder(Customer *customer, Car *car, Mechanic *mechanic, int servicesSize)
    {
        ServiceOrder *newServiceOrder = new ServiceOrder(NumGenerator::generateOrderNum(), customer, car, mechanic, servicesSize);
        this->orders[this->ordersCount] = newServiceOrder;
        this->ordersCount++;
        return newServiceOrder;
    }

    void printCustomers()
    {
        cout << "Customers" << endl;
        for (int i = 0; i < customersCount; i++)
        {
            cout << this->customers[i]->textOutput() << endl;
        }
    }

    void printCars()
    {
        cout << "Cars" << endl;
        for (int i = 0; i < carsCount; i++)
        {
            cout << this->cars[i]->textOutput() << endl;
        }
    }

    void printMechanics()
    {
        cout << "Mechanics" << endl;
        for (int i = 0; i < mechanicsCount; i++)
        {
            cout << this->mechanics[i]->textOutput() << endl;
        }
    }

    void printOrders()
    {
        cout << "Orders" << endl;
        for (int i = 0; i < ordersCount; i++)
        {
            cout << this->orders[i]->textOutput() << endl;
            cout << endl;
        }
    }
};

int main()
{

    RepairShop *shop = new RepairShop(50, 50, 50, 50);

    Customer *c1 = shop->CreateCustomer("Jon", 894465466, "jon@mail.com");
    Customer *c2 = shop->CreateCustomer("Keivn", 894465460, "kevin@mail.com");
    Customer *c3 = shop->CreateCustomer("Tomas", 894465462, "tomas@mail.com");
    Customer *c4 = shop->CreateCustomer("Martin", 894465461, "martin@mail.com");
    Customer *c5 = shop->CreateCustomer("Lucie", 894465463, "lucie@mail.com");
    Customer *c6 = shop->CreateCustomer(6567562, "Peter", 894465465, "peter@mail.com");

    Car *car1 = shop->CreateCar("4A12345", "Škoda", "Octavia", 2020, c1);
    Car *car2 = shop->CreateCar("4A12346", "Mercedes", "S65", 2006, c2);
    Car *car3 = shop->CreateCar("4A12347", "Ford", "Mustang", 2015, c3);
    Car *car4 = shop->CreateCar("4A12348", "Opel", "Corsa", 2006, c4);
    Car *car5 = shop->CreateCar("4A12331", "Volvo", "V70", 2014, c5);
    Car *car6 = shop->CreateCar("4A12365", "Bmw", "M4", 2018, c6);

    Mechanic *m1 = shop->CreateMechanic("Rob K", 300);
    Mechanic *m2 = shop->CreateMechanic(322432, "Shawn W", 320);
    Mechanic *m3 = shop->CreateMechanic(89895, "Joe L", 500);
    Mechanic *m4 = shop->CreateMechanic(998759, "Chad", 1000);

    ServiceOrder *o1 = shop->CreateServiceOrder(c1, car1, m2, 3);
    o1->addService(new TireChange("Tire change", 400, 60, 2, 200));
    o1->addService(new OilChange("Oil", 300, 20, "5w-30", 4, 100));

    ServiceOrder *o2 = shop->CreateServiceOrder(c2, car2, m4, 3);
    o2->addService(new Diagnostics("Diagnostics", 1000, 120, 2, 700));
    o2->addService(new OilChange("Oil", 400, 30, "5w-40", 3, 200));

    ServiceOrder *o3 = shop->CreateServiceOrder(c3, car3, m3, 3);
    o3->addService(new Diagnostics("Diagnostics", 700, 100, 4, 500));
    o3->addService(new OilChange("Oil", 200, 50, "5w-40", 2, 150));
    o3->addService(new TireChange("Tire change", 500, 120, 4, 400));

    ServiceOrder *o4 = shop->CreateServiceOrder(c4, car4, m1, 3);
    o4->addService(new OilChange("Oil", 130, 30, "5w40", 2, 150));
    o4->addService(new TireChange("Tire change", 300, 80, 4, 100));

    ServiceOrder *o5 = shop->CreateServiceOrder(c5, car5, m1, 3);
    o5->addService(new Diagnostics("Diagnostics", 400, 100, 0, 200));
    o5->addService(new TireChange("Tire change", 300, 45, 1, 120));

    ServiceOrder *o6 = shop->CreateServiceOrder(c6, car6, m4, 3);
    o6->addService(new Diagnostics("Diagnostics", 500, 120, 4, 600));
    o6->addService(new TireChange("Tire change", 300, 100, 4, 250));
    o6->addService(new OilChange("Oil", 220, 45, "5w-40", 2.5, 175));

    shop->printCustomers();
    cout << endl;

    shop->printCars();
    cout << endl;

    shop->printMechanics();
    cout << endl;

    shop->printOrders();
    delete shop;

    return 0;
}