#include <iostream>
#include <string.h>
#include <vector>


void menu_main();
void menu_cardValidity();
bool valid_card();
void check_balance();
void deposit();
void withdraw();
void atm_functions();

int money = 1000;

int main()
{
    
    bool repeat_validity = true;
    std::string y_n;


    // loop for checking debit card & 
    // ask if they want to add another when the card is not valid
    while (repeat_validity)
    {

        bool validity = valid_card();
        
        while (validity == false)
        {
            std::cout << "\n\n\t\tDo you want to check an another card (y/n): ";
            std::cin >> y_n;
            if (y_n == "n")
            {
                std::cout << "\n\n\t\tThank you for using the service.\n\t\tHave a great day.\n\n";
                return 0;
            }
            else if(y_n == "y")
            {
                repeat_validity = true;
                break;
            }
            else 
            {
                std::cout << "\n\n\t\tPlease enter a single character y or n.\n";
            }


        }
        repeat_validity = false;

    }

    // looping through atm functions until the user exit
    atm_functions();
 
}

// show main menu
void menu_main() 
{
    std::cout << "\n\n\t\t------------Menu------------\n\n";
    std::cout << "\t\t 1. Check balance \n";
    std::cout << "\t\t 2. Deposit\n";
    std::cout << "\t\t 3. Withdraw\n";
    std::cout << "\t\t 4. Exit\n\n";
    std::cout << "\t\t----------------------------\n\n";
}

// show menu for card validity
void menu_cardValidity() 
{

    std::cout << "\n\n\t\t 1. Visa \n"; // 13 or 16
    std::cout << "\t\t 2. Mastercard\n"; // 16
    std::cout << "\t\t 3. Discover\n"; // 16
    std::cout << "\t\t 4. American Express\n\n"; // 15
    std::cout << "\t\t----------------------------\n";
}

void atm_functions() 
{
    // show menu
    menu_main();

    int user_choice;
    // getting user's choice
    std::cout << "\n\tEnter the index of your choice: ";
    std::cin >> user_choice;

    // switch case for each of the user's choice 
    switch (user_choice)
    {

    case 1:
        check_balance();
        atm_functions();
        break;

    case 2:
        
        deposit();
        atm_functions();
        break;

    case 3:
        withdraw();
        atm_functions();
        break;

    case 4:
        std::cout << "\n\n\t\tThank you for using the service.\n\t\tHave a great day.\n\n";
        break;

    default:
        system("cls");
        std::cout << "\n\n\tPlease input a valid option.";
        atm_functions();
        break;
    }
}

// checking the validity of the card
// used Luhn algorithm
bool valid_card() 
{

        bool company_length;
        std::string debit_num, cvv;
        int len, card_company, num, sum;

        // Asking information regarding the debit card
        menu_cardValidity();
        std::cout << "\n\tEnter the index of your company: ";
        std::cin >> card_company;
        std::cout << "\n\n\t\tEnter your debit card's number: ";
        std::cin >> debit_num;
        std::cout << "\n\n\t\tEnter your CVV: ";
        std::cin >> cvv;

        len = debit_num.size();

        // checking if the length is right for each company
        if (
            ((card_company == 1 && (len == 13 || len == 16)) ||
            (card_company == 4 && len == 15) || 
            ((card_company == 2 || card_company == 3 ) && len == 16)) && 
            (cvv.length() == 3)
            )
        {
            company_length = true;
        }

        else
        {
            
            std::cout << "\n\t\tError! Your debit card is not legit!";
            company_length = false;
        }

        // if length is right for the given company & cvv is 3 numbers, 
        // continue with following if-else
        // using Luhn algorithm to check the validity of the debit card
        if (company_length)
        {
            // create a vector
            std::vector<int> card_num{};         

            // add each number to the vector
            for (char& c : debit_num) {
                card_num.push_back(int(c)-48);
            }
            
            /* get every other number to the right
               if more than 1 digit, add them
               add all of final numbers in the list 
             */
            for (int i = len - 2; i > 0; i -= 2) 
            {
                num = card_num[i] * 2;
                sum = num / 10;
                sum = num % 10;
            }

            if (sum % 10 != 0) 
            {
                return false;
            }
            return true;
        }
        else
        {
            return false;

        }
    

}

// giving output on the amount of money in the account
void check_balance() 
{
    std::cout << "\n\n\tYour balance is " << money;
  
}

// deposit money into the account
void deposit()
{
    int deposit_money;
    std::cout << "\n\n\tEnter the amount you want to deposit: ";
    std::cin >> deposit_money;
    money += deposit_money;

    std::cout << "\n\n\tYou successfully deposit " << deposit_money << " into your account";

}

// withdraw money from the account
void withdraw() 
{
    int withdraw_money;
    std::cout << "\n\n\tEnter the amount you want to withdraw: ";
    std::cin >> withdraw_money;

    // able to be withdraw iff the amount the user want to withdraw
    // is less than the amount in the account
    if (withdraw_money < money) 
    {
        money -= withdraw_money;
        std::cout << "\n\n\tYou successfully withdraw " << withdraw_money << " from your account";
    }

    // not sufficient & give options again
    else
    {  
        int option = 0;

        std::cout << "\n\tYou don't have sufficient amount of money in your account\n\n";

        // loop to repeat until input is valid
        do {
            
            std::cout << "\t 1. Withdraw\n";
            std::cout << "\t 2. Go back to menu\n";
            std::cout << "\t 3. Exit\n";

            std::cout << "\n\tEnter the index of your choice: ";
            std::cin >> option;


            switch (option)
            {
                std::cout << "\n\tEnter the index of your choice: ";
                std::cin >> option;
            case 1:
                withdraw();
                break;
            case 2:
                main();
                break;
            case 3:
                break;

            default:
                system("cls");
                std::cout << "\n\n\tPlease input a valid option.\n\n";
                break;
            }
        } while (option != 1 && option != 2 && option != 3);
        
    }

}