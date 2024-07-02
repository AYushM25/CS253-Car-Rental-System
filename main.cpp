#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include <regex>
#define man_user "manager"
#define man_pwd "cars"

using namespace std;

int customer_id, employee_id, car_id;

class Request
{
public:
    int isEmployee;
    int id;
    int car_id;
    string startDay;
    string endDay;
};

class Car
{
public:
    int id;
    string model;
    string condition;
    int price;
    bool available;
};

class User
{
public:
    string name;
    string username;
    string password;
    int fine;
};

class Customer : public User
{
public:
    int id;
    int customer_record;
};

class Employee : public User
{
public:
    int employee_record;
    int id;
};

class Manager : public User
{
};

class MAIN
{
private:
public:
    MAIN();
    void customer_Login();
    void customer_Register();
    void employee_Login();
    void employee_Register();
    int avg_record();
    void manager_Login();
    void manager_Dashboard();
    void add_Car();
    void update_Car_Manager();
    void updateAvl(int carId);
    void delete_Car();
    void delete_Customer();
    void delete_Employee();
    void viewCarList();
    void addRentRequestCustomer(Customer customer);
    void addRentRequestEmployee(Employee employee);
    void viewCustomerDetails(Customer customer);
    void viewEmployeeDetails(Employee employee);
    void removeRentRequestCustomer(Customer customer);
    void removeRentRequestEmployee(Employee employee);
    void customer_Dashboard(const Customer &c);
    void employee_Dashboard(const Employee &e);
    void end_Program();
    int countRentedCars(int customerId);
    void deleteRequestCustomer(int isCustomer, int id, int cid);
    void deleteRequestEmployee(int isEmployee, int id, int cid);
};

bool isValidDate(const std::string &dateStr)
{
    int day, month, year;
    char delimiter;
    istringstream iss(dateStr);
    iss >> day >> delimiter >> month >> delimiter >> year;
    if (month < 1 || month > 12)
    {
        return false;
    }
    int maxDays;
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            maxDays = 29;
        }
        else
        {
            maxDays = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDays = 30;
    }
    else
    {
        maxDays = 31;
    }
    if (day < 1 || day > maxDays)
    {
        return false;
    }
    return true;
}

bool isValidDateFormat(const string &date)
{
    if (!isValidDate(date))
    {
        return false;
    }
    regex dateRegex("\\b(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}\\b");
    return regex_match(date, dateRegex);
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return -1;
    }
}

void parseDate(const string &date, int &day, int &month, int &year)
{
    istringstream ss(date);
    char delimiter;
    ss >> day >> delimiter >> month >> delimiter >> year;
}

int daysBetweenDates(const string &date1, const string &date2)
{
    int day1, month1, year1;
    int day2, month2, year2;
    parseDate(date1, day1, month1, year1);
    parseDate(date2, day2, month2, year2);
    if (year2 < year1 || (year2 == year1 && month2 < month1) || (year2 == year1 && month2 == month1 && day2 < day1))
    {
        swap(day1, day2);
        swap(month1, month2);
        swap(year1, year2);
    }
    int totalDays1 = day1;
    for (int i = 1; i < month1; ++i)
    {
        totalDays1 += getDaysInMonth(i, year1);
    }
    for (int i = 1; i < year1; ++i)
    {
        totalDays1 += isLeapYear(i) ? 366 : 365;
    }

    int totalDays2 = day2;
    for (int i = 1; i < month2; ++i)
    {
        totalDays2 += getDaysInMonth(i, year2);
    }
    for (int i = 1; i < year2; ++i)
    {
        totalDays2 += isLeapYear(i) ? 366 : 365;
    }
    return totalDays2 - totalDays1;
}

string getTodaysDate()
{
    time_t now = time(nullptr);
    tm *timeinfo = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return string(buffer);
}

string swapDayYear(const string &date)
{
    string swapped = date.substr(6, 4);
    swapped += "/";
    swapped += date.substr(3, 2);
    swapped += "/";
    swapped += date.substr(0, 2);
    return swapped;
}

int compareDates(const string &date1, const string &date2)
{
    string swapped_date1 = swapDayYear(date1);
    string swapped_date2 = swapDayYear(date2);
    return swapped_date1 > swapped_date2;
}

void write_data_Employees(string str, Employee &employee)
{
    ofstream write;
    if (str == "id.txt")
    {
        write.open("temp.txt");
        write << customer_id << endl;
        write << employee_id << endl;
        write << car_id << endl;
        write.close();
        remove("id.txt");
        rename("temp.txt", "id.txt");
    }
    else
    {
        write.open(str, ios::app);
        write << employee.id << "\n";
        write << employee.name << "\n";
        write << employee.username << "\n";
        write << employee.password << "\n";
        write << employee.fine << "\n";
        write << employee.employee_record << "\n";
        write.close();
    }
}

void write_data_Customers(string str, Customer &cust)
{
    ofstream write;
    if (str == "id.txt")
    {
        write.open("temp.txt");
        write << customer_id << endl;
        write << employee_id << endl;
        write << car_id << endl;
        write.close();
        remove("id.txt");
        rename("temp.txt", "id.txt");
    }
    else
    {
        write.open(str, ios::app);
        write << cust.id << "\n";
        write << cust.name << "\n";
        write << cust.username << "\n";
        write << cust.password << "\n";
        write << cust.fine << "\n";
        write << cust.customer_record << "\n";
        write.close();
    }
}

void write_data_request(string str, Request &req)
{
    ofstream write;
    write.open(str, ios::app);
    write << req.isEmployee << " ";
    write << req.id << " ";
    write << req.car_id << endl;
    write << req.startDay << endl;
    write << req.endDay << endl;
    write.close();
}

void write_data_cars(string str, Car car)
{
    ofstream write;
    write.open(str, ios::app);
    write << car.id << endl;
    write << car.model << endl;
    write << car.condition << endl;
    write << car.price << endl;
    write << car.available << endl;
    write.close();
}

void viewRequests(int isEmployee, int id)
{
    ifstream read;
    read.open("requests.txt", ios::app);
    Request req;
    int count = 1;
    while (read >> req.isEmployee)
    {
        read >> req.id;
        read >> req.car_id;
        read.ignore();
        getline(read, req.startDay);
        getline(read, req.endDay);
        if (isEmployee == req.isEmployee && req.id == id)
        {
            cout << "\n"<< count++ << ". Rented Car ID: " << req.car_id << " | Start Date: " << req.startDay << " | End Date: " << req.endDay << endl;
        }
    }
    read.close();
}

