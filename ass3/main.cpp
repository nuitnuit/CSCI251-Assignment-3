#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
#include <deque>
#include <algorithm>
#include <vector>
#include <map>
#include "header1.h"

using namespace std;

int main()
{
    //need a vector for tables, name it tableList
    //a queue for customers
    //customers who are seated to a table will be stored
    //in a map as a key, and the table as value
    //must store it in a pair object before adding to map
    //the record is removed from the map when a customer leaves
    //should contain a loop to show the process of sassigning customers to the tables

    //before each iteration, check for customers leaving first
    //if customer leaving, then remove table and customer
    //pair from map and set that table to vacant
    //then check for empty tables
    //if empty table is available, then assign customer to
    //that table if the customer number lesser or equal
    //to the seat amount of that table
    //add that customer and table pair into map
    //remove customer from queue
    //set table to not vacant

    ifstream readFile;

    int custNum, counter = 0, tableNum, seats, clock = 0;
    string fileStr, table;

    deque<Customer> custList;
    vector<Table> tableList;
    map<Customer, pair<Customer, Table>> customerTableMap;
    readFile.open("tables.txt", ios::in);
    getline(readFile, fileStr);
    tableNum = stoi(fileStr);
    //reads all tables information
    while(!readFile.eof())
    {
        switch(counter % 2)
        {
            case 0:
            {
                getline(readFile, table);
                break;
            }
            case 1:
            {
                getline(readFile, fileStr);
                seats = stoi(fileStr);
                Table aNewTable = Table(seats, table);
                tableList.emplace_back(aNewTable);
                break;
            }
        }
        counter++;
    }
    readFile.close();
    readFile.open("customers.txt", ios::in);
    getline(readFile, fileStr);
    custNum = stoi(fileStr);
    //the number of customers read will be decided randomly
    srand(time(NULL));
    while(custNum > 0 || custList.size() > 0)
    {
        cout << "\nCurrent empty tables: " << endl;
        for(int i = 0; i < tableList.size(); i++)
        {
            cout << tableList.at(i).getTableNum() << " " << tableList.at(i).getSeating() << " seater" << endl;
        }
        cout << "\nWaiting list: " << endl;
        for (int i = 0; i < custList.size(); i++)
        {
            cout << (i + 1) << ". " << custList.at(i).getName() << endl;
        }
        cout << "\nSeated customers and their tables: " << endl;
        for_each(customerTableMap.begin(), customerTableMap.end(), func);//disply all seated customers
        cout << "\nRemoving any customers that are already going to leave either by force or compliance" << endl;
        for (map<Customer, pair<Customer, Table>>::iterator i = customerTableMap.begin(); i != customerTableMap.end(); i++)
        {
            if ((*i).first.checkTime(clock))
            {
                cout << "\n" << (*i).first.getName() << " will be leaving and leaving table #"
                << (*i).second.second.getTableNum() << " with " << (*i).second.second.getSeating()
                << " seat vacant" << endl;
                //remove customer table from map, then reset table to not vacant
                (*i).second.second.setVacant();
                tableList.emplace_back((*i).second.second);//clone back the table
                customerTableMap.erase(i);//strap customer with table on rocket
                custNum--;//bye bye customer
                break;
            }
        }
        cout << "\nChecking for any tables that are already vacant to serve some customers" << endl;
        //sorting the tablelist so that smaller seat number tables will be checked for vacancy first
        sort(tableList.begin(), tableList.end());
        //after removing customers from the map, its time to check the queue on the customers
        for (int i = 0; i < custList.size(); i++)
        {
            if (!tableList.empty())
            {
                for (int k = 0; k < tableList.size(); k++)
                {
                    cout << "\nChecking whether table #" << tableList.at(k).getTableNum() << " can accomodate the customer" << endl;
                    if (custList.at(i).getSeat() <= tableList.at(k).getSeating())
                    {
                        cout << "\nThe table has " << tableList.at(k).getSeating()
                        << " seats and is able to accomodate customer #"
                        << (i + 1) << ", " << custList.at(i).getName() << " from the list and is transfered into the map" << endl;
                        //if the customer in customer list can be matched with a table
                        //create the pair object and make the customer gone from the deque
                        //the customerTableMap will always be sorted according to the time customers still have
                        custList.at(i).addToTime(clock);
                        customerTableMap.emplace(custList.at(i), pair<Customer, Table>(custList.at(i), tableList.at(k)));
                        custList.erase(custList.begin() + i);
                        tableList.erase(tableList.begin() + k);
                        cout << "Added a customer" << endl;
                        break;
                    }
                }
            }
            else//no more tables and everyone have to wait unless they tapao
            {
                break;
            }
        }
        //get some fresh new customers to torture with bad food
        //serve them with milocola
        int randomNumberOfCustomers = (rand() % tableNum) + 1, customerCounter;
        counter = 0;
        cout << "\nWe found " << randomNumberOfCustomers << " hungry group of zombies at the restaurant door" << endl;
        for (int i = 0; i < randomNumberOfCustomers; i++)
        {
            customerCounter = 0;
            //get more customers
            if (!readFile.eof())
            {
                string name;
                int seat;
                while(customerCounter < 2)
                {
                    switch(customerCounter)
                    {
                        case 0:
                        {
                            getline(readFile, name);
                            break;
                        }
                        case 1:
                        {
                            getline(readFile, fileStr);
                            seat = stoi(fileStr);
                            Customer someNewCustomer = Customer(to_string(counter), name, seat, (rand() % 8) + 1);
                            custList.emplace_back(someNewCustomer);
                            break;
                        }
                    }
                    customerCounter++;
                }
                counter++;
            }
            else
            {
                break;
            }
        }
        if (counter == randomNumberOfCustomers)
        {
            cout << "\nAll the " << randomNumberOfCustomers
            << " group of zombies are on the waiting list so the staffs' brains are spared" << endl;
        }
        else if (counter == 0)
        {
            cout << "\nIts closing time. So we gunned down all the zombies outside so that we can go back early" << endl;
        }
        else
        {
            cout << "\nIts closing time. We can still serve " << counter
            << " group of zombies. So we gunned the rest down and put the those chosen in the waiting list" << endl;
        }
        clock++;
        cout << "\nA time block has passed" << endl;
        cout << "\nOne cycle ended" << endl;
    }
    cout << "Fat Cat restaurant is officially closed for the day. All staff will be distrubuted with guns for safety on their way back" << endl;
    readFile.close();
}
