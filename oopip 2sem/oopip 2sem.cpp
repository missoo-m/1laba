#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

class Employee 
{
public:
    string fio;
    string post; // должность

    Employee(const string& fio, const string& post) : fio(fio), post(post) {}

    virtual void printInfo() const
    {
        cout << "Имя: " << fio << ", Должность: " << post << endl;
    }

    virtual ~Employee() {} 
};

class Pilot : public Employee 
{
public:
    int license_number;

    Pilot(const string& fio, int license_number): Employee(fio, "Пилот"), license_number(license_number) {}

    void printInfo() const override
    {
        Employee::printInfo();
        cout << "Номер лицензии: " << license_number << endl;
    }
};

class FlightAttendant : public Employee 
{
public:
    string certification;

    FlightAttendant(const string& fio, const string& certification): Employee(fio, "Бортпроводник"), certification(certification) {}

    void printInfo() const override 
    {
        Employee::printInfo();
        cout << "Сертификация: " << certification << endl;
    }
};

class Flight 
{
public:
    string number_of_flight;
    string destination;     // пункт назначения
    string departure_point; // пункт вылета
    Employee* employees[5]; // cсоздаю команду (агрегация) тк сотрудники существуют сами по себе и создаются вне этого класса
    int employee_count;     // в итоге скок сотрудников 

    Flight(const string& number_of_flight, const string& destination, const string& departure_point): number_of_flight(number_of_flight), destination(destination), departure_point(departure_point), employee_count(0)
    {
        for (int i = 0; i < 5; i++) 
        {
            employees[i] = nullptr;
        }
    }

    void addEmployee(Employee* employee) 
    {
        if (employee_count < 5) 
        {
            employees[employee_count++] = employee;
        }
        else {
            cout << "Невозможно добавить больше сотрудников. Максимум 5." << endl;
        }
    }

    void printFlightInfo() const 
    {
        cout << "Рейс " << number_of_flight << ", пункт назначения: " << destination << ", пункт отправления: " << departure_point << endl;
        cout << "Команда: " << endl;

        for (int i = 0; i < employee_count; i++) 
        {
            employees[i]->printInfo();
        }
    }

    ~Flight() {} // Уничтожение сотрудников где-то не тут , так как это агрегация
       

};

class Airline 
{
public:
    string name_airline;
    Flight flight; // Композиция: рейс принадлежит авиакомпании( авиакомпания не может быть без рейса)

    Airline(const string& name_airline, const Flight& flight): name_airline(name_airline), flight(flight) {}

    void printAirlineInfo() const 
    {
        cout << "Авиакомпания: " << name_airline << endl;
        flight.printFlightInfo();
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
  
    Pilot pilot("Семечев А.В.", 23456789);
    FlightAttendant flightAttendant("Яровая В.А.", "29930493994");
    Employee employee("Старикова В.А.", "Помощник стюардессы");
    Flight flight("ZX234", "New York", "Varshava");
    
    // добавляем сотрудников (агрегация)
    flight.addEmployee(&pilot);
    flight.addEmployee(&flightAttendant);
    flight.addEmployee(&employee);

    // Создаем авиакомпанию (композиция)
    Airline airline("Sky_Airlines", flight);

    airline.printAirlineInfo();
    return 0;
}