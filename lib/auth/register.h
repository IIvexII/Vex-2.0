#include "../header.h"

#pragma once

class Register
{
    private:
        User user;
    public:
        int createUser(char *username, char *password)
        {
            int validator = validate(username, password);

            // if successfull
            if (validator == 1738)
            {
                // Writing to file
                ofstream outFile(USER_FILE_PATH, ios::app | ios::binary);

                if (!outFile)
                {
                    return 404;
                }
                strcpy(user.name, username);
                strcpy(user.password, password);

                outFile.write(reinterpret_cast<char *>(&user), sizeof(User));

                outFile.close();
                
            }
            return validator;
        }

        // Validate if the entered information is correct
        int validate(char *username, char *password)
        {
            ////////////////////////
            // Error/return Codes
            ////////////////////////
            // 404  - file not found.
            // 1738 - valid
            // 1122 - username exist already
            // 1123 - username format is wrong
            // 2211 - Short password (less then 7)
            // 69   - username is missing. 

            // Check if username already registered.
            // Read from file
            ifstream inFile(USER_FILE_PATH, ios::binary); 

            if (!inFile)
            {
                return 404;
            }
            while (inFile.read((char *)&user, sizeof(User)))
            {
                if (strcmp(user.name, username) == 0)
                {
                    inFile.close();
                    return 1122;
                }
            }
            inFile.close();

            // Validating username for correct username
            for (int i = 0, length = strlen(username); i < length; i++)
            {
                if (username[i] == ' ')
                {
                    return 1123;
                }
            }

            // check the password length
            if (strlen(password) < 7)
            {
                return 2211;
            }

            if (strlen(username) == 0)
            {
                return 69;
            }
            // if information is valid
            return 1738;
        }
        
};