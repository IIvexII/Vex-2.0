#include "lib/astrometeorologer.h"
#include "lib/history.h"

int main()
{
    Astrometeorologer astro;
    char choice = '\0'; // Null

    while (choice != 'x' && choice != 'X')
    {

        astro.showMenu();
        choice = getch();

        PlaySound(TEXT("sound/select.wav"), NULL, SND_SYNC);

        if (choice == 'L' || choice == 'l')
        {

            astro.banner();
            cout << endl << endl;
            if (astro.loginForm())
            {
                getch();
                choice = '\0'; // Again Reset the choice variable.
                while (choice != 'l' && choice != 'L')
                {
                    astro.setCity();
                    astro.getWeather();
                    astro.displayWeather();

                    cout << endl;
                    cout << setw(80) << "[L] Logout, [H] View History [Any key] Search weather again." << endl;
                    choice = getch();

                    if (choice == 'H' || choice == 'h')
                    {
                        astro.showHistory();
                        getch();
                    }
                }
            }
            else
            {
                getch();
            }            
        }
        else if (choice == 'R' || choice == 'r')
        {
            astro.banner();

            astro.registrationForm();

            getch();
        }
    }

    return 0;
}