#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include "header1.h"

using namespace std;

Customer::Customer(string i, string n, int s, int t)
{
    custID = i;
    name = n;
    seating = s;
    time = t;
}
bool Customer::checkTime(int k) const
{
    return (time <= k);
}
bool Customer::operator<(const Customer a) const
{
    return (*this).time < a.time;
}
void Customer::setTime()
{
    time--;
}
void Customer::addToTime(int k)
{
    time += k;//add the time the customer was assigned to the table
}
int Customer::getTime()
{
    return time;
}
string Customer::getCustID()
{
    return custID;
}
string Customer::getName() const
{
    return name;
}
int Customer::getSeat() const
{
    return seating;
}
Table::Table(int n, string t)
{
    seatNum = n;
    tableNum = t;
    vacant = true;
}
Table Table::operator=(Table a)
{
    (*this).seatNum = a.seatNum;
    (*this).vacant = a.vacant;
    return *this;
}
bool Table::operator==(Table a)
{
    return ((*this).getTableNum() == a.getTableNum());
}
void Table::setVacant()
{
    vacant = !vacant;
}
bool Table::isVacant()
{
    return vacant;
}
int Table::getSeating()
{
    return seatNum;
}
string Table::getTableNum()
{
    return tableNum;
}
bool Table::operator<(Table a)
{
    return (*this).getSeating() < a.getSeating();
}
bool less(Table& a, Table& b)
{
    return a.getSeating() < b.getSeating();
}
bool less(Customer& a, Customer& b)
{
    return a.getTime() < b.getTime();
}
void func(pair<Customer, pair<Customer, Table>> p)
{
    cout << "Customer " << p.first.getName() << " with " << p.first.getSeat()
            << " people is seated at table " << p.second.second.getTableNum() << " with " << p.second.second.getSeating() << " seats" << endl;
}