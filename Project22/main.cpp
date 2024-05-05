//#include <iostream>
//#include <fstream>
//#include <string>
//#include <ctime>
//#include <vector>
//#include "HashTable.h"
//using namespace std;
//// Node to hold username-password pair
//struct node {
//    string username;
//    string password;
//    node* next;
//
//    node(const string& uname, const string& pwd)
//    {
//        username = uname;
//        password = pwd;
//        next = nullptr;
//    }
//};
//struct Commit {
//    string msg;
//    time_t Time; // Time of commit
//    Commit* next;
//
//    Commit(const string& mesg)
//    {
//        msg = mesg;
//        Time = time(nullptr);
//        next = nullptr;
//    }
//};
//struct File {
//    string filename;
//    File* next;
//
//    File(const string& name)
//    {
//        filename = name;
//        next = nullptr;
//    }
//};
//struct Repository {
//    string name;
//    bool isPublic;
//    int forkC;
//    int commitC;
//    int views;
//    File* files;
//    Commit* commits;
//    vector<string> comments;
//    vector<string> likes;
//    vector<string> viewers;
//    Repository* left;
//    Repository* right;
//
//    Repository(const string& repoName, bool visibility) : name(repoName), isPublic(visibility),
//        forkC(1), commitC(5), views(3), files(nullptr), commits(nullptr), left(nullptr), right(nullptr) {}
//
//    ~Repository()
//    {
//        delete[] files;
//        delete[] commits;
//    }
//};
//// Tree node to represent a user's repositories
//struct Tree {
//    string userN;
//    Repository* Repo;
//    Tree* left;
//    Tree* right;
//
//    Tree(const string& uname, Repository* repo)
//    {
//        userN = uname;
//        Repo = repo;
//        left = nullptr;
//        right = nullptr;
//    }
//    ~Tree() {
//        delete[] Repo;
//    }
//};
//// Hash Table class
//class HashTable {
//public:
//    static const int size = 100;
//    node* table[size];
//    Tree* userRepo[size];
//    vector<pair<string, string>> followR;
//    int count;
//    int hashFunction(const string& key)
//    {
//        int hash = 0;
//        for (char ch : key)
//        {
//            hash =hash+ ch;
//        }
//        return hash % size;
//    }
//    HashTable()
//    {
//        count = 0;
//
//        for (int i = 0; i < size; i++)
//        {
//            table[i] = nullptr;
//            userRepo[i] = nullptr;
//
//        }
//    } // Function to register a new user
//    bool registerUser(const string& Uname, const string& pswd)
//    {
//        int indx = hashFunction(Uname);           // Check if username already exists
//        node* curr = table[indx];
//        while (curr != nullptr)
//        {
//            if (curr->username == Uname)
//            {
//                cout << "Username " << Uname << " already exists Please choose a different username" << endl;
//                return false;
//            }
//            curr = curr->next;
//        }
//        // If username doesn't exist, register the new user
//        node* newNode = new node(Uname, pswd);
//        newNode->next = table[indx];
//        table[indx] = newNode;
//        cout << "User " << Uname << " registered successfully" << endl;
//        // Create a file for the user's repository data
//        ofstream userFile(Uname + "_repo_data.txt");
//        userFile << "Repository Data for User: " << Uname << endl;
//        userFile.close();
//        return true;
//    }
//    // Function to login a user
//    bool login(const string& Uname, const string& pswd)
//    {
//        int idex = hashFunction(Uname);
//
//        node* curr = table[idex];
//        while (curr != nullptr)
//        {
//            if (curr->username == Uname && curr->password == pswd)
//            {
//                cout << "User " << Uname << " logged in successfully" << endl;
//
//                ifstream userFile(Uname + "_repo_data.txt");
//                string line;
//                while (getline(userFile, line))
//                {
//                    cout << line << endl;
//                }
//                userFile.close();
//                showFollower(Uname);
//                showFollowing(Uname);
//                showFollowers(Uname);
//                return true;
//            }
//            curr = curr->next;
//        }
//        cout << "Invalid username or password" << endl;
//        return false;
//    }
//    void logout(const string& Uname)
//    {
//        cout << "User " << Uname << " logged out" << endl;
//    } // Function to create a new repository for a user
//    void createRepo(const string& Uname)
//    {
//        string repoName;
//        bool repoTyp;
//        cout << "Enter repository name: ";
//        cin >> repoName;
//        cout << "Is the repository public? (1 for Yes, 0 for No): ";
//        cin >> repoTyp;
//        int index = hashFunction(Uname);
//
//        node* curr = table[index];
//        while (curr != nullptr)
//        {
//            if (curr->username == Uname)
//            {
//
//                Repository* newRepo = new Repository(repoName, repoTyp);
//                // Create a tree node for the repository
//                Tree* repoNode = new Tree(Uname, newRepo);
//                // Add repository to the repository tree
//                if (userRepo[index] == nullptr)
//                {
//                    userRepo[index] = repoNode;
//                }
//                else
//                {
//                    insertRepo(userRepo[index], repoNode);
//                }
//                cout << "Repository '" << repoName << "' created successfully for user " << Uname << endl;
//
//                ofstream userFile(Uname + "_repo_data.txt", ios::app);
//                cout << endl;
//                userFile << "Repository: " << repoName << ", Visibility: " << endl;
//                if (repoTyp) {
//                    cout << "Public";
//                }
//                else
//                {
//                    cout << "Private";
//                }
//                
//                cout<< endl;
//                userFile.close();
//                return;
//            }
//            curr = curr->next;
//        }
//        cout << "User " << Uname << " not found Please register first" << endl;
//    }
//    void viewRepo(const string& username)
//    {
//        int index = hashFunction(username);
//        viewRepofunc(userRepo[index]);
//    }
//    void viewRepofunc(Tree* root)
//    {
//        if (root != nullptr)
//        {
//            viewRepofunc(root->left);
//            cout << "Repo name: " << root->Repo->name << ", Repo files: " << FileCnt(root->Repo->files)
//                << ", Repo commits: " << root->Repo->commitC++ << ", Repo fork count: " << root->Repo->forkC++
//                << ", Views: " << root->Repo->views++ << ", Likes: " << root->Repo->likes.size() << ", Viewers: " << root->Repo->viewers.size() << endl;
//            cout << "Comments: ";
//            for (const string& comment : root->Repo->comments)
//            {
//                cout << comment << " ";
//            }
//            cout << endl;
//            viewRepofunc(root->right);
//        }
//    }         // Function to insert a repository node into a repository tree
//    void insertRepo(Tree*& root, Tree* newNode)
//    {
//        if (root == nullptr)
//        {
//            root = newNode;
//        }
//        else
//        {
//            if (newNode->Repo->name < root->Repo->name)
//            {
//                insertRepo(root->left, newNode);
//            }
//            else
//            {
//                insertRepo(root->right, newNode);
//            }
//        }
//    }               // Helper function to count files in a linked list
//    int FileCnt(File* head)
//    {
//        File* current = head;
//        while (current != nullptr)
//        {
//            count++;
//            current = current->next;
//        }
//        return count;
//    }                         // Function to follow a user
//    void follow(const string& folwr, const string& folwed)
//    {
//        followR.push_back(make_pair(folwr, folwed));
//        cout << folwr << " is now following " << folwed << endl;
//
//        updateFollower(folwr);
//    }                   // Function to unfollow a user
//    void unfollow(const string& folwr, const string& folwed)
//    {
//        for (auto i = followR.begin(); i != followR.end(); i++)
//        {
//            if (i->first == folwr && i->second == folwed)
//            {
//                followR.erase(i);
//                break;
//            }
//        }
//        cout << folwr << " unfollowed " << folwed << endl;
//
//        updateFollower(folwr);
//    }   // Function to show follower list of a user
//    void showFollower(const string& Uname)
//    {
//        cout << "Follower list of " << Uname << ":" << endl;
//        for (const auto& rel : followR)
//        {
//            if (rel.second == Uname)
//            {
//                cout << rel.first << endl;
//            }
//        }
//    }                   // Function to show users followed by a user
//    void showFollowing(const string& Uname)
//    {
//        cout << "Following list of " << Uname << ":" << endl;
//        for (const auto& rel : followR)
//        {
//            if (rel.first == Uname)
//            {
//                cout << rel.second << endl;
//            }
//        }
//    }                    // Function to show users following a user
//    void showFollowers(const string& Uname)
//    {
//        cout << "Followers list of " << Uname << ":" << endl;
//        for (const auto& rel : followR)
//        {
//            if (rel.second == Uname)
//            {
//                cout << rel.first << endl;
//            }
//        }
//    }          // Function to update follower list in the account file
//    void updateFollower(const string& Uname)
//    {
//        ofstream userFile(Uname + "_repo_data.txt", ios::app);
//        cout << endl;
//        userFile << "----- Follower List -----";
//        cout << endl;
//        for (const auto& rel : followR)
//        {
//            if (rel.second == Uname)
//            {
//                userFile << rel.first << endl;
//            }
//        }
//        userFile.close();
//    }
//    void deleteRepo(const string& Uname, const string& repoName)
//    {
//        int index = hashFunction(Uname);
//        Tree* userTree = userRepo[index];
//        userTree = deleteRepofunc(userTree, repoName);
//        userRepo[index] = userTree;
//    }
//    Tree* deleteRepofunc(Tree* root, const string& repoName)
//    {
//        if (root == nullptr)
//        {
//            return nullptr;
//        }
//        if (repoName < root->Repo->name)
//        {
//            root->left = deleteRepofunc(root->left, repoName);
//        }
//        else if (repoName > root->Repo->name)
//        {
//            root->right = deleteRepofunc(root->right, repoName);
//        }
//        else
//        {                                        // Case 1: Node to be deleted has no children
//            if (root->left == nullptr && root->right == nullptr)
//            {
//
//                delete root;
//                return nullptr;
//            }                                                  // Case 2: Node to be deleted has only one child
//            else if (root->left == nullptr)
//            {
//                Tree* temp = root->right;
//
//                delete root;
//                return temp;
//            }
//            else if (root->right == nullptr)
//            {
//                Tree* temp = root->left;
//
//                delete root;
//                return temp;
//            }                                       // Case 3: Node to be deleted has two children
//            else
//            {
//
//                Tree* minRight = root->right;
//                while (minRight->left != nullptr)
//                {
//                    minRight = minRight->left;
//                }
//
//                root->Repo = minRight->Repo;
//
//                root->right = deleteRepofunc(root->right, minRight->Repo->name);
//            }
//        }
//        return root;
//    }
//};
//int main()
//{
//    HashTable ha;
//    string currUser, Uname, follow, Unfollow,reponame;
//    int num, n1, choice;
//    cout << "Please enter how many members you want to register: ";
//    cin >> num;
//    for (int i = 0; i < num; i++)
//    {
//        string user, pswd;
//        cout << "Enter username for member " << i + 1 << ": ";
//        cin >> user;
//        cout << "Enter password for member " << i + 1 << ": ";
//        cin >> pswd;
//        ha.registerUser(user, pswd);
//    }
//    cout << "Please enter the number of logins: ";
//    cin >> n1;
//    for (int j = 0; j < n1; j++)
//    {
//        string user, pswd;
//        cout << "Please enter username for login " << j + 1 << ": ";
//        cin >> user;
//        cout << "Please enter password for login " << j + 1 << ": ";
//        cin >> pswd;
//        ha.login(user, pswd);
//    }
//    while (true)
//    {
//        cout << endl;
//        cout << "----- Menu -----" << endl;
//        cout << "1. Create a new repository" << endl;
//        cout << "2. View repository stats" << endl;
//        cout << "3. Delete Repository " << endl;
//        cout << "4. Follow a user" << endl;
//        cout << "5. Unfollow a user" << endl;
//        cout << "6. See followers list" << endl;
//        cout << "7. Logout" << endl;
//        cout << "8. Exit" << endl;
//        cout << "Enter your choice: ";
//        cin >> choice;
//        switch (choice)
//        {
//        case 1:
//            cout << "Enter your username: ";
//            cin >> currUser;
//            ha.createRepo(currUser);
//            break;
//        case 2:
//            cout << "Enter the username to view repository stats: ";
//            cin >> Uname;
//            ha.viewRepo(Uname);
//            break;
//        case 3:
//            cout << "For Deletion of Repository Enter Username" << endl;
//            cin >> currUser;
//            cout << "Enter Repository name" << endl;
//            cin >> reponame;
//            ha.deleteRepo(currUser,reponame);
//            cout << "after Deletion no repository exit" << endl;
//            break;
//        case 4:
//            cout << "Enter your username: ";
//            cin >> currUser;
//            cout << "Enter the username you want to follow: ";
//            cin >> follow;
//            ha.follow(currUser, follow);
//            break;
//        case 5:
//            cout << "Enter your username: ";
//            cin >> currUser;
//            cout << "Enter the username you want to unfollow: ";
//            cin >> Unfollow;
//            ha.unfollow(currUser, Unfollow);
//            break;
//        case 6:
//            cout << "Enter the username to see followers list: ";
//            cin >> Uname;
//            ha.showFollower(Uname);
//            break;
//        case 7:
//            cout << "Loged out" << endl;
//            for (int j = 0; j < n1; j++)
//            {
//                string user;
//                cout << "Enter username for logout " << j + 1 << ": ";
//                cin >> user;
//                ha.logout(user);
//            }
//            break;
//        case 8:
//            cout << "Exiting" << endl;
//            return 0;
//        default:
//            cout << "Invalid Input" << endl;
//        }
//    }
//    system("pause");
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "HashTable.h"
using namespace std;