void MAIN::deleteRequestCustomer(int isEmployee, int id, int cid)
{
    ifstream read;
    ofstream write;
    int fine = 0;
    string returnDate;
    read.open("requests.txt",ios::app);
    write.open("temp.txt",ios::app);
    Request req;
    int req_found = 0;
    Car car;
    while (read >> req.isEmployee >> req.id >> req.car_id >> ws && getline(read, req.startDay) && getline(read, req.endDay))
    {
        if (isEmployee == req.isEmployee && req.id == id && req.car_id == cid)
        {
            req_found = 1;
            returnDate = req.endDay;
        }
        else
        {
            write << req.isEmployee << " " << req.id << " " << req.car_id << endl
                  << req.startDay << endl
                  << req.endDay << endl;
        }
    }
    read.close();
    write.close();
    if (!req_found)
    {
        cout << "\nInvalid details, Please try again\n";
        remove("temp.txt");
        return;
    }
    else
    {
        cout << "\nEnter Today's Date (DD/MM/YYYY): ";
        string todaysDate;
        cin.ignore();
        while (true)
        {
            getline(cin, todaysDate);
            if (isValidDateFormat(todaysDate))
            {
                break;
            }
            else
            {
                cout << "\nInvalid date format. Please enter the date in the format (DD/MM/YYYY)\n";
                return;
            }
        }

        string expectedStartDate = req.startDay;
        if (compareDates(returnDate, todaysDate))
        {
            cout << "\nSorry, but return can't be made earlier than due dates\n\n";
            return;
        }
        else if (daysBetweenDates(returnDate, todaysDate) == 0)
        {
            fine = 0;
        }
        else
        {
            int rentalDays = daysBetweenDates(returnDate, todaysDate);
            fine = 10000 * rentalDays;
        }

        int pricePerDay = car.price;

        int totalRentalCost = pricePerDay * daysBetweenDates(expectedStartDate, todaysDate);

        int totalAmount = fine + totalRentalCost;

        string returningCondition;
        cout << "\nEnter the condition of returned Car (Perfect / Not Bad / Critical): ";
        getline(cin, returningCondition);

        Customer cust;
        ifstream read;
        read.open("customers.txt", ios::app);
        while (read >> cust.id)
        {
            read.ignore();
            getline(read, cust.name);
            read >> cust.username;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if (cust.id == id)
            {
                cust.fine += fine;
                if (returningCondition == "Perfect")
                {
                    cust.customer_record = min(cust.customer_record + 2, 5);
                }
                else if (returningCondition == "Critical")
                {
                    cust.customer_record = max(cust.customer_record - 1, 0);
                }
            }
            write_data_Customers("temp1.txt", cust);
        }
        read.close();
        remove("customers.txt");
        rename("temp1.txt", "customers.txt");
        remove("requests.txt");
        rename("temp.txt", "requests.txt");
        cout << "\nCar return request Approved\n";
        int id = car.id;
        updateAvl(id);
        ifstream readCars;
        ofstream writeCars;
        readCars.open("cars.txt");
        writeCars.open("temp_cars.txt");
        Car temp_car;
        while (readCars >> temp_car.id >> ws && getline(readCars, temp_car.model) && getline(readCars, temp_car.condition) && readCars >> temp_car.price >> temp_car.available)
        {
            if (temp_car.id == cid)
            {
                temp_car.available = true;
            }
            writeCars << temp_car.id << " " << temp_car.model << endl
                      << temp_car.condition << endl
                      << temp_car.price << endl
                      << temp_car.available << endl;
        }
        readCars.close();
        writeCars.close();

        remove("cars.txt");
        rename("temp_cars.txt", "cars.txt");
        return;
    }
}

void MAIN::deleteRequestEmployee(int isEmployee, int id, int cid)
{
    ifstream read;
    ofstream write;
    int fine = 0;
    string returnDate;
    read.open("requests.txt");
    write.open("temp.txt");
    Request req;
    int req_found = 0;
    Car car;
    while (read >> req.isEmployee >> req.id >> req.car_id >> ws && getline(read, req.startDay) && getline(read, req.endDay))
    {
        if ((isEmployee-1) == req.isEmployee && req.id == id && req.car_id == cid)
        {
            req_found = 1;
            returnDate = req.endDay;
        }
        else
        {
            write << req.isEmployee << " " << req.id << " " << req.car_id << endl
                  << req.startDay << endl
                  << req.endDay << endl;
        }
    }
    read.close();
    write.close();
    if (!req_found)
    {
        cout << "\nInvalid details, Please try again\n";
        remove("temp.txt");
        return;
    }
    else
    {
        cout << "\nEnter Today's Date (DD/MM/YYYY): ";
        string todaysDate;
        cin.ignore();
        while (true)
        {
            getline(cin, todaysDate);
            if (isValidDateFormat(todaysDate))
            {
                break;
            }
            else
            {
                cout << "\nInvalid date format. Please enter the date in the format (DD/MM/YYYY)\n";
                return;
            }
        }

        string expectedStartDate = req.startDay;
        if (compareDates(returnDate, todaysDate))
        {
            cout << "\nSorry, but return can't be made earlier than due dates\n\n";
            return;
        }
        else if (daysBetweenDates(returnDate, todaysDate) == 0)
        {
            fine = 0;
        }
        else
        {
            int rentalDays = daysBetweenDates(returnDate, todaysDate);
            fine = 10000 * rentalDays;
        }

        int pricePerDay = car.price;

        int totalRentalCost = pricePerDay * daysBetweenDates(expectedStartDate, todaysDate);

        int totalAmount = fine + totalRentalCost;

        string returningCondition;
        cout << "\nEnter the condition of returned Car (Perfect / Not Bad / Critical): ";
        getline(cin, returningCondition);

        Employee emp;
        ifstream read;
        read.open("employees.txt", ios::app);
        while (read >> emp.id)
        {
            read.ignore();
            getline(read, emp.name);
            read >> emp.username;
            read >> emp.password;
            read >> emp.fine;
            read >> emp.employee_record;
            if (emp.id == id)
            {
                emp.fine += fine;
                if (returningCondition == "Perfect")
                {
                    emp.employee_record = min(emp.employee_record + 2, 5);
                }
                else if (returningCondition == "Critical")
                {
                    emp.employee_record = max(emp.employee_record - 1, 0);
                }
            }
            write_data_Employees("temp1.txt", emp);
        }
        read.close();
        remove("employees.txt");
        rename("temp1.txt", "employees.txt");
        remove("requests.txt");
        rename("temp.txt", "requests.txt");
        cout << "\nCar return request Approved\n";
        int id = car.id;
        updateAvl(id);
        ifstream readCars;
        ofstream writeCars;
        readCars.open("cars.txt");
        writeCars.open("temp_cars.txt");
        Car temp_car;
        while (readCars >> temp_car.id >> ws && getline(readCars, temp_car.model) && getline(readCars, temp_car.condition) && readCars >> temp_car.price >> temp_car.available)
        {
            if (temp_car.id == cid)
            {
                temp_car.available = true;
            }
            writeCars << temp_car.id << " " << temp_car.model << endl
                      << temp_car.condition << endl
                      << temp_car.price << endl
                      << temp_car.available << endl;
        }
        readCars.close();
        writeCars.close();

        remove("cars.txt");
        rename("temp_cars.txt", "cars.txt");
        return;
    }
}


