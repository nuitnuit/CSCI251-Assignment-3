#pragma once
#include <string>

using namespace std;

class Customer
{
    string custID, name;
    int seating, time;
    public:
    Customer(string, string, int, int);
    bool checkTime(int) const;
    void setTime();
    int getTime();
    int getSeat() const;
    bool operator<(const Customer) const;
    void addToTime(int);
    string getCustID();
    string getName() const;
    string display();
};

class Table
{
    bool vacant;
    int seatNum;
    string tableNum;
    public:
    Table(int, string);
    bool operator<(Table);
    Table operator=(Table);
    bool operator==(Table);
    bool isVacant();
    void setVacant();
    string getTableNum();
    int getSeating();
};
bool less(Table&, Table&);
bool less(Customer&, Customer&);
void func(pair<Customer, pair<Customer, Table>>);