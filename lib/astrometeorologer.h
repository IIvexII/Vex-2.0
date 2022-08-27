#include "header.h"
#include "weather.h"
#include "cache.h"
#include "auth/auth.h"
#include "history.h"

#pragma once

class Astrometeorologer: public Auth, public HistoryHandler
{
    public:
        void banner();
        void showMenu();
        void setCity();
        void getWeather();
        void showHistory();
        void displayWeather();
    private:
        void showColumnInTable(string, string);
        void error404();
        void error12029();
        void saveCityNameInFile();
        void displayTable();
        int parseFile();
        void capitalize(char*);

        // Attributes
        char city[50];
        Weather weather;
        Cache cache;
};

void Astrometeorologer::showMenu()
{
    int paddingLeft = 60;
    banner();
    cout << endl;
    cout << setw(paddingLeft) << "[L] Login   " << endl;
    cout << setw(paddingLeft) << "[R] Register" << endl;
    cout << setw(paddingLeft) << "[X] Exit    " << endl;
}
/////////////////////////////////
//          banner()
/////////////////////////////////
void Astrometeorologer::banner()
{
    int leftPadding = 4,
        leftMostPadding = 8,
        rightPadding = 4;

    system("CLS");
    cout << setw(leftMostPadding) << "" << "#################################################################################################" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << "   _       _                            _                       _                       " << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << "  /_\\  ___| |_ _ __ ___  _ __ ___   ___| |_ ___  ___  _ __ ___ | | ___   __ _  ___ _ __ " << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << " //_\\\\/ __| __| '__/ _ \\| '_ ` _ \\ / _ \\ __/ _ \\/ _ \\| '__/ _ \\| |/ _ \\ / _` |/ _ \\ '__|" << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << "/  _  \\__ \\ |_| | | (_) | | | | | |  __/ ||  __/ (_) | | | (_) | | (_) | (_| |  __/ |   " << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << "\\_/ \\_/___/\\__|_|  \\___/|_| |_| |_|\\___|\\__\\___|\\___/|_|  \\___/|_|\\___/ \\__, |\\___|_|   " << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#" << setw(leftPadding) << " " << "                                     Made By: Zafeer, Zaheer & Sumama   |___/           " << setw(rightPadding) << "#" << endl;
    cout << setw(leftMostPadding) << "" << "#################################################################################################" << endl;
}

/////////////////////////////////
//          getCity()
/////////////////////////////////
void Astrometeorologer::setCity()
{
    // Used String Constructor to generate a string of repeated backspaces 16 times.
    string backspaces(16, '\b');

    this->banner();
    cout << endl << endl;
    cout << setw(70) << "Search Location: ________________" << backspaces;
    input(city, 100, SIMPLE); 
    capitalize(this->city); 
}

void Astrometeorologer::showHistory()
{
    this->banner();
    HistoryHandler::searchHistoryByUsername(Auth::name);
}

int Astrometeorologer::parseFile()
{
    string firstLine;
    ifstream fin;

    fin.open("storage/info.dat");

    getline(fin, firstLine);

    if (firstLine != "404" && firstLine != "12029")
    {
        weather.city = firstLine;
        getline(fin, weather.country);
        getline(fin, weather.temprature);
        getline(fin, weather.feelsLike);
        getline(fin, weather.description);
        getline(fin, weather.lat);
        getline(fin, weather.lon);
        getline(fin, weather.pressure);
        getline(fin, weather.humidity);
        getline(fin, weather.visibility);

        cache.enter(weather);
        writeHistory(Auth::name, weather.city, weather.temprature);
    }
    else if (firstLine == "404")
    {
        // In case of not found
        weather.city = "";
        return 404;
    }
    else if (firstLine == "12029")
    {
        // In case of Connection error
        weather.city = "";
        return 12029;
    }

    fin.close();
    return 1;   // When successfull
}

