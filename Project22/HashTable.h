#pragma once
//This is header file 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
struct node {
    string username;
    string password;
    node* next;

    node(const string& uname, const string& pwd) : username(uname), password(pwd), next(nullptr) {}
};
struct Commit {
    string msg;
    time_t Time; 
    Commit* next;

    Commit(const string& mesg) : msg(mesg), Time(time(nullptr)), next(nullptr) {}
};
struct File {
    string filename;
    File* next;

    File(const string& name) : filename(name), next(nullptr) {}
};
struct Repository {
    string name;
    bool isPublic;
    int forkC;
    int commitC;
    int views;
    File* files;
    Commit* commits;
    vector<string> comments;
    vector<string> likes;
    vector<string> viewers;
    Repository* left;
    Repository* right;

    Repository(const string& repoName, bool visibility);

    ~Repository();
};
struct Tree {
    string userN;
    Repository* Repo;
    Tree* left;
    Tree* right;

    Tree(const string& uname, Repository* repo);
    ~Tree();
};
class HashTable {
public:
    static const int size = 100;
    node* table[size];
    Tree* userRepo[size];
    vector<pair<string, string>> followR;
    int count;

    HashTable();
    ~HashTable();

    int hashFunction(const string& key);
    bool registerUser(const string& Uname, const string& pswd);
    bool login(const string& Uname, const string& pswd);
    void logout(const string& Uname);
    void createRepo(const string& Uname);
    void viewRepo(const string& username);
    void follow(const string& folwr, const string& folwed);
    void unfollow(const string& folwr, const string& folwed);
    void showFollower(const string& Uname);
    void showFollowing(const string& Uname);
    void showFollowers(const string& Uname);
    void deleteRepo(const string& Uname, const string& repoName);
    void insertRepo(Tree*& root, Tree* newNode);
    void updateFollower(const string& Uname);
    Tree* deleteRepofunc(Tree* root, const string& repoName);
    void viewRepofunc(Tree* root);
    int FileCnt(File* head);
};