void updateCustomer(Customer &customer)
{
    ifstream read;
    Customer cust;
    int count = 0;
    read.open("customers.txt", ios::app);
    while (!read.eof() && count < customer_id)
    {
        read >> cust.id;
        read.ignore();
        getline(read, cust.name);
        read >> cust.username;
        read >> cust.password;
        read >> cust.fine;
        read >> cust.customer_record;
        if (cust.id == customer.id)
        {
            write_data_Customers("temp.txt", customer);
        }
        else
        {
            write_data_Customers("temp.txt", cust);
        }
        count++;
    }
    read.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
}

void updateEmployee(Employee &employee)
{
    ifstream read;
    Employee emp;
    int count = 0;
    read.open("employees.txt", ios::app);
    while (read >> emp.id)
    {
        read.ignore();
        getline(read, emp.name);
        read >> emp.username;
        read >> emp.password;
        read >> emp.fine;
        read >> emp.employee_record;
        if (emp.id == employee.id)
        {
            write_data_Employees("temp.txt", employee);
        }
        else
        {
            write_data_Employees("temp.txt", emp);
        }
        count++;
    }
    read.close();
    remove("employees.txt");
    rename("temp.txt", "employees.txt");
}

int MAIN::avg_record()
{
    long long sum = 0;
    int count = 0;
    ifstream read;
    Customer temp_cust;
    read.open("customers.txt", ios::app);
    while (!read.eof() && count < customer_id)
    {
        read >> temp_cust.id;
        read.ignore();
        getline(read, temp_cust.name);
        read >> temp_cust.username;
        read >> temp_cust.password;
        read >> temp_cust.fine;
        read >> temp_cust.customer_record;
        sum += temp_cust.customer_record;
        count++;
    }
    read.close();
    count = 0;
    Employee temp_employee;
    read.open("employees.txt", ios::app);
    while (!read.eof() && count < employee_id)
    {
        read >> temp_employee.id;
        read.ignore();
        getline(read, temp_employee.name);
        read >> temp_employee.username;
        read >> temp_employee.password;
        read >> temp_employee.fine;
        read >> temp_employee.employee_record;
        sum += temp_employee.employee_record;
        count++;
    }
    read.close();
    int ans = (int)(sum) / (customer_id + employee_id);
    return ans;
}

void MAIN::viewCarList()
{
    if (car_id == 0)
    {
        cout << "\nNo cars available at the Moment, EMPTY List\n\n";
        return;
    }
    int count = 0;
    cout << "---------------------------------------------------------------------\n";
    cout << "LIST: ";
    ifstream read;
    Car temp_car;
    read.open("cars.txt");
    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) && read >> temp_car.price >> temp_car.available && count < car_id)
    {
        if (temp_car.available == true)
        {
            cout << "\n\n"
                 << temp_car.id << ". " << temp_car.model << " | " << temp_car.condition << " | [ " << temp_car.price << " ]\n";
        }
        count++;
    }
    read.close();
    cout << "\n";
}

void MAIN::viewCustomerDetails(Customer customer)
{
    ifstream read;
    Customer cust;
    read.open("customers.txt", ios::app);
    while (!read.eof())
    {
        read >> cust.id;
        read.ignore();
        getline(read, cust.name);
        read >> cust.username;
        read >> cust.password;
        read >> cust.fine;
        read >> cust.customer_record;
        if (customer.id == cust.id)
        {
            cout << "\n\n----- " << cust.name << " -----\n";
            cout << "Username: " << cust.username << endl;
            cout << "Password: " << cust.password << endl;
            cout << "Fine: " << cust.fine << endl;
            cout << "Customer Record: " << cust.customer_record << endl;
            viewRequests(0, cust.id);
            break;
        }
    }
    read.close();
    return;
}

int MAIN::countRentedCars(int Id)
{
    ifstream read;
    read.open("requests.txt", ios::app);
    Request req;
    int rentedCarsCount = 0;
    while (read >> req.isEmployee)
    {
        read >> req.id;
        read >> req.car_id;
        read.ignore();
        getline(read, req.startDay);
        getline(read, req.endDay);
        if (req.isEmployee == 0 && req.id == Id)
        {
            rentedCarsCount++;
        }
    }
    read.close();
    return rentedCarsCount;
}

void MAIN::viewEmployeeDetails(Employee employee)
{
    ifstream read;
    Employee emp;
    read.open("employees.txt", ios::app);
    while (!read.eof())
    {
        read >> emp.id;
        read.ignore();
        getline(read, emp.name);
        read >> emp.username;
        read >> emp.password;
        read >> emp.fine;
        read >> emp.employee_record;
        if (employee.id == emp.id)
        {
            cout << "\n\n----- " << emp.name << " -----\n";
            cout << "Username: " << emp.username << endl;
            cout << "Password: " << emp.password << endl;
            cout << "Fine: " << emp.fine << endl;
            cout << "Employee Record: " << emp.employee_record << endl;
            viewRequests(1, emp.id);
            break;
        }
    }
    read.close();
    return;
}

void MAIN::addRentRequestCustomer(Customer customer)
{
    if (car_id == 0)
    {
        cout << "\nNo cars available at the moment. The list is empty.\n\n";
        return;
    }

    cout << "\nChoose one of the following cars: \n";
    viewCarList();
    cout << "Enter: ";

    int index;
    while (true)
    {
        if (cin >> index)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ifstream read;
    Car temp_car;
    int count = 0;
    int car_found = 0;
    int priceOfCar = 0;

    read.open("cars.txt");
    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) && read >> temp_car.price >> temp_car.available)
    {
        if (temp_car.id == index && temp_car.available == true)
        {
            if (customer.customer_record <= 0)
            {
                cout << "\nPoor customer record. Please talk to the manager.\n\n";
                customer_Dashboard(customer);
                return;
            }
            car_found = 1;
            priceOfCar = temp_car.price;
            cout << "\nAre you sure you want to proceed with the rent request (y/n) ?\nEnter: ";
            cout << "\nDetails For The Rental:\n";
            cout << "Model Name: " << temp_car.model << endl
                 << "Car Condition: " << temp_car.condition << "\nCar Rent Price (daily): " << temp_car.price << "\n\nEnter: ";
            break;
        }
        else if (temp_car.id == index)
        {
            cout << "This particular car isn't available at the moment.\n\n";
            read.close();
            customer_Dashboard(customer);
            return;
        }
        count++;
    }

    read.close();

    if (!car_found)
    {
        cout << "\nPlease enter a valid car index as per the list.\n";
        customer_Dashboard(customer);
    }
    else
    {
        char choice;
        do
        {
            cin >> choice;
            if (choice != 'y' && choice != 'n')
            {
                cout << "\nPlease enter a valid reply.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter: ";
            }
            else if (choice == 'y')
            {
                string date_time = getTodaysDate();
                cout << "Rental Start Date: " << date_time << endl;
                string rentalInvalidationTime;
                int isDateEnteredValid;
                cout << "Enter Return Date (DD/MM/YYYY): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, rentalInvalidationTime);
                isDateEnteredValid = isValidDateFormat(rentalInvalidationTime);
                if (isDateEnteredValid != 1)
                {
                    cout << "\nInvalid Date Format.\n";
                    customer_Dashboard(customer);
                }
                cout << "\nCharge Amount per Day: " << priceOfCar << endl;
                ofstream write;
                write.open("requests.txt", ios::app);
                write << "0 " << customer.id << " " << index << endl
                      << date_time << endl
                      << rentalInvalidationTime << endl;
                write.close();
                cout << "\nRENT REQUEST SENT!\n\n";
                int id = temp_car.id;
                updateAvl(id);
                customer.customer_record = (customer.customer_record - 1) < 0 ? 0 : (customer.customer_record - 1);
                updateCustomer(customer);
                customer_Dashboard(customer);
                break;
            }
            else
            {
                cout << "Request Cancelled, Redirecting\n\n";
                customer_Dashboard(customer);
                break;
            }
        } while (true);
    }
}

