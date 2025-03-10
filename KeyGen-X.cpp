#include <iostream>
#include <random>
#include <string>
#include <cstdlib>  

using namespace std;


// Defining some usefule colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define GOLD "\033[38;5;220m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

//============== Function =================

string passgenrator(int length)
{
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";
    
    random_device rd;
    mt19937 genrator(rd());
    uniform_int_distribution<int> distribution(0,characters.length()-1);

    string password="";
    for(int i=0;i<length;i++)
    {
        password += characters[distribution(genrator)];
    }
    
    return password;



}

//============== Main Part ==================

int main(){

system("chcp 65001 >nul");  // This will enable UTF-8 without showing output so tha banner can correctly show

cout<<"\n";

cout << GREEN
         << "       ██╗  ██╗███████╗██╗   ██╗ ██████╗ ███████╗███╗   ██╗    ██╗  ██╗\n"
         << "       ██║ ██╔╝██╔╝╝╝╝╝╚██╗ ██╔╝██╔╝╝╝╝╝ ██╔╝╝╝╝╝████╗  ██║    ╚██╗██╔╝\n"
         << "       █████╔╝ █████╗   ╚████╔╝ ██║  ███╗█████╗  ██╔██╗ ██║     ╚███╔╝ \n"
         << "       ██╔╝██╗ ██╔╝╝╝    ╚██╔╝  ██║   ██║██╔╝╝╝  ██║╚██╗██║     ██╔██╗ \n"
         << "       ██║  ██╗███████╗   ██║   ╚██████╔╝███████╗██║ ╚████║    ██╔╝ ██╗\n"
         << "       ╚╝╝  ╚╝╝╚╝╝╝╝╝╝╝   ╚╝╝    ╚╝╝╝╝╝╝ ╚╝╝╝╝╝╝╝╚╝╝  ╚╝╝╝╝    ╚╝╝  ╚╝╝\n"
<< RESET << endl;

cout << "\033[32m" << string(75, '=') << "\033[0m" << endl;

cout << "\t\033[38;5;220m~~~~~  Developed by Aspiring Pentester Mr. Izaz   ~~~~~ \033[0m "<<endl;

cout <<"\t\033[35m~~~~~  Follow Here: GitHub.com/mizazhaider-ceh  ~~~~~\033[0m"<<endl;



cout << "\033[32m" << string(75, '=') << "\033[0m" << endl;

int length;

cout <<GOLD<<"\n~~ Enter your Desried length of password : "<<RESET;

cin >>length;

//====== using the funtion =====


string password = passgenrator(length);

cout <<CYAN<<"~~ Generated Password : "<<RESET << password << endl;

string choice;

cout <<"\n ~ \033[92m Do you want to check password's strength (yes/y or no/n): " <<RESET;

cin>>choice;


    if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y" || choice =="Yes") 
      {

        string command = "python keycheck.py \"" + password + "\"";  // Handle spaces in passwords

        system(command.c_str());

      } 

    else
      {

        cout << "Okay, skipping Password Strength Checking... But don't blame me if hackers love your password!😁 \n";

      }


}