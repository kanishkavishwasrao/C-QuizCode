#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <regex> 

using namespace std;

class Student
{
private:
    string name, roll_no, course, address, email_id, contact_no, score;

public:
    void menu();
    void quiz();
    void login();
    void registration();
};

struct MCQ
{
    string question;
    vector<string> choices;
    char correctChoice;
};

vector<MCQ> readMCQuestions(const string& filename)
{
vector<MCQ> mcQuestions;
ifstream file(filename);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            MCQ mcq;
            getline(iss, mcq.question, '|');

            for (char choice = 'A'; choice <= 'D'; ++choice)
            {
                string choiceText;
                getline(iss, choiceText, '|');
                mcq.choices.push_back(choiceText);
            }

            string correctChoice;
            getline(iss, correctChoice);
            mcq.correctChoice = correctChoice[0];

            mcQuestions.push_back(mcq);
        }
        file.close();
    } else
    {
        cerr << "Error opening file: " << filename << std::endl;
    }

    return mcQuestions;
}

// Function to shuffle questions
void shuffleMCQuestions(vector<MCQ>& mcQuestions)
{
    random_device rd;
    mt19937 g(rd());

    shuffle(mcQuestions.begin(), mcQuestions.end(), g);
}

// Function to play the MCQ quiz
void playMCQuiz(const vector<MCQ>& mcQuestions, int ToAsk)
{
    int score = 0;
    char ag;
    for (int i = 0; i < ToAsk && i < mcQuestions.size(); ++i)
    {
        const auto& mcq = mcQuestions[i];
        cout << "Question: " << mcq.question << endl;

        for (size_t j = 0; j < mcq.choices.size(); ++j)
        {
            cout << static_cast<char>('A' + j) << ". " << mcq.choices[j] << endl;
        }

        char userChoice;
        cout << "Your Answer (A/B/C/D): ";
        cin >> userChoice;

        if (toupper(userChoice) == mcq.correctChoice)
        {
            cout << "Correct!\n";
            score++;
        } 
        else
        {
            cout << "Incorrect. The correct answer is: " << mcq.correctChoice << ". " << mcq.choices[mcq.correctChoice - 'A'] << "\n";
        }

        cout << "-----------------\n";
    }

    cout << "MCQ Quiz completed. Your score: " << score << "/" << min(ToAsk, static_cast<int>(mcQuestions.size())) << endl;
    
    if(score==5)
    {
        cout<<"\nCongratulations!!!\n";
    }
    else if(score==4)
    {
        cout<<"\nWell Done!!!\n";
    }
    else if(score==0 || score==1 || score==2 || score==3)
    {
        cout<<"\nDo you want to play again?\n Enter Y/N: ";
        cin>>ag;
        if(ag=='y' || ag=='Y')
        {
            playMCQuiz(mcQuestions, ToAsk);
        }
        else if (ag=='n' || ag=='N')
        {
            cout<<"\n\nEXIT\n\n";
        }
        else
        {
            cout<<"Invalid Input";
        }
    }
}

void Student::login()
{
    int count = 0;
    char y;
    string userId, password, id, pass;
    system("cls");
    cout << "\nPlease enter username and password: \n";
    cout << "USERNAME: ";
    cin >> userId;
    cout << "PASSWORD: ";
    cin >> password;

    ifstream input("rq1.txt");

    while (input >> id >> pass)
    {
        if (id == userId && pass == password)
        {
            count = 1;
            system("cls");
        }
    }
    
    input.close();
    if (count == 1)
    {
        name = userId;
        cout << userId << "\n Your login is successful.\n";
        cout << "Are you ready to attempt the quiz? Press 'Y' if yes.\n";
        cin >> y;
        if (y == 'Y' || y == 'y') {
            quiz();
        }
        else
            cout << "EXIT";
    }
    else
    {
        cout << "\nLogin Failed.\n";
    }
}

void Student::registration()
{
    string n_userId, n_password, n_mobile, n_email;
    char y;
    system("cls");
    cout << "Enter Username: ";
    cin >> n_userId;
    cout << "Enter Password: ";
    cin >> n_password;
    //MOBILE
    while (true)
    {
        cout << "Enter Mobile Number: ";
        cin >> n_mobile;
        if (regex_match(n_mobile, regex("\\d{10}")))
        {
            break;
        } else
        {
            cout << "Invalid mobile number! Please enter a 10-digit number.\n";
        }
    }
    //EMAIL
    while (true)
    {
        cout << "Enter E-mail ID: ";
        cin >> n_email;
        if (regex_match(n_email, regex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)")))
        {
            break; 
        } 
        else
        {
            cout << "Invalid email address! Please enter a valid email address.\n";
        }
    }

    ofstream f1("rq1.txt", ios::app);
    f1 << n_userId << " " << n_password << " " << n_mobile << " " << n_email << endl;
    system("cls");
    cout << "\n\nRegistration Successful!\n\n";
    cout << "Are you ready to attempt the quiz? Press 'Y' if yes.\n";
    cin >> y;
    if (y == 'Y' || y == 'y')
    {
        quiz();
    } 
    else {
        cout << "EXIT";
    }
}

void Student::menu()
{
    int choice;
    system("cls");

    cout << "--------------------------------------------" << endl;
    cout << "         Welcome to Page              " << endl;
    cout << "                 MENU                       " << endl;
    cout << "Press 1 to LOGIN" << endl;
    cout << "Press 2 to REGISTER" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            login();
            break;

        case 2:
            registration();
            break;

        default:
            system("cls");
            cout << "\nInvalid Input\n";
    }
}

int main()
{
    Student project;
    project.menu();
    return 0;
}

void Student::quiz()
{
    vector<MCQ> mcQuestions = readMCQuestions("mcq_quiz.txt");
    shuffleMCQuestions(mcQuestions);
    playMCQuiz(mcQuestions,5);
}