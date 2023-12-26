#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



struct Member {
    int id;
    string name;
    int totalMeals;
    double currentBalance;
    double bazarcost;
};


void deposit(vector<Member>& members);
void recordBazarCost(vector<Member>& members);
void addMeal(vector<Member>& members);
void addMember(vector<Member>& members);
void viewCurrentStatus(const vector<Member>& members);
double getMealRate(const vector<Member>& members);
void resetSystem(vector<Member>& members);
int getTotalMeal(const Member& member);


void saveData(const vector<Member>& members);
void loadData(vector<Member>& members);

int main() {
    vector<Member> members;
    loadData(members);

    int choice;
    do {
        cout << "Mess Management System\n";
        cout << "1) Add Member\n";
        cout << "2) Deposit\n";
        cout << "3) Bazar Cost\n";
        cout << "4) Add Meal\n";
        cout << "5) View Current\n";
        cout << "6) Reset System\n";

        cout << "0) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember(members);

                break;
            case 2:
                deposit(members);

                break;
            case 3:
                recordBazarCost(members);

                break;
            case 4:
                addMeal(members);
                break;
            case 5:
                viewCurrentStatus(members);
                break;
            case 6:
                resetSystem(members);
                break;
            case 0:
                cout << "Exiting the program.\n";
                saveData(members);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void deposit(vector<Member>& members) {
    int memberId;
    double amount;

    cout << "Enter Member ID: ";
    cin >> memberId;

    for (Member& member : members) {
        if (member.id == memberId) {
            cout << "Enter deposit amount: tk";
            cin >> amount;
            member.currentBalance += amount;
            cout << "Deposit successful. Updated balance: " << member.currentBalance << endl;


            saveData(members);
            return;
        }
    }

    cout << "Member not found with ID: " << memberId << endl;
}

void recordBazarCost(vector<Member>& members) {
     double cost;
     int memberId;

    cout << "Enter Member ID: ";
    cin >> memberId;

    for (Member& member : members) {
        if (member.id == memberId) {
            cout << "Enter cost of bazar: ";
            cin >> cost;
            member.bazarcost += cost;
            cout << "Bazar cost added succesfully " << endl;
            saveData(members);

            return;
        }
}
cout << "Member not found with ID: " << memberId << endl;
}

//         double getCurrentBalance(const Member& member) {
//
//     return member.currentBalance - (member.totalMeals * getMealRate({member}));
// }
//     double cost;

//     cout << "Enter Bazar cost: $";
//     cin >> cost;
//    // total_cost+=cost;


//     for (Member& member : members) {
//         member.bazarcost+=cost;
//     }

//     cout << "Bazar cost recorded successfully.\n";
//     saveData(members); // Save data after recording bazar cost



void addMeal(vector<Member>& members) {
    int memberId, meals;

    cout << "Enter Member ID: ";
    cin >> memberId;

    for (Member& member : members) {
        if (member.id == memberId) {
            cout << "Enter number of meals: ";
            cin >> meals;
            member.totalMeals += meals;
            cout << "Meals added successfully. Total meals: " << member.totalMeals << endl;
            double x=getMealRate(members);
            double y=x*meals;
           // member.currentBalance -= y;
            saveData(members);
            return;
        }
    }

    cout << "Member not found with ID: " << memberId << endl;
}

void addMember(vector<Member>& members) {
    Member newMember;
    cout << "Enter Member ID: ";
    cin >> newMember.id;


    for (const Member& member : members) {
        if (member.id == newMember.id) {
            cout << "Member with ID " << newMember.id << " already exists.\n";
            return;
        }
    }

    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, newMember.name);

    newMember.totalMeals = 0;
    newMember.currentBalance = 0;
    newMember.bazarcost=0;

    members.push_back(newMember);
    cout << "Member added successfully.\n";
    saveData(members);
}

void viewCurrentStatus(const vector<Member>& members) {
    cout << "Current Status\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << "Member ID\tMember Name\tTotal Meals\tCurrent Balance\t\tBazar\t\tRate\n";
    cout << "-----------------------------------------------------------------------------------------\n";


    for (const Member& member : members) {
        double x=getMealRate(members);
        int y=getTotalMeal(member);
        double z=member.currentBalance-(x*y);
        cout << member.id << "\t\t" << member.name << "\t\t" << member.totalMeals << "\t\ttk" << z <<"\t\t\t"<<member.bazarcost<<"\t\t"<<x<<endl;
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}
double getMealRate(const vector<Member>& members) {
    double totalBazarCost = 0;
    int totalMeals = 0;

    for (const Member& member : members) {
        totalBazarCost += member.bazarcost;
        totalMeals += member.totalMeals;
    }

    return (totalMeals > 0) ? (totalBazarCost / totalMeals) : 0;

}

void saveData(const vector<Member>& members) {
    ofstream file("members.txt");

    for (const Member& member : members) {
        file << member.id << " " << member.name << " " << member.totalMeals << " " << member.currentBalance <<" "<<member.bazarcost << endl;
    }

    file.close();
}

void loadData(vector<Member>& members) {
    ifstream file("members.txt");

    if (!file.is_open()) {
        cout << "No previous data found.\n";
        return;
    }

    Member member;
    while (file >> member.id >> member.name >> member.totalMeals >> member.currentBalance >> member.bazarcost) {
        members.push_back(member);
    }

    file.close();
}
void resetSystem(vector<Member>& members) {
    ofstream clearFile("members.txt", ios::trunc);
    clearFile.close();


    members.clear();

    cout << "System reset successfully. All information deleted.\n";
}
int getTotalMeal(const Member& member) {
    int meal= member.totalMeals;

    return meal;
}
