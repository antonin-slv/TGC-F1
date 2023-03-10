#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

bool Menu_Pause(void)
{   string option;  
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( option != "p");
    return 1;
};

bool Menu_Principal(void)
{   string option;  
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( option != "p");
    return 1;
}
    