int main()
{
    HashTable ha;
    string currUser, Uname, follow, Unfollow, reponame;
    int num, n1, choice;
    cout << "Please enter how many members you want to register: ";
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        string user, pswd;
        cout << "Enter username for member " << i + 1 << ": ";
        cin >> user;
        cout << "Enter password for member " << i + 1 << ": ";
        cin >> pswd;
        ha.registerUser(user, pswd);
    }
    cout << "Please enter the number of logins: ";
    cin >> n1;
    for (int j = 0; j < n1; j++)
    {
        string user, pswd;
        cout << "Please enter username for login " << j + 1 << ": ";
        cin >> user;
        cout << "Please enter password for login " << j + 1 << ": ";
        cin >> pswd;
        ha.login(user, pswd);
    }
    while (true)
    {
        cout << endl;
        cout << "----- Menu -----" << endl;
        cout << "1. Create a new repository" << endl;
        cout << "2. View repository stats" << endl;
        cout << "3. Delete Repository " << endl;
        cout << "4. Follow a user" << endl;
        cout << "5. Unfollow a user" << endl;
        cout << "6. See followers list" << endl;
        cout << "7. Logout" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter your username: ";
            cin >> currUser;
            ha.createRepo(currUser);
            break;
        case 2:
            cout << "Enter the username to view repository stats: ";
            cin >> Uname;
            ha.viewRepo(Uname);
            break;
        case 3:
            cout << "For Deletion of Repository Enter Username" << endl;
            cin >> currUser;
            cout << "Enter Repository name" << endl;
            cin >> reponame;
            ha.deleteRepo(currUser, reponame);
            cout << "after Deletion no repository exit" << endl;
            break;
        case 4:
            cout << "Enter your username: ";
            cin >> currUser;
            cout << "Enter the username you want to follow: ";
            cin >> follow;
            ha.follow(currUser, follow);
            break;
        case 5:
            cout << "Enter your username: ";
            cin >> currUser;
            cout << "Enter the username you want to unfollow: ";
            cin >> Unfollow;
            ha.unfollow(currUser, Unfollow);
            break;
        case 6:
            cout << "Enter the username to see followers list: ";
            cin >> Uname;
            ha.showFollower(Uname);
            break;
        case 7:
            cout << "Loged out" << endl;
            for (int j = 0; j < n1; j++)
            {
                string user;
                cout << "Enter username for logout " << j + 1 << ": ";
                cin >> user;
                ha.logout(user);
            }
            break;
        case 8:
            cout << "Exiting" << endl;
            return 0;
        default:
            cout << "Invalid Input" << endl;
        }
    }
    system("pause");
    return 0;
}