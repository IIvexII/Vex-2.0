#include "header.h"

#pragma once

class History
{
public:
    char username[50];
    char city[50];
    char temprature[50];
};

class HistoryHandler
{
public:
    History history;

    void writeHistory(char *name,string city, string temprature)
    {
        strcpy(history.username, name);
        strcpy(history.city, city.c_str());
        strcpy(history.temprature, temprature.c_str());
        ofstream fileWrite(HISTORY_FILE_PATH, ios::binary | ios::app);
            if(!fileWrite)
                cout<<"\aError file not found"<<endl;
            else
            {
                fileWrite.write((char *)&history , sizeof(history));
                fileWrite.close();
            }
    }

    void searchHistoryByUsername(string username)
    {
        ifstream fileOut(HISTORY_FILE_PATH, ios::binary | ios::in);
        if(!fileOut)
            cout<<"\aError file not found"<<endl;
        else
        {
            bool found=false;
            int leftPadding = 30;

            cout << setw(leftPadding) <<"" << "  __________________________________________________"<< endl;
            cout << setw(leftPadding) <<"" << "/|                                                  |\\"<< endl;

            while(fileOut.read((char *)&history, sizeof(History)))
            {
                if(strcmp(history.username, username.c_str()) == 0)
                {
                    
                    cout << setw(31) << "| " << "|" << left << setw(20) << history.city << setw(10) << 
                        "|" <<  setw(20) << history.temprature << setw(10) << "| |" << right << endl;                   
                    found=true;
                }
            }
            fileOut.close();
            if(found==false)
            {
                cout << setw(31) << "| " << "|" << right << setw(33) << " No history found!" << setw(20) << "| |" << endl;
            }
            cout << setw(leftPadding) <<"" << "\\|__________________________________________________|/"<< endl;
                
        }
    }
    void deleteFullHistory()
    {
        // ifstream fileOut(HISTORY_FILE_PATH,ios::binary | ios::in);
        fstream file("storage/history.dat",ios::binary | ios::out);
        
        if(!file)
        {
            cout<<"\aError file not found."<<endl;
        }
        else
        {
            file.close();
        }
    }
    
    void deleteUserHistory(char *name)
    {
        ifstream fileOut(HISTORY_FILE_PATH, ios::binary | ios::in);
        ofstream fileIn(TMP_FILE_PATH, ios::binary | ios::out);

        if(!fileOut || !fileIn)
        {
            cout<<"\aUnable to open file."<<endl;
        }
        else
        {
            while(fileOut.read((char *)&history, sizeof(History)))
            if(strcmp(history.username,name) != 0)
            {
                fileIn.write((char *)&history, sizeof(History));
            }
            
            fileOut.close();
            fileIn.close();
        }

        remove(HISTORY_FILE_PATH);
        rename(TMP_FILE_PATH , HISTORY_FILE_PATH);
    }

};