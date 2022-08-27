#include "../header.h"

#pragma once

class Login
{
    private:
        User user;
    public:
        bool login(char username[], char password[])
        {
            ifstream inFile(USER_FILE_PATH, ios::in | ios::binary);
            if (!inFile)
            {
                return 0;
            }
            while(inFile.read(reinterpret_cast<char *>(&user), sizeof(User)))
            {
                if (strcmp(user.name, username) == 0 && strcmp(user.password, password) == 0)
                {
                    inFile.close();
                    return 1;
                }
            }

            inFile.close();

            return 0;
        }

}; 