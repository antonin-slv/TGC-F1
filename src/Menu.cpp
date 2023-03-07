#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

void Menu_Pause()
{   string option;  
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( strcmp(option, "p") != 0);
}

void Menu_Principal()
{   string option;  
    do{
        cout<<"entrer p pour sortir"<<endl;
        cin>>option;
    } while ( strcmp(option, "p") != 0);
}
    