#include<iostream>
#include<fstream>
#include<regex>
#include<vector>
using namespace std;

int main(int argc, char** argv){
    string str;
    string repo(argv[1]);
    string path(argv[2]);
    string name;
    regex re("(.*)(/)(.*)(.git)");
    smatch match;
    if(regex_search(repo, match, re)){
        cout<<match.str(match.size()-2)<<endl;
        name = match.str(match.size()-2);
    }
    else{
        return 404;
    }
    string cmd_path = "cd "+path;
    string cmd_mkdir = "mkdir "+name+" && "+"cd "+name;
    path = path + "\\" + name;
    string cmd_clone = "git clone "+repo;
    string git_path = path + "\\" + name + "\\.git";
    string cmd_log = "git --git-dir " + git_path + " log > commits.txt";
    string cmd_get_repo = cmd_path + " && " + cmd_mkdir + " && " + cmd_clone + " && " + cmd_log;
    //cout<<cmd_get_repo<<endl;
    system(cmd_get_repo.c_str());
    vector<string> commitsVector;
    string commits_path = path + "/commits.txt";
    ifstream commits(commits_path.c_str());
    regex r("(commit)(.*)");
    while(getline(commits,str)){
        if(regex_match(str,r)){
            commitsVector.push_back(str.substr(7));
        }
    }
    cout<<commitsVector.size()<<endl;
    for(int i = commitsVector.size()-1;i>commitsVector.size()-11;i--){
    //for(int i = 0;i<10;i++){
        //string cmd1 = "git --git-dir D:\\project\\OldCommits\\Python_commit_" + commitsVector[i] + " init";
        string cmd1 = "git clone " + git_path + " " + path + "\\Python_commit_" + commitsVector[i];
        //string cmd3 = "git --git-dir D:\\project\\OldCommits\\Python_commit_" + commitsVector[i] + "\\.git checkout -f "+commitsVector[i];
        string cmd2 = "cd " + path + "\\Python_commit_" + commitsVector[i];
        string cmd3 = "git checkout "+commitsVector[i];
        //string cmd3 = "git log > commits.txt";
        
        string command = cmd1 + " && " + cmd2 + " && " + cmd3;
        //cout<<command<<endl;
        system(command.c_str());
    }
    
    return 0;
}