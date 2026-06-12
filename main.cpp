#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DiaryEntry
{
protected:
    string title;
    string date;
    string content;

public:
    DiaryEntry(const string &title = "", const string &date = "", const string &content = "")
        : title(title), date(date), content(content) {}

    string getTitle() const { return title; }
    string getDate() const { return date; }
    string getContent() const { return content; }
};

class Diary : public DiaryEntry
{
private:
    vector<DiaryEntry> entries;

public:
    virtual void createNewEntry()
    {
        string title, date, content;
        cin.ignore();
        cout << "Title: ";
        getline(cin, title);
        cout << "Date: ";
        getline(cin, date);
        cout << "Content: ";
        getline(cin, content);
        entries.push_back(DiaryEntry(title, date, content));
        cout << "Entry added successfully.\n";
    }

    void viewAllEntries()
    {
        if (entries.empty())
        {
            cout << "No entries to display.\n";
            return;
        }

        cout << "\n            *My Diary*\n";
        for (size_t i = 0; i < entries.size(); ++i)
        {
            cout << "Title: " << entries[i].getTitle() << endl;
            cout << "Date: " << entries[i].getDate() << endl;
            cout << "Content: " << entries[i].getContent() << endl
                 << endl;
        }
    }

    void deleteEntry()
    {
        if (entries.empty())
        {
            cout << "No entries to delete.\n";
            return;
        }

        cout << "List of entries:\n";
        for (size_t i = 0; i < entries.size(); ++i)
        {
            cout << i + 1 << ". " << entries[i].getTitle() << endl;
        }

        cout << "Select entry to delete: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice > 0 && choice <= static_cast<int>(entries.size()))
        {
            entries.erase(entries.begin() + choice - 1);
            cout << "\nEntry deleted successfully.\n";
        }
        else
        {
            cout << "Invalid entry selection.\n";
        }
    }

    virtual void runMenu() = 0;
    virtual void recordEmotions() = 0;
    virtual void recordMeeting() = 0;
};

class LockedDiary : public Diary
{
private:
    string password;

public:
    LockedDiary(const string &password) : password(password) {}

    void createNewEntry() override
    {
        if (!authenticate())
            return;
        Diary::createNewEntry();
    }

    void viewAllEntries()
    {
        if (!authenticate())
            return;
        Diary::viewAllEntries();
    }

    void deleteEntry()
    {
        if (!authenticate())
            return;
        Diary::deleteEntry();
    }

    void recordEmotions() override
    {
        if (!authenticate())
            return;

        int choice;
        string emotion;
        bool validChoice = false;

        while (!validChoice)
        {
            cout << "\nSelect your current emotion:\n";
            cout << "1. Happy \n";
            cout << "2. Scared \n";
            cout << "3. Tired \n";
            cout << "4. Angry \n";
            cout << "5. Sad \n";
            cout << "6. Cry \n";
            cout << "7. Excited \n";
            cout << "8. Confident \n";
            cout << "9. Sick \n";
            cout << "10. Bored \n";
            cout << "Enter your choice (1-10): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                emotion = "Happy ";
                validChoice = true;
                break;
            case 2:
                emotion = "Scared ";
                validChoice = true;
                break;
            case 3:
                emotion = "Tired ";
                validChoice = true;
                break;
            case 4:
                emotion = "Angry ";
                validChoice = true;
                break;
            case 5:
                emotion = "Sad ";
                validChoice = true;
                break;
            case 6:
                emotion = "Cry ";
                validChoice = true;
                break;
            case 7:
                emotion = "Excited ";
                validChoice = true;
                break;
            case 8:
                emotion = "Confident ";
                validChoice = true;
                break;
            case 9:
                emotion = "Sick ";
                validChoice = true;
                break;
            case 10:
                emotion = "Bored ";
                validChoice = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }

        cout << "Emotion recorded: " << emotion << endl;
    }

    void recordMeeting() override
    {
        if (!authenticate())
            return;
        string meetingDetails;
        cin.ignore();
        cout << "Enter details of the meeting: ";
        getline(cin, meetingDetails);
        cout << "Meeting details recorded: " << meetingDetails << endl;
    }

    void changePassword()
    {
        string currentPassword, newPassword, confirmPassword;
        cout << "Enter current password: ";
        cin >> currentPassword;

        if (currentPassword == password)
        {
            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Confirm new password: ";
            cin >> confirmPassword;

            if (newPassword == confirmPassword)
            {
                password = newPassword;
                cout << "Password changed successfully.\n";
            }
            else
            {
                cout << "New passwords do not match. Password not changed.\n";
            }
        }
        else
        {
            cout << "Incorrect current password. Password not changed.\n";
        }
    }

    void runMenu() override
    {
        string attempt;
        cout << "Enter password to unlock: ";
        cin >> attempt;

        if (attempt == password)
        {
            int choice;
            char returnToMenu;
            do
            {
                cout << "\n     Welcome To The Locked Diary !!!\n";
                cout << "\n --------------------------------\n";
                cout << "\n            *Menu*\n";
                cout << "\n      1. Create a new entry\n";
                cout << "      2. See all your list\n";
                cout << "      3. Delete an entry\n";
                cout << "      4. Record emotions\n";
                cout << "      5. Record meeting\n";
                cout << "      6. Change password\n";
                cout << "      7. Exit the program\n";
                cout << "      Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    createNewEntry();
                    break;
                case 2:
                    viewAllEntries();
                    break;
                case 3:
                    deleteEntry();
                    break;
                case 4:
                    recordEmotions();
                    break;
                case 5:
                    recordMeeting();
                    break;
                case 6:
                    changePassword();
                    break;
                case 7:
                    cout << "Exiting program.\n";
                    return;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }

                cout << "\nDo you want to return to the menu? (y/n): ";
                cin >> returnToMenu;
                if (returnToMenu != 'y' && returnToMenu != 'Y')
                {
                    cout << "I hope you will come back to write a diary again :)\n";
                    return;
                }

            } while (true);
        }
        else
        {
            cout << "Incorrect password. Access denied.\n";
        }
    }

private:
    bool authenticate()
    {
        string attempt;
        cout << "Enter password: ";
        cin >> attempt;

        if (attempt == password)
        {
            return true;
        }

        cout << "Incorrect password.\n";
        return false;
    }
};

int main()
{
    LockedDiary diary("1234");

    diary.runMenu();

    return 0;
}