void MAIN::removeRentRequestCustomer(Customer customer)
{
    int rentedCarsCount = countRentedCars(customer.id);

    if (rentedCarsCount == 0)
    {
        cout << "\nYou have no rented cars.\n";
        customer_Dashboard(customer);
        return;
    }

    viewRequests(0, customer.id);

    int CID;
    cout << "\nEnter the Rented Car ID: ";
    while (true)
    {
        if (cin >> CID)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    deleteRequestCustomer(0, customer.id, CID);
    customer_Dashboard(customer);
}

void MAIN::removeRentRequestEmployee(Employee employee)
{
    int rentedCarsCount = countRentedCars(employee.id);

    if (rentedCarsCount == 0)
    {
        cout << "\nYou have no rented cars.\n";
        employee_Dashboard(employee);
        return;
    }

    viewRequests(1, employee.id);

    cout << "\nEnter the Rented Car ID: ";
    int CID;
    while (true)
    {
        if (cin >> CID)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    deleteRequestEmployee(1, employee.id, CID);
    employee_Dashboard(employee);
}


void MAIN::addRentRequestEmployee(Employee employee)
{
    if (car_id == 0)
    {
        cout << "\nNo cars available at the moment. The list is empty.\n\n";
        return;
    }

    cout << "\nChoose one of the following cars: \n";
    viewCarList();
    cout << "Enter: ";

    int index;
    while (true)
    {
        if (cin >> index)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ifstream read;
    Car temp_car;
    int count = 0;
    int car_found = 0;
    int priceOfCar = 0;

    read.open("cars.txt");
    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) && read >> temp_car.price >> temp_car.available)
    {
        if (temp_car.id == index && temp_car.available == true)
        {
            if (employee.employee_record <= 0)
            {
                cout << "\nPoor employee record. Please talk to the manager.\n\n";
                employee_Dashboard(employee);
                return;
            }
            car_found = 1;
            priceOfCar = temp_car.price;
            cout << "\nAre you sure you want to proceed with the rent request (y/n) ?\nEnter: ";
            cout << "\nDetails For The Rental:\n";
            cout << "Model Name: " << temp_car.model << endl
                 << "Car Condition: " << temp_car.condition << "\nCar Rent Price (daily): " << temp_car.price << "\n\nEnter: ";
            break;
        }
        else if (temp_car.id == index)
        {
            cout << "This particular car isn't available at the moment.\n\n";
            read.close();
            employee_Dashboard(employee);
            return;
        }
        count++;
    }

    read.close();

    if (!car_found)
    {
        cout << "\nPlease enter a valid car index as per the list.\n";
        employee_Dashboard(employee);
    }
    else
    {
        char choice;
        do
        {
            cin >> choice;
            if (choice != 'y' && choice != 'n')
            {
                cout << "\nPlease enter a valid reply.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter: ";
            }
            else if (choice == 'y')
            {
                string date_time = getTodaysDate();
                cout << "Rental Start Date: " << date_time << endl;
                string rentalInvalidationTime;
                int isDateEnteredValid;
                cout << "Enter Return Date (DD/MM/YYYY): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, rentalInvalidationTime);
                isDateEnteredValid = isValidDateFormat(rentalInvalidationTime);
                if (isDateEnteredValid != 1)
                {
                    cout << "\nInvalid Date Format.\n";
                    employee_Dashboard(employee);
                }
                cout << "\nCharge Amount per Day: " << 0.85 * priceOfCar << endl;
                ofstream write;
                write.open("requests.txt", ios::app);
                write << "0 " << employee.id << " " << index << endl
                      << date_time << endl
                      << rentalInvalidationTime << endl;
                write.close();
                cout << "\nRENT REQUEST SENT!\n\n";
                int id = temp_car.id;
                updateAvl(id);
                employee.employee_record = (employee.employee_record - 1) < 0 ? 0 : (employee.employee_record - 1);
                updateEmployee(employee);
                employee_Dashboard(employee);
                break;
            }
            else
            {
                cout << "Request Cancelled, Redirecting\n\n";
                employee_Dashboard(employee);
                break;
            }
        } while (true);
    }
}

Customer getCustomerWithID(int id)
{
    Customer cust;
    ifstream read;
    read.open("customers.txt", ios::app);
    while (!read.eof())
    {
        read >> cust.id;
        read.ignore();
        getline(read, cust.name);
        read >> cust.username;
        read >> cust.password;
        read >> cust.fine;
        read >> cust.customer_record;
        if (id == cust.id)
        {
            viewRequests(0, cust.id);
            return cust;
        }
    }
    read.close();
    cout << "\n Customer Search Error\n\n";
    MAIN();
    return Customer();
}

Employee getEmployeeWithID(int id)
{
    ifstream read;
    Employee emp;
    read.open("employees.txt", ios::app);
    while (read >> emp.id)
    {
        read.ignore();
        getline(read, emp.name);
        read >> emp.username;
        read >> emp.password;
        read >> emp.fine;
        read >> emp.employee_record;
        if (id == emp.id)
        {
            viewRequests(1, emp.id);
            return emp;
        }
    }
    read.close();
    cout << "\n Employee search Error\n\n";
    MAIN();
    return Employee();
}

void MAIN::employee_Dashboard(const Employee &e)
{
    Employee employee = getEmployeeWithID(e.id);
    int choice;
    cout << "\n---------------------------------------------------------------------\n";
    cout << "Option:  ";
    cout << "1. View Available Car List\n";
    cout << "\t 2. Make a rent request\n";
    cout << "\t 3. Make a return request\n";
    cout << "\t 4. View Profile/Status\n";
    cout << "\t 5. Clear Your Dues\n";
    cout << "\t 6. Update Profile\n";
    cout << "\t 7. Logout\n";
    while (true)
    {
        cout << "Enter:   ";
        if (cin >> choice)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    Employee emp;
    switch (choice)
    {
    case 1:
    {
        viewCarList();
        employee_Dashboard(employee);
        break;
    }
    case 2:
        addRentRequestEmployee(employee);
        employee_Dashboard(employee);
        break;
    case 3:
        removeRentRequestEmployee(employee);
        break;
    case 4:
        viewEmployeeDetails(employee);
        employee_Dashboard(employee);
        break;
    case 5:
        emp = employee;
        emp.fine = 0;
        updateEmployee(emp);
        cout << "\nAll Dues Cleared\n\n";
        employee_Dashboard(emp);
        break;
    case 6:
    {
        int choice1;
        cout << "What field will you like to update?\n";
        cout << "\nOptions:\n\t1. Name\n\t2. Username\n\t3. Password\nEnter: ";

        while (true)
        {
            if (cin >> choice1)
            {
                break;
            }
            else
            {
                cout << "\nInvalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        char c;
        string temp;
        switch (choice1)
        {
        case 1:
            cout << "\nEnter a New Name: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << employee.name << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                employee.name = temp;
                updateEmployee(employee);
                cout << "Updated Successfully!\n";
                employee_Dashboard(employee);
            }
            else
            {
                cout << "\nUpdate Cancelled\n";
                employee_Dashboard(employee);
                return;
            }
            break;
        case 2:
            cout << "\nEnter a New Username: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << employee.username << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                employee.username = temp;
                updateEmployee(employee);
                cout << "Updated Successfully!\n";
                employee_Dashboard(employee);
            }
            else
            {
                cout << "\nUpdate Cancelled\n\n";
                employee_Dashboard(employee);
                return;
            }
            break;
        case 3:
            cout << "\nEnter a New Password: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << employee.password << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                employee.password = temp;
                updateEmployee(employee);
                cout << "Updated Successfully!\n";
                employee_Dashboard(employee);
            }
            else
            {
                cout << "\nUpdate Cancelled\n\n";
                employee_Dashboard(employee);
                return;
            }
            break;
        default:
            cout << "Please choose one of the above choices\n";
            employee_Dashboard(employee);
            return;
        }
        break;
    }

    case 7:
        MAIN();
        break;
    default:
    {
        cout << "\nInvalid Input \n\n";
        employee_Dashboard(employee);
        break;
    }
    }
}

void MAIN::customer_Dashboard(const Customer &c)
{
    Customer customer = getCustomerWithID(c.id);
    int choice;
    cout << "---------------------------------------------------------------------\n";
    cout << "Option:  ";
    cout << "1. View Available Car List\n";
    cout << "\t 2. Make a rent request\n";
    cout << "\t 3. Make a return request\n";
    cout << "\t 4. View Profile/Status\n";
    cout << "\t 5. Clear Your Dues\n";
    cout << "\t 6. Update Profile\n";
    cout << "\t 7. Logout\n";
    while (true)
    {
        cout << "Enter:   ";
        if (cin >> choice)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    Customer cust;
    switch (choice)
    {
    case 1:
    {
        viewCarList();
        customer_Dashboard(customer);
        break;
    }
    case 2:
        addRentRequestCustomer(customer);
        customer_Dashboard(customer);
        break;
    case 3:
        removeRentRequestCustomer(customer);
        break;
    case 4:
        viewCustomerDetails(customer);
        customer_Dashboard(customer);
        break;
    case 5:
        cust = customer;
        cust.fine = 0;
        updateCustomer(cust);
        cout << "\nAll Dues Cleared\n\n";
        customer_Dashboard(cust);
        break;
    case 6:
    {
        int choice1;
        cout << "What field will you like to update?\n";
        cout << "\nOptions:\n\t1. Name\n\t2. Username\n\t3. Password\nEnter: ";

        while (true)
        {
            if (cin >> choice1)
            {
                break;
            }
            else
            {
                cout << "\nInvalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        char c;
        string temp;
        switch (choice1)
        {
        case 1:
            cout << "\nEnter a New Name: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << customer.name << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                customer.name = temp;
                updateCustomer(customer);
                cout << "Updated Successfully!\n";
                customer_Dashboard(customer);
            }
            else
            {
                cout << "\nUpdate Cancelled\n";
                customer_Dashboard(customer);
                return;
            }
            break;
        case 2:
            cout << "\nEnter a New Username: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << customer.username << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                customer.username = temp;
                updateCustomer(customer);
                cout << "Updated Successfully!\n";
                customer_Dashboard(customer);
            }
            else
            {
                cout << "\nUpdate Cancelled\n\n";
                customer_Dashboard(customer);
                return;
            }
            break;
        case 3:
            cout << "\nEnter a New Password: ";
            cin.ignore();
            getline(cin, temp);
            cout << "Are you sure you want the following update ?(y/n):\n " << customer.password << " >> " << temp << "\nEnter: ";
            cin >> c;
            if (c == 'y')
            {
                customer.password = temp;
                updateCustomer(customer);
                cout << "Updated Successfully!\n";
                customer_Dashboard(customer);
            }
            else
            {
                cout << "\nUpdate Cancelled\n\n";
                customer_Dashboard(customer);
                return;
            }
            break;
        default:
            cout << "Please choose one of the above choices\n";
            customer_Dashboard(customer);
            return;
        }
        break;
    }

    case 7:
        MAIN();
        break;
    default:
    {
        cout << "\nInvalid Input \n\n";
        customer_Dashboard(customer);
        break;
    }
    }
}

MAIN::MAIN()
{
    ifstream read;
    read.open("id.txt");
    if (!read.fail())
    {
        read >> customer_id;
        read >> employee_id;
        read >> car_id;
    }
    else
    {
        customer_id = 0;
        employee_id = 0;
        car_id = 0;
    }
    read.close();

    int Choice;
    cout << "---------------------------------------------------------------------\n";
    cout << "\n\t         <> Welcome to A-Star Car Rentals <> \t\n\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Option: ";
    cout << " 1. Customer Login\n";
    cout << "\t 2. Employee Login\n";
    cout << "\t 3. Manager Login\n";
    cout << "\t 4. New users register here\n";
    cout << "\t 5. Exit the Program\n";
    cout << "Enter:   ";

    while (!(cin >> Choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input. \nPlease enter a valid number: ";
    }

    switch (Choice)
    {
    case 1:
        customer_Login();
        break;
    case 2:
        employee_Login();
        break;
    case 3:
        manager_Login();
        break;
    case 4:
        char c;
        do
        {
            cout << "Are you a customer? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                customer_Register();
                break;
            }
            else if (c == 'n' || c == 'N')
            {
                employee_Register();
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 'y' or 'n'.\n";
            }
        } while (true);
    case 5:
        end_Program();
        break;
    default:
        cout << "Invalid input.\nPlease enter a valid number.\n";
        MAIN();
    }
}

void MAIN::customer_Register()
{
    Customer new_cust;
    cout << "Enter your name: ";
    string temporary;
    cin.ignore();
    getline(cin, temporary);
    new_cust.name = temporary;

    cout << "Enter your username: ";
    cin >> new_cust.username;

    string username = new_cust.username;
    ifstream read;
    read.open("customers.txt", ios::app);

    while (!read.eof())
    {
        Customer cust;
        read >> cust.id;
        read.ignore();
        getline(read, cust.name);
        read >> cust.username;
        read >> cust.password;
        read >> cust.fine;
        read >> cust.customer_record;

        if (cust.username == username)
        {
            cout << "\nUser with the same username already Exists, Please Login\n";
            customer_Login();
            return;
        }
    }

    read.close();

    cout << "Enter your password: ";
    cin >> new_cust.password;
    new_cust.fine = 0;
    new_cust.customer_record = 3;
    customer_id++;
    new_cust.id = customer_id;

    write_data_Customers("customers.txt", new_cust);
    write_data_Customers("id.txt", new_cust);

    cout << "\nCustomer Registration Successful\n"
         << endl;
    customer_Login();
}

void MAIN::customer_Login()
{
    cout << "---------------------------------------------------------------------\n";
    cout << "Enter your Username: ";
    string username;
    cin >> username;
    cout << "Enter your Password: ";
    string password, name;
    cin >> password;
    int found_customer = 0;
    Customer cust_found;
    ifstream read;
    read.open("customers.txt", ios::app);
    while (!read.eof())
    {
        Customer cust;
        read >> cust.id;
        read.ignore();
        getline(read, cust.name);
        read >> cust.username;
        read >> cust.password;
        read >> cust.fine;
        read >> cust.customer_record;
        if (cust.username == username && cust.password == password)
        {
            cout << "\nWelcome " << cust.name << "!\n";
            found_customer = 1;
            cust_found = cust;
            break;
        }
        else if (cust.username == username)
        {
            cout << "\nWrong Username Or Password\n";
            found_customer = 2;
            break;
        }
    }
    read.close();
    if (found_customer == 1)
    {
        customer_Dashboard(cust_found);
    }
    else if (found_customer == 2)
    {
        customer_Login();
    }
    else if (found_customer == 0)
    {
        cout << "\nUsername not found, please register yourself\n";
        MAIN();
    }
    else
    {
        MAIN();
    }
}

void MAIN::employee_Register()
{
    Employee new_employee;
    cout << "Enter your name: ";
    string temporary;
    cin.ignore();
    getline(cin, temporary);
    new_employee.name = temporary;
    cout << "Enter your username: ";
    cin >> new_employee.username;
    string username = new_employee.username;
    ifstream read;
    read.open("employees.txt", ios::app);
    while (!read.eof())
    {
        Employee employee;
        read >> employee.id;
        read.ignore();
        getline(read, employee.name);
        read >> employee.username;
        read >> employee.password;
        read >> employee.fine;
        read >> employee.employee_record;
        if (employee.username == username)
        {
            cout << "\nUser with same username ID already Exists, Please Login \n";
            employee_Login();
            break;
        }
    }
    read.close();
    cout << "Enter your password: ";
    cin >> new_employee.password;
    new_employee.fine = 0;
    new_employee.employee_record = (avg_record() > 3) ? avg_record() : 3;
    employee_id++;
    new_employee.id = employee_id;
    write_data_Employees("employees.txt", new_employee);
    write_data_Employees("id.txt", new_employee);
    cout << "\nEmployee Registeration Successful\n"<< endl;
    employee_Login();
}

void MAIN::employee_Login()
{
    cout << "---------------------------------------------------------------------\n";
    cout << "Enter your Username: ";
    string username;
    cin >> username;
    cout << "Enter your Password: ";
    string password, name;
    cin >> password;
    int found_employee = 0;
    Employee employee_found;
    ifstream read;
    read.open("employees.txt", ios::app);
    while (!read.eof())
    {
        Employee employee;
        read >> employee.id;
        read.ignore();
        getline(read, employee.name);
        read >> employee.username;
        read >> employee.password;
        read >> employee.fine;
        read >> employee.employee_record;
        if (employee.username == username && employee.password == password)
        {
            cout << "\n Welcome " << employee.name << "!";
            found_employee = 1;
            employee_found = employee;
            break;
        }
        else if (employee.username == username)
        {
            cout << "\n Wrong username Or Password\n";
            found_employee = 2;
            break;
        }
    }
    read.close();
    if (found_employee == 1)
    {
        employee_Dashboard(employee_found);
    }
    else if (found_employee == 2)
    {
        employee_Login();
    }
    else if (found_employee == 0)
    {
        cout << "\n Username not found, please register yourself.\n";
        MAIN();
    }
    else
    {
        MAIN();
    }
}

void MAIN::manager_Login()
{
    cout << "\nEnter your Username : ";
    string username, password;
    cin >> username;
    cout << "Enter your Password : ";
    cin >> password;
    Manager manager;
    if (username == man_user && password == man_pwd)
    {
        cout << "\n\nWelcome Manager!\n";
        manager_Dashboard();
    }
    else
    {
        cout << "\nWrong Username/Password, try again\n";
        manager_Login();
    }
}

void MAIN::manager_Dashboard()
{
    int choice;
    bool anyRequests = false;
    cout << "---------------------------------------------------------------------\n";
    cout << "Option: 1. Add a Car\n";
    cout << "\t2. Update a Car\n";
    cout << "\t3. Delete a Car\n";
    cout << "\t4. View Available Car List\n";
    cout << "\t5. View Customer Details\n";
    cout << "\t6. View Employee Details\n";
    cout << "\t7. View All Requests\n";
    cout << "\t8. Delete Customer\n";
    cout << "\t9. Delete Employee\n";
    cout << "\t10. Update Customer Details\n";
    cout << "\t11. Update Employee Details\n";
    cout << "\t12. Logout.\n";
    while (true)
    {
        cout << "Enter: ";
        if (cin >> choice)
            break;
        else
        {
            cout << "\nInvalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    string name;
    ifstream read;
    Customer cust;
    int found = 0;
    Employee emp;
    switch (choice)
    {
    case 1:
        add_Car();
        break;
    case 2:
        update_Car_Manager();
        break;
    case 3:
        delete_Car();
        break;
    case 4:
        viewCarList();
        manager_Dashboard();
        break;
    case 5:
        cout << "Enter the Customer Name you would want details of: ";
        cin.ignore();
        getline(cin, name);
        read.open("customers.txt", ios::app);
        while (read >> cust.id)
        {
            read.ignore();
            getline(read, cust.name);
            read >> cust.username;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if (name == cust.name)
            {
                found = 1;
                viewCustomerDetails(cust);
                break;
            }
        }
        read.close();
        if (!found)
        {
            cout << "\nNo customer with this Name exists\n\n";
        }
        manager_Dashboard();
        break;
    case 6:
        cout << "Enter the employee Name you would want details of:\n";
        cin.ignore();
        getline(cin, name);
        read.open("employees.txt", ios::app);
        while (read >> emp.id)
        {
            read.ignore();
            getline(read, emp.name);
            read >> emp.username;
            read >> emp.password;
            read >> emp.fine;
            read >> emp.employee_record;
            if (name == emp.name)
            {
                found = 1;
                viewEmployeeDetails(emp);
                break;
            }
        }
        read.close();
        if (!found)
        {
            cout << "\nNo employee with this Name exists\n\n";
        }
        manager_Dashboard();
        break;
    case 7:
        for (int i = 1; i <= customer_id; i++)
        {
            viewRequests(0, i);
            if (found)
            {
                anyRequests = true;
                found = false;
            }
        }
        for (int i = 1; i <= employee_id; i++)
        {
            viewRequests(1, i);
            if (found)
            {
                anyRequests = true;
                found = false;
            }
        }

        if (!anyRequests)
        {
            cout << "\nNo requests found.\n";
        }
        cout << "\n";
        manager_Dashboard();
        break;

    case 8:
        delete_Customer();
        break;
    case 9:
        delete_Employee();
        break;
    case 10:
    {
        cout << "\nEnter Customer Name for the Update: \n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        int name_found = 0, count = 0;
        Customer temp_cust;
        read.open("customers.txt", ios::app);
        while (!read.eof() && count < (car_id))
        {
            read >> temp_cust.id;
            read.ignore();
            getline(read, temp_cust.name);
            read >> temp_cust.username;
            read >> temp_cust.password;
            read >> temp_cust.fine;
            read >> temp_cust.customer_record;
            if (temp_cust.name != name)
            {
                write_data_Customers("temp.txt", temp_cust);
            }
            else
            {
                name_found = 1;
                int choice1;
                cout << "\nWhat field will you like to update ?\n";
                cout << "\nOption: 1. Name\n\t2. Username\n\t3. Password\n\t4. Fine\n\t5. Customer Record\nEnter: ";
                cin >> choice1;
                string temp;
                switch (choice1)
                {
                case 1:
                    cout << "\nCurrent Name: " << temp_cust.name << endl;
                    cout << "\nEnter New Name: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_cust.name = temp;
                    break;
                case 2:
                    cout << "\nCurrent Username: " << temp_cust.username << endl;
                    cout << "\nEnter New Username: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_cust.username = temp;
                    break;
                case 3:
                    cout << "\nCurrent Password: " << temp_cust.password << endl;
                    cout << "\nEnter New Password: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_cust.password = temp;
                    break;
                case 4:
                    cout << "\nCurrent Fine: " << temp_cust.fine << endl;
                    cout << "\nEnter New Fine: ";
                    int newFine;
                    cin >> newFine;
                    temp_cust.fine = newFine;
                    break;
                case 5:
                    cout << "\nCurrent Customer Record: " << temp_cust.customer_record << endl;
                    cout << "\nEnter New Customer Record: ";
                    int newCR;
                    cin >> newCR;
                    temp_cust.customer_record = newCR;
                    break;
                default:
                    cout << "Please choose one of the above choices\n";
                    manager_Dashboard();
                    return;
                }
                write_data_Customers("temp.txt", temp_cust);
            }
            count++;
        }
        read.close();
        if (!name_found)
        {
            cout << "\nCustomer with Name doesn't exist.\n";
            remove("temp.txt");
            manager_Dashboard();
        }
        else
        {
            remove("customers.txt");
            rename("temp.txt", "customers.txt");
            cout << "\nThe Update Was Successful\n";
            manager_Dashboard();
        }
        break;
    }
    case 11:
    {
        cout << "\nEnter Employee Name for the Update: \n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        int name_found = 0, count = 0;
        Employee temp_emp;
        read.open("employees.txt", ios::app);
        while (!read.eof() && count < (car_id))
        {
            read >> temp_emp.id;
            read.ignore();
            getline(read, temp_emp.name);
            read >> temp_emp.username;
            read >> temp_emp.password;
            read >> temp_emp.fine;
            read >> temp_emp.employee_record;
            if (temp_emp.name != name)
            {
                write_data_Employees("temp.txt", temp_emp);
            }
            else
            {
                name_found = 1;
                int choice1;
                cout << "What field will you like to update ?\n";
                cout << "\nOption: 1. Name\n\t2. Username\n\t3. Password\n\t4. Fine\n\t5. Customer Record\nEnter: ";
                cin >> choice1;
                string temp;
                switch (choice1)
                {
                case 1:
                    cout << "\nCurrent Name: " << temp_emp.name << endl;
                    cout << "\nEnter New Name: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_emp.name = temp;
                    break;
                case 2:
                    cout << "\nCurrent Username: " << temp_emp.username << endl;
                    cout << "\nEnter New Username: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_emp.username = temp;
                    break;
                case 3:
                    cout << "\nCurrent Password: " << temp_emp.password << endl;
                    cout << "\nEnter New Password: ";
                    cin.ignore();
                    getline(cin, temp);
                    temp_emp.password = temp;
                    break;
                case 4:
                    cout << "\nCurrent Fine: " << temp_emp.fine << endl;
                    cout << "\nEnter New Fine: ";
                    int newFine;
                    cin >> newFine;
                    temp_emp.fine = newFine;
                    break;
                case 5:
                    cout << "\nCurrent Employee Record: " << temp_emp.employee_record << endl;
                    cout << "\nEnter New Employee Record: ";
                    int newCR;
                    cin >> newCR;
                    temp_emp.employee_record = newCR;
                    break;
                default:
                    cout << "Please choose one of the above choices\n";
                    manager_Dashboard();
                    return;
                }
                write_data_Employees("temp.txt", temp_emp);
            }
            count++;
        }
        read.close();
        if (!name_found)
        {
            cout << "\nEmployee with Name doesn't exist.\n";
            remove("temp.txt");
            manager_Dashboard();
        }
        else
        {
            remove("employees.txt");
            rename("temp.txt", "employees.txt");
            cout << "\nThe Update Was Successful\n";
            manager_Dashboard();
        }
        break;
    }
    case 12:
        MAIN();
        break;
    default:
        cout << "\n-->> Invalid Input \n\n";
        manager_Dashboard();
        break;
    }
}

void MAIN::add_Car()
{
    ifstream read;
    read.open("id.txt");
    if (!read.fail())
    {
        read >> customer_id;
        read >> employee_id;
        read >> car_id;
    }
    else
    {
        customer_id = 0;
        employee_id = 0;
        car_id = 0;
    }
    read.close();
    Car car;
    car.id = ++car_id;
    car.condition = "Brand New";
    car.available = true;
    cout << "\nAdd new car details-> \n";
    cout << "\nName of the Model: ";
    cin.ignore();
    getline(cin, car.model);
    int same_model_found = 0;
    read.open("cars.txt", ios::app);
    while (!read.eof())
    {
        Car temp_car;
        read >> temp_car.id;
        read.ignore();
        getline(read, temp_car.model);
        getline(read, temp_car.condition);
        read >> temp_car.price;
        read >> temp_car.available;
        if (temp_car.model == car.model)
        {
            cout << "\nCar with same Model Name, already exists\n";
            same_model_found = 1;
            break;
        }
    }
    read.close();
    if (same_model_found)
    {
        add_Car();
    }
    else
    {
        cout << "Rent Price: ";
        cin >> car.price;
        write_data_cars("cars.txt", car);
        Customer c;
        write_data_Customers("id.txt", c);
        cout << "\nCar Added To Collection Successfully\n";
        manager_Dashboard();
    }
}

void MAIN::delete_Car()
{
    ifstream read;
    car_id--;
    Customer c;
    write_data_Customers("id.txt", c);
    string model;
    cout << "\nEnter Model Name for Deletion: ";
    cin.ignore();
    getline(cin, model);
    int model_found = 0, count = 0;
    Car temp_car;
    read.open("cars.txt");
    ofstream temp("temp.txt");
    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) && read >> temp_car.price >> temp_car.available)
    {
        if (temp_car.model != model)
        {
            if (model_found)
                temp_car.id--;
            temp << temp_car.id << "\n"
                 << temp_car.model << "\n"
                 << temp_car.condition << "\n"
                 << temp_car.price << " " << temp_car.available << "\n";
        }
        else
        {
            model_found = 1;
        }
        count++;
    }
    read.close();
    temp.close();
    if (!model_found)
    {
        cout << "\n--> Model Name doesn't exist.\n";
        remove("temp.txt");
        manager_Dashboard();
    }
    else
    {
        remove("cars.txt");
        rename("temp.txt", "cars.txt");
        cout << "\nDeletion was successful\n";
        manager_Dashboard();
    }
}

void MAIN::updateAvl(int car_id)
{
    ifstream read;
    int car_found = 0;
    Car temp_car;
    read.open("cars.txt");

    ofstream temp_file("temp.txt");

    if (!temp_file.is_open() || !read.is_open())
    {
        cout << "Error: File could not be opened.";
        return;
    }

    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) >> temp_car.price >> temp_car.available)
    {
        if (temp_car.id != car_id)
        {
            write_data_cars("temp.txt", temp_car);
        }
        else
        {
            car_found = 1;
            temp_car.available = !temp_car.available;
            write_data_cars("temp.txt", temp_car);
        }
    }
    read.close();
    temp_file.close();

    if (!car_found)
    {
        remove("temp.txt");
        return;
    }
    else
    {
        remove("cars.txt");
        rename("temp.txt", "cars.txt");
        return;
    }
}

