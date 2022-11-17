#include <iostream>
#include <string>
#include <vector>

using namespace std;



struct card_info
{
    string name;
    int card_number=0;
    int pin=0;
    int cash=0;
};


// __Class [1]__ //bank server
class ATM_P{ 
    int cash=0;
    card_info customer_ex;


public:
    ATM_P(const int& cash_) 
    {
        this->cash = cash_;
    }

    void add_customer_info(const card_info& cin)
    {
        this->customer_ex = cin;
    }

    int getCASH() const{ return this->cash; }

    int getCASH_CUSTOMER() const {return this->customer_ex.cash; }

    int getCARDNUM_CUSTOMER() const {return this->customer_ex.card_number; }

    bool pin_check(const int& num)
    {
        if(this->customer_ex.pin == num)
        {
            return true;
        }
        return false;
    }

    void updatCASH(int edit_cash) { this->cash = edit_cash; }

    void updatCASH_CUSTOMER(int edit_cash) { this->customer_ex.cash = edit_cash; }
};


// __Class [2]__ //atm machine
class ATM_C : public ATM_P{ 
    int card_n;

public:
    ATM_C(const int& cash, const int& car_num) : ATM_P(cash) 
    {
        this->card_n = car_num;
    }

    void new_customer(const int& car_num)
    {
        this->card_n = car_num;
    }

    void withdrawal()
    {
        int input;
        int again_flag=0;
withdrawal_again:
        cout << endl << "** How much do you want? **" << endl <<  "** Now, Your bank balance is $" << getCASH_CUSTOMER() << endl;
        cin >> input;
        if( input > getCASH())
        {
            cout << endl << "!! Sorry, the machine is not enough money " << endl;
            cout << ">> If you want withdrawal again, push number '1'." << endl << ">> Cancellation is '2'" << endl;
            cin >> again_flag;
            if(again_flag == 1)
            {
                goto withdrawal_again;
            }
        }
        else
        {
            cout << endl << "$" << input << " :: Is it correct that you entered it?" << endl;
            cout << ">> Press '1' to re-enter" << endl << ">> Continue is number  '2'" << endl;
            cin >> again_flag;
            if(again_flag == 1)
            {
                goto withdrawal_again;
            }
            else
            {
                cout << endl << "** complete! please, check the machine **" << endl << "** And your bank balace is $" << getCASH_CUSTOMER()-input << endl;
                updatCASH(getCASH() - input);
                updatCASH_CUSTOMER(getCASH_CUSTOMER()-input);
            }
        }
    }

    void deposit()
    {
        int input;
        cout << endl << "** Insert cash **" << endl;        
        cin >> input;
        updatCASH(getCASH() + input);
        updatCASH_CUSTOMER(getCASH_CUSTOMER()+input);
        cout << endl << "** complete! **" << endl << "** Now, your bank balance is $" << getCASH_CUSTOMER() << endl;
    }

    void balance()
    {
        cout << "** Now, your bank balance is $" << getCASH_CUSTOMER() << endl;
    }
};




int main()
{
    // [0] Initialize the ATM system when the system is powered on
    int cash = 10000; //real cash in the ATM 
    int selected;
    int pin_number;
    int card_number_in=0xff;
    ATM_P atm_sys(cash);
    ATM_C atm_c(cash, card_number_in);

    // example customer
    card_info customer1;
    customer1.name = "Joy";
    customer1.card_number = 12345678;
    customer1.pin = 2580;
    customer1.cash = 500;
    atm_c.add_customer_info(customer1);
    
    // ------------------------------------------------

    cout << "===========[ A T M ]==============" << endl;
    int card_number_in_;
    // [1] insert card
insert_card_again:
    cout << "** Insert the card **" << endl;
    cin >> card_number_in_;

    if(atm_c.getCARDNUM_CUSTOMER() != card_number_in_)
    {
        cout << endl << "your card has some problem. Please check again" << endl;
        goto insert_card_again;
    }
    atm_c.new_customer(card_number_in_);

    // [2] read information from card
    // [3] enter your PIN number
    cout << endl << "** Please enter your PIN number **" << endl;
    cin >> pin_number;

pin_check_again:
    if(!atm_c.pin_check(pin_number))
    {
        cout << endl << "PIN is wrong, please enter again" << endl;
        cin >> pin_number;
        goto pin_check_again;
    }
    else
    {
        // [4] select system
        cout << endl << " ** select your transaction **" << endl;
        cout << "1. Withdrawal" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Balance Inquiry" << endl;
        cin >> selected;
        
selected_again:
        switch(selected)
        {
            case 1: //withdrawal
                atm_c.withdrawal();
                break;

            case 2: //deposit
                atm_c.deposit();
                break;

            case 3: //balance inquiry
                atm_c.balance();
                break;

            default:
                cout << "select your transaction, again" << endl;
                cin >> selected;
                goto selected_again;
                break;
        }
    }
    cout << endl << "* Thank you, Have a good day *" << endl;
    cout << "==================================" << endl << endl;
}

