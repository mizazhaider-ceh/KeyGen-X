#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <limits>

#ifndef _WIN32
#include <sys/wait.h>
#endif

using namespace std;


// Defining some usefule colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define GOLD "\033[38;5;220m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define YELLOW "\033[93m"

#ifdef _WIN32
#define POPEN _popen
#define PCLOSE _pclose
#else
#define POPEN popen
#define PCLOSE pclose
#endif

//============== Functions =================

string generate_password(int length)
{
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.length() - 1);

    string password = "";
    for (int i = 0; i < length; i++)
    {
        password += characters[distribution(generator)];
    }

    return password;
}

// Ask the user for a password length and validate it.
// Keeps asking until a sane number is entered.
int ask_length()
{
    const int MIN_LEN = 1;
    const int MAX_LEN = 1024;

    while (true)
    {
        int length = 0;
        cout << GOLD << "\n~~ Enter your desired length of password (" << MIN_LEN << "-" << MAX_LEN << "): " << RESET;

        if (!(cin >> length))
        {
            // user typed something that is not a number
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "~~ That is not a number. Try again." << RESET << endl;
            continue;
        }

        if (length < MIN_LEN || length > MAX_LEN)
        {
            cout << RED << "~~ Length must be between " << MIN_LEN << " and " << MAX_LEN << "." << RESET << endl;
            continue;
        }

        return length;
    }
}

// Run keycheck.py, feeding it the password over stdin.
// Passing it through stdin (instead of building a shell command string)
// means special characters like $ or % in the password can never be
// interpreted by the shell. Returns the checker's exit code.
int run_strength_check(const string& password, const string& python_cmd)
{
    string cmd = python_cmd + " keycheck.py";
    FILE* pipe = POPEN(cmd.c_str(), "w");
    if (!pipe)
    {
        cout << RED << "~~ Could not start keycheck.py" << RESET << endl;
        return -1;
    }

    fwrite(password.c_str(), 1, password.size(), pipe);
    fputc('\n', pipe);

    int status = PCLOSE(pipe);
#ifdef _WIN32
    return status;
#else
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return -1;
#endif
}

//============== Main Part ==================

int main(){

#ifdef _WIN32
system("chcp 65001 >nul");  // This will enable UTF-8 without showing output so tha banner can correctly show
#endif

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

int length = ask_length();

//====== using the function =====

string password = generate_password(length);

cout <<CYAN<<"~~ Generated Password : "<<RESET << password << endl;

string choice;

cout <<"\n ~ \033[92m Do you want to check password's strength (yes/y or no/n): " <<RESET;

cin>>choice;


    if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y" || choice =="Yes")
      {

        // 'python' vs 'python3' differs per platform, try the common one first
#ifdef _WIN32
        int rc = run_strength_check(password, "python");
#else
        int rc = run_strength_check(password, "python3");
        if (rc == 127)
        {
            // 'python3' not found either, last resort: plain 'python'
            rc = run_strength_check(password, "python");
        }
#endif
        if (rc != 0)
        {
            cout << YELLOW << "~~ Strength check did not complete cleanly (exit code " << rc << ")." << RESET << endl;
        }

      }

    else
      {

        cout << "Okay, skipping Password Strength Checking... But don't blame me if hackers love your password!😁 \n";

      }


}
