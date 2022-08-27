#pragma once

class User
{
    public:
        char name[50];
        char password[50];

        User(){
            strcpy(name, "");
            strcpy(password, "");
        }
};