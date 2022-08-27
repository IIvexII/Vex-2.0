#include "login.h"
#include "register.h"

#pragma once

class Auth: public Login, public Register
{
    public:
        bool loginForm();
        bool registrationForm();

    protected:
        char name[50],password[50];
};

////////////////////////////
//    Login in Form
////////////////////////////
bool Auth::loginForm()
{   
    string backspaces16 = string(16, '\b');
    int paddingLeft = 70;

    // Print basic skeleton of login form
    cout << setw(paddingLeft) << "Username: ________________" << endl << endl;
    cout << setw(paddingLeft) << "Password: ________________" << endl << endl;

    cout << setw(paddingLeft-21) << F_YELLOW << B_MAGENTA << " Login " << RESET_COLOR << endl;

    cout << setw(paddingLeft-1) << "\x1B[A\x1B[A\x1B[A\x1B[A\x1B[A";
    // get username
    input(name, 50, SIMPLE);

    cout << endl;
    cout << setw(paddingLeft) << "Password: ________________" << backspaces16;
    
    input(password, 50, PASSWORD);
    cout << endl;
    
    // return true when logged in successfully and false otherwise
    if (login(name, password))
    {
        cout << F_GREEN << setw(paddingLeft) << "Logged in Successfully!   " << RESET_COLOR;
        cout << endl << endl;
        PlaySound(TEXT("sound/success.wav"), NULL, SND_SYNC);
        return true;
    }
    else
    {
        cout << F_RED << setw(paddingLeft) << "Wrong Credentials!        " << RESET_COLOR;
        cout << endl << endl;
        PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
        return false;
    }
}

////////////////////////////
//  Registration in Form
////////////////////////////
bool Auth::registrationForm()
{
    char confirm[50];
    int paddingLeft = 70;
    string escape7 = "\x1B[A\x1B[A\x1B[A\x1B[A\x1B[A\x1B[A\x1B[A";
    string backspaces16 = string(16, '\b');

    cout << endl;
    cout << setw(paddingLeft) << "Username: ________________" << endl << endl;
    cout << setw(paddingLeft) << "Password: ________________" << endl << endl;
    cout << setw(paddingLeft) << "Confirm:  ________________" << endl << endl;
    cout << setw(paddingLeft-10) << F_YELLOW << B_MAGENTA << " Register Now! " << RESET_COLOR << endl;
    cout << setw(paddingLeft) << "                          " << escape7 << backspaces16;

    input(name, 50, SIMPLE); // Take username
    cout << endl;

    cout << setw(paddingLeft) << "Password: ________________" << backspaces16;
    input(password, 50, PASSWORD); // Take Password
    cout << endl;

    cout << setw(paddingLeft) << "Confirm:  ________________" << backspaces16;
    input(confirm, 50, PASSWORD); // Take Password
    cout << endl;
    if (strcmp(password, confirm) == 0)
    {
        switch (createUser(name, password))
        {
            case 1738:
                // Successfull
                cout << F_GREEN << setw(paddingLeft) << "User Created Successfully!" << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/success.wav"), NULL, SND_SYNC);
                return true;
            case 1122:
                // User already exist
                cout << F_RED << setw(paddingLeft) << "Username already exist!   " << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
                return false;
            case 1123:
                // Username format is wrong
                cout << F_RED << setw(paddingLeft+4) << "Username can't contain spaces!" << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
                return false;
            case 2211:
                // Short password
                cout << F_YELLOW << setw(paddingLeft+10) << "Password must be longer then 7 characters!" << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
                return false;
            case 404:
                // Short password
                cout << F_RED << setw(paddingLeft) << "'user.dat' file not found!" << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
                return false;
            case 69:
                // Short password
                cout << F_RED << setw(paddingLeft) << "Username is missing!      " << RESET_COLOR;
                cout << endl << endl;
                PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
                return false;
        }
    }
    else
    {
        cout << F_RED << setw(paddingLeft) << "Paswword don't match!     " << RESET_COLOR;
        cout << endl << endl;
        PlaySound(TEXT("sound/fail.wav"), NULL, SND_SYNC);
        return false;
    }
}
