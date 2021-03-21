#include <iostream>
#include <string.h>
#include <time.h>               //for randomising rand() with time
#include <fstream>              //for creating and editing text file

using namespace std;

int YNchecker(char input)
{
       switch (input)
        {
        case 'Y':
        case 'y':
            return 1;
        case 'N':
        case 'n':
            return 2;
        default:
            cout<<"\nPlease enter a valid input";
            return 3;
        }
}

bool checkArray(int arrayYN[])
{
    for (int i = 0; i < sizeof(arrayYN); i++)
    {
        if(arrayYN[i] != 0)
        {
            return false;
        }
    }
            return true;

}


int * YNArrayMaker()
{
    char capitalYN;
    char smallYN;
    char numberYN;
    char symbolYN;
    int capitalYNreturn;
    int smallYNreturn;
    int numberYNreturn;
    int symbolYNreturn;
    static int arrayYN[4] = {0,0,0,0};

    capitalYNLoop:
        cout << "\nDo you want capital letters in Password[Y/N]: ";
        cin >> capitalYN;
        capitalYNreturn = YNchecker(capitalYN);

        if(capitalYNreturn == 1)
            arrayYN[0] = 1;
        else if (capitalYNreturn == 2)
            arrayYN[0] = 0;
        else
            goto capitalYNLoop;


    smallYNLoop:
        cout << "\nDo you want small letters in Password[Y/N]: ";
        cin >> smallYN;
        smallYNreturn = YNchecker(smallYN);

        if(smallYNreturn == 1)
            arrayYN[1] = 1;
        else if (smallYNreturn == 2)
            arrayYN[1] = 0;
        else
            goto smallYNLoop;


    numberYNLoop:
        cout << "\nDo you want numbers in Password[Y/N]: ";
        cin >> numberYN;
        numberYNreturn = YNchecker(numberYN);

        if(numberYNreturn == 1)
            arrayYN[2] = 1;
        else if (numberYNreturn == 2)
            arrayYN[2] = 0;
        else
            goto numberYNLoop;


    symbolYNLoop:
        cout << "\nDo you want symbols in Password[Y/N]: ";
        cin >> symbolYN;
        symbolYNreturn = YNchecker(symbolYN);

        if(symbolYNreturn == 1)
            arrayYN[3] = 1;
        else if (symbolYNreturn == 2)
            arrayYN[3] = 0;
        else
            goto symbolYNLoop;

    return arrayYN;
}

string PwdGen(int arrayYN[], int digit)
{
    const char capitalArray [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    const char smallArray [26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    const char numberArray [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const char symbolArray [] = {'@', '%', '^', '&', '*', '!', '*', '-', '+'};
    string result;
    int random;

    for (int i = 0; i<digit; ++i)
    {
        startover:
        random = (rand() % 4);

        if(arrayYN[random]==1)
        {

           switch(random)
           {
           case 0:
                result = result + capitalArray[rand() % 26];
                break;
           case 1:
                result = result + smallArray[rand() % 26];
                break;
           case 2:
                result = result + numberArray[rand() % 10];
                break;
           case 3:
                result = result + symbolArray[rand() % (sizeof(symbolArray))];
                break;
           default:
                cout<<"error";

           }

        }

        else if(arrayYN[random]==0)
            goto startover;
    }

    cout<<"\nYour password is: "<<result;
    return result;
}

void File(string result)
{
    string FileName;
    char choice;
    char exist;
    int choiceReturn;
    int existReturn;

    choiceLoop:
    cout << "\n\nDo you want to output password in file[Y/N]: ";
    cin >> choice;

    choiceReturn = YNchecker(choice);
        if(choiceReturn == 3)
            goto choiceLoop;

    existLoop:
    cout << "\nEnter file name: ";
    cin.ignore();                   //for ignoring buffer that makes it without input
    getline(cin, FileName);         //for getting filename with spaces

    ifstream ifile;
    ifile.open(FileName + ".txt");
    if(ifile)
    {
      cout<<"\nFile already exists";
      cout<<"\nWant to replace it[Y/N]: ";
      cin >> exist;
      existReturn = YNchecker(exist);
      if (existReturn == 2)
        goto existLoop;
      else if (existReturn == 3)
        goto existLoop;

    }

    ofstream PasswordFile(FileName + ".txt");
    PasswordFile << result;
    PasswordFile.close();
    cout << "\nPassword stored in " << FileName << ".txt";
}



int isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) == false)
            return false;
    }
    return true;
}

int main()
{
    //variables
    string isNumberMain;
    int digit;
    int *arrayYN;
    string result;

    //for randomness of rand() func
    srand((unsigned) time(0));

    cout << "-----------------------------------------------------------"<<endl;
	cout << "		   Made by Mr Matrix"<<endl;
    cout << "-----------------------------------------------------------"<<endl;

	cout << "Welcome!" <<endl;

	digitCheck:
    cout << "Please enter the number of characters in password: ";
    cin >> isNumberMain;

    //checking if input is number
    if (isNumber(isNumberMain))
        digit = stoi(isNumberMain);

    else
    {
        cout << "\nPlease enter a valid input\n";
        goto digitCheck;
    }

    //array maker
    arrayYNLoop:
    arrayYN = YNArrayMaker();


    //confirming that the values are all not zero
    if (checkArray(arrayYN) == true)
    {
        cout << "\nPlease select one of the above option.";
        goto arrayYNLoop;
    }


    //main Password generator
    result = PwdGen(arrayYN, digit);

    //storing password in file
    File(result);

    cin.ignore();
    cin.get();
    return 0;

}
