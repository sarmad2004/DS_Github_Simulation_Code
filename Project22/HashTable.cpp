//This is cpp file of body 
#include "HashTable.h"

Repository::Repository(const string& repoName, bool visibility) : name(repoName), isPublic(visibility),
forkC(1), commitC(5), views(3), files(nullptr), commits(nullptr), left(nullptr), right(nullptr) {}
Repository::~Repository()
{
    delete[] files;
    delete[] commits;
}
Tree::Tree(const string& uname, Repository* repo) : userN(uname), Repo(repo), left(nullptr), right(nullptr) {}
Tree::~Tree() {
    delete[] Repo;
}
HashTable::HashTable() : count(0)
{
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
        userRepo[i] = nullptr;
    }
}
HashTable::~HashTable()
{
    delete[] table;
    delete[] userRepo;
}
int HashTable::hashFunction(const string& key)
{
    int hash = 0;
    for (char ch : key)
    {
        hash =hash+ ch;
    }
    return hash % size;
}
bool HashTable::registerUser(const string& Uname, const string& pswd)
{
    int indx = hashFunction(Uname);
    node* curr = table[indx];
    while (curr != nullptr)
    {
        if (curr->username == Uname)
        {
            cout << "Username " << Uname << " already exists. Please choose a different username." << endl;
            return false;
        }
        curr = curr->next;
    }
    node* newNode = new node(Uname, pswd);
    newNode->next = table[indx];
    table[indx] = newNode;
    cout << "User " << Uname << " registered successfully." << endl;
    ofstream userFile(Uname + "_repo_data.txt");
    userFile << "Repository Data for User: " << Uname << endl;
    userFile.close();
    return true;
}

bool HashTable::login(const string& Uname, const string& pswd)
{
    int idex = hashFunction(Uname);
    node* curr = table[idex];
    while (curr != nullptr)
    {
        if (curr->username == Uname && curr->password == pswd)
        {
            cout << "User " << Uname << " logged in successfully." << endl;
            ifstream userFile(Uname + "_repo_data.txt");
            string line;
            while (getline(userFile, line))
            {
                cout << line << endl;
            }
            userFile.close();
            showFollower(Uname);
            showFollowing(Uname);
            showFollowers(Uname);
            return true;
        }
        curr = curr->next;
    }
    cout << "Invalid username or password." << endl;
    return false;
}

void HashTable::logout(const string& Uname)
{
    cout << "User " << Uname << " logged out." << endl;
}

void HashTable::createRepo(const string& Uname)
{
    string repoName;
    bool repoTyp;
    cout << "Enter repository name: ";
    cin >> repoName;
    cout << "Is the repository public? (1 for Yes, 0 for No): ";
    cin >> repoTyp;
    int index = hashFunction(Uname);
    node* curr = table[index];
    while (curr != nullptr)
    {
        if (curr->username == Uname)
        {
            Repository* newRepo = new Repository(repoName, repoTyp);
            Tree* repoNode = new Tree(Uname, newRepo);
            if (userRepo[index] == nullptr)
            {
                userRepo[index] = repoNode;
            }
            else
            {
                insertRepo(userRepo[index], repoNode);
            }
            cout << "Repository '" << repoName << "' created successfully for user " << Uname << endl;
            ofstream userFile(Uname + "_repo_data.txt", ios::app);
            cout << endl;
            userFile << "Repository: " << repoName << ", Visibility: " << endl;
            if (repoTyp) {
                cout << "Public";
            }
            else
            {
                cout << "Private";
            }
            cout << endl;
            userFile.close();
            return;
        }
        curr = curr->next;
    }
    cout << "User " << Uname << " not found. Please register first." << endl;
}
void HashTable::viewRepo(const string& username)
{
    int index = hashFunction(username);
    viewRepofunc(userRepo[index]);
}
void HashTable::viewRepofunc(Tree* root)
{
    if (root != nullptr)
    {
        viewRepofunc(root->left);
        cout << "Repo name: " << root->Repo->name << ", Repo files: " << FileCnt(root->Repo->files)
            << ", Repo commits: " << root->Repo->commitC++ << ", Repo fork count: " << root->Repo->forkC++
            << ", Views: " << root->Repo->views++ << ", Likes: " << root->Repo->likes.size() << ", Viewers: " << root->Repo->viewers.size() << endl;
        cout << "Comments: ";
        for (const string& comment : root->Repo->comments)
        {
            cout << comment << " ";
        }
        cout << endl;
        viewRepofunc(root->right);
    }
}
void HashTable::insertRepo(Tree*& root, Tree* newNode)
{
    if (root == nullptr)
    {
        root = newNode;
    }
    else
    {
        if (newNode->Repo->name < root->Repo->name)
        {
            insertRepo(root->left, newNode);
        }
        else
        {
            insertRepo(root->right, newNode);
        }
    }
}
int HashTable::FileCnt(File* head)
{
    File* current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

void HashTable::follow(const string& folwr, const string& folwed)
{
    followR.push_back(make_pair(folwr, folwed));
    cout << folwr << " is now following " << folwed << endl;
    updateFollower(folwr);
}

void HashTable::unfollow(const string& folwr, const string& folwed)
{
    for (auto i = followR.begin(); i != followR.end(); i++)
    {
        if (i->first == folwr && i->second == folwed)
        {
            followR.erase(i);
            break;
        }
    }
    cout << folwr << " unfollowed " << folwed << endl;
    updateFollower(folwr);
}

void HashTable::showFollower(const string& Uname)
{
    cout << "Follower list of " << Uname << ":" << endl;
    for (const auto& rel : followR)
    {
        if (rel.second == Uname)
        {
            cout << rel.first << endl;
        }
    }
}
void HashTable::showFollowing(const string& Uname)
{
    cout << "Following list of " << Uname << ":" << endl;
    for (const auto& rel : followR)
    {
        if (rel.first == Uname)
        {
            cout << rel.second << endl;
        }
    }
}

void HashTable::showFollowers(const string& Uname)
{
    cout << "Followers list of " << Uname << ":" << endl;
    for (const auto& rel : followR)
    {
        if (rel.second == Uname)
        {
            cout << rel.first << endl;
        }
    }
}
void HashTable::updateFollower(const string& Uname)
{
    ofstream userFile(Uname + "_repo_data.txt", ios::app);
    cout << endl;
    userFile << "----- Follower List -----" << endl;
    cout << endl;
    for (const auto& rel : followR)
    {
        if (rel.second == Uname)
        {
            userFile << rel.first << endl;
        }
    }
    userFile.close();
}
void HashTable::deleteRepo(const string& Uname, const string& repoName)
{
    int index = hashFunction(Uname);
    Tree* userTree = userRepo[index];
    userTree = deleteRepofunc(userTree, repoName);
    userRepo[index] = userTree;
}

Tree* HashTable::deleteRepofunc(Tree* root, const string& repoName)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (repoName < root->Repo->name)
    {
        root->left = deleteRepofunc(root->left, repoName);
    }
    else if (repoName > root->Repo->name)
    {
        root->right = deleteRepofunc(root->right, repoName);
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            Tree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Tree* temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Tree* minRight = root->right;
            while (minRight->left != nullptr)
            {
                minRight = minRight->left;
            }
            root->Repo = minRight->Repo;
            root->right = deleteRepofunc(root->right, minRight->Repo->name);
        }
    }
    return root;
}