void Astrometeorologer::displayWeather()
{
    //  Search in cache
    weather = cache.search(city);

    if (weather.city != "")
    {
        this->displayTable();
    }
    else
    {
        this->getWeather();
        int response = this->parseFile();

        if ( response == 1)
        {
            this->displayTable();
        }
        else if (response == 404)
        {
            this->error404();
        }
        else if (response == 12029)
        {
            this->error12029();
        }
    } 
}

void Astrometeorologer::displayTable()
{
    int leftPadding = 30;
    cout << setw(leftPadding) <<"" << "  __________________________________________________"<< endl;
    cout << setw(leftPadding) <<"" << "/|                                                  |\\"<< endl;
    this->showColumnInTable("Location", weather.city);
    this->showColumnInTable("Country", weather.country);
    this->showColumnInTable("Temprature", weather.temprature);
    this->showColumnInTable("Feels Like", weather.feelsLike);
    this->showColumnInTable("Description", weather.description);
    this->showColumnInTable("Latitude", weather.lat);
    this->showColumnInTable("Longitude", weather.lon);
    this->showColumnInTable("Pressure", weather.pressure);
    this->showColumnInTable("Humidity", weather.humidity);
    this->showColumnInTable("Visibility", weather.visibility);
    cout << setw(leftPadding) <<"" << "\\|__________________________________________________|/"<< endl;
}

void Astrometeorologer::showColumnInTable(string head, string data)
{
    cout << setw(31) << "| " << "|" << left << setw(20) << head << setw(10) << 
            "|" <<  setw(20) << data << setw(10) << "| |" << right << endl;
}

void Astrometeorologer::saveCityNameInFile()
{
    // Open file in write mode.
    ofstream infoFile;
    infoFile.open ("storage/info.dat");
    // Store city name in file.
    infoFile << this->city;
    infoFile.close();
}

void Astrometeorologer::getWeather()
{
    this->saveCityNameInFile();
     
    system("python .\\weatherInfo.py");
}

void Astrometeorologer::error404()
{
    int leftPadding = 70;
    cout << endl;
    cout << setw(leftPadding) << "  _  _    ___  _  _   " << endl;
    cout << setw(leftPadding) << " | || |  / _ \\| || |  " << endl;
    cout << setw(leftPadding) << " | || |_| | | | || |_ " << endl;
    cout << setw(leftPadding) << " |__   _| | | |__   _|" << endl;
    cout << setw(leftPadding) << "    | | | |_| |  | |  " << endl;
    cout << setw(leftPadding) << "    |_|  \\___/   |_|  " << endl << endl;
    cout << setw(leftPadding-5) << "NOT FOUND!" << endl;
}

void Astrometeorologer::capitalize(char str[])
{
    str[0] = toupper(str[0]);
}

void Astrometeorologer::error12029()
{
    int leftPadding = 73;
    cout << endl;
    cout << setw(leftPadding) << " /~~~\\________/~~~\\    " << endl;
    cout << setw(leftPadding) << "(  o  )      (  o  )   " << endl;
    cout << setw(leftPadding) << " \\___/  ++++  \\___/    " << endl;
    cout << setw(leftPadding) << "  | \\          / |     " << endl;
    cout << setw(leftPadding) << "  |   \\o____o/   |     " << endl;
    cout << setw(leftPadding) << "  |%%   #### oooo|     " << endl;
    cout << setw(leftPadding) << "  |______________|     " << endl;

    leftPadding = 86;
    cout << setw(leftPadding) << " _   _         _____      _                       _   " << endl;
    cout << setw(leftPadding) << "| \\ | |       |_   _|    | |                     | |  " << endl;
    cout << setw(leftPadding) << "|  \\| | ___     | | _ __ | |_ ___ _ __ _ __   ___| |_ " << endl;
    cout << setw(leftPadding) << "| . ` |/ _ \\    | || '_ \\| __/ _ \\ '__| '_ \\ / _ \\ __|" << endl;
    cout << setw(leftPadding) << "| |\\  | (_) |  _| || | | | ||  __/ |  | | | |  __/ |_ " << endl;
    cout << setw(leftPadding) << "\\_| \\_/\\___/   \\___/_| |_|\\__\\___|_|  |_| |_|\\___|\\__|" << endl;
                                                      

}