void MAIN::update_Car_Manager()
{
    ifstream read;
    string model;
    cout << "\nEnter Model for the Car you want to update: ";
    cin.ignore();
    getline(cin, model);

    int model_found = 0;
    Car temp_car;
    read.open("cars.txt");

    ofstream temp_file("temp.txt");

    if (!temp_file.is_open() || !read.is_open())
    {
        cout << "Error: File could not be opened.";
        return;
    }

    while (read >> temp_car.id >> ws && getline(read, temp_car.model) && getline(read, temp_car.condition) >> temp_car.price >> temp_car.available)
    {
        if (temp_car.model != model)
        {
            write_data_cars("temp.txt", temp_car);
        }
        else
        {
            model_found = 1;
            int choice1;
            cout << "\nWhat field will you like to update?\n";
            cout << "Enter:  1. Model Name\n\t2. Condition\n\t3. Price\n\t4. Availability\nOption: ";
            cin >> choice1;
            string temp;
            switch (choice1)
            {
            case 1:
                cout << "\nCurrent Model Name: " << temp_car.model << endl;
                cout << "Enter New Model Name: ";
                cin.ignore();
                getline(cin, temp);
                temp_car.model = temp;
                break;
            case 2:
                cout << "\nCurrent Condition: " << temp_car.condition << endl;
                cout << "Enter New Condition (Perfect / Not Bad / Critical): ";
                cin.ignore();
                getline(cin, temp);
                temp_car.condition = temp;
                break;
            case 3:
                cout << "\nCurrent Price: " << temp_car.price << endl;
                cout << "Enter New Price: ";
                cin >> temp_car.price;
                break;
            case 4:
                cout << "\nChanging availability: " << temp_car.available << " >> " << !temp_car.available << endl;
                temp_car.available = !temp_car.available;
                break;
            default:
                cout << "Please choose one of the above choices\n";
                continue;
            }
            write_data_cars("temp.txt", temp_car);
        }
    }
    read.close();
    temp_file.close();

    if (!model_found)
    {
        cout << "\nModel Name doesn't exist.\n";
        remove("temp.txt");
        manager_Dashboard();
    }
    else
    {
        remove("cars.txt");
        rename("temp.txt", "cars.txt");
        cout << "\nThe Update Was Successful!\n";
        manager_Dashboard();
    }
}

void MAIN::delete_Customer()
{
    ifstream read;
    customer_id--;
    Customer c;
    write_data_Customers("id.txt", c);
    string name;
    cout << "\nName of Customer to be deleted: ";
    cin.ignore();
    getline(cin, name);
    int name_found = 0, count = 0;
    Customer temp_cust;
    read.open("customers.txt", ios::app);
    while (!read.eof() && count < (customer_id + 1))
    {
        read >> temp_cust.id;
        read.ignore();
        getline(read, temp_cust.name);
        read >> temp_cust.username;
        read >> temp_cust.password;
        read >> temp_cust.fine;
        read >> temp_cust.customer_record;
        if (temp_cust.name != name)
        {
            if (name_found)
            {
                temp_cust.id--;
            }
            write_data_Customers("temp.txt", temp_cust);
        }
        else
        {
            name_found = 1;
        }
        count++;
    }
    read.close();
    if (!name_found)
    {
        cout << "\nCustomer with this Name doesn't exist.\n\n";
        remove("temp.txt");
        manager_Dashboard();
    }
    else
    {
        remove("customers.txt");
        rename("temp.txt", "customers.txt");
        cout << "\nDeletion was successful\n";
        manager_Dashboard();
    }
}

void MAIN::delete_Employee()
{
    ifstream read;
    employee_id--;
    Employee e;
    write_data_Employees("id.txt", e);
    string name;
    cout << "\nName of Employee to be deleted: ";
    cin.ignore();
    getline(cin, name);
    int name_found = 0, count = 0;
    Employee temp_emp;
    read.open("employees.txt", ios::app);
    while (!read.eof() && count < (employee_id + 1))
    {
        read >> temp_emp.id;
        read.ignore();
        getline(read, temp_emp.name);
        read >> temp_emp.username;
        read >> temp_emp.password;
        read >> temp_emp.fine;
        read >> temp_emp.employee_record;
        if (temp_emp.name != name)
        {
            if (name_found)
            {
                temp_emp.id--;
            }
            write_data_Employees("temp.txt", temp_emp);
        }
        else
        {
            name_found = 1;
        }
        count++;
    }
    read.close();
    if (!name_found)
    {
        cout << "\nEmployee with this Name doesn't exist.\n\n";
        remove("temp.txt");
        manager_Dashboard();
    }
    else
    {
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        cout << "\nDeletion was successful\n";
        manager_Dashboard();
    }
}

void MAIN::end_Program()
{
    cout << "\nExiting the program...\n";
    exit(0);
}

int main()
{
    MAIN BEGIN;
    return 0;
}
