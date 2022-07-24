#pragma once
#include "processcommand.h"
#include "time.h"
#include<string>
#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>


using namespace std;
using namespace std::chrono;
string command, target1, target2;

const string EXIT_COMMAND = "exit";
string currentDirectory = "";
vector<string> history;
auto start = high_resolution_clock::now();

void prefix(string& s)
{

	istringstream iss(s);
	iss >> command;
	iss >> target1;
	string word;
	while (iss >> word)
	{
		target2 += word + " ";
	}

}

bool isNumber(string s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


void getCommandID(string& s)
{
	string temp;
	for (auto x : s)
	{
		if (x >= 'A' && x <= 'Z')
			temp.push_back(x + 'a' - 'A');
		else temp.push_back(x);
	}
	s = temp;
	void date();
	prefix(s);
	int a;
	if (command == "exit") 
	{
		cout << "Closing all process" << endl;
		killAll();
		Sleep(1);
		cout << "Closed all process" << endl;
		Sleep(1);
		exit(0);
		
	}
	else if (command == "help")
	{
		cout << setw(20) << "COMMAND" << setw(40) << "SYNTAX" << setw(60) << "USE" << endl;
		cout << setw(20) << "exit" << setw(40) << "exit" << setw(60) << "shut down all process and exit" << endl;
		cout << setw(20) << "date" << setw(40) << "date" << setw(60) << "to see the date today" << endl;
		cout << setw(20) << "time" << setw(40) << "time" << setw(60) << "to see the excution time" << endl;
		cout << setw(20) << "clear" << setw(40) << "clear" << setw(60) << "to clear screen and history" << endl;
		cout << setw(20) << "history" << setw(40) << "history" << setw(60) << "to see history of command" << endl;
		cout << setw(20) << "dir" << setw(40) << "dir" << setw(60) << "to see current director" << endl;
		cout << setw(20) << "list" << setw(40) << "list" << setw(60) << "to see list of process" << endl;
		cout << setw(20) << "kill_all" << setw(40) << "kill_all" << setw(60) << "to kill all process" << endl;
		cout << setw(20) << "run_background" << setw(40) << "run_background  (path to file exe)" << setw(60) << "to execute file exe in background mode" << endl;
		cout << setw(20) << "run_foreground" << setw(40) << "run_foreground  (path to file exe)" << setw(60) << "to execute file exe in foreground mode" << endl;
		cout << setw(20) << "run_bat" << setw(40) << "run_bat  (path to file bat)" << setw(60) << "to execute file bat" << endl;
		cout << setw(20) << "save" << setw(40) << "save   (path to file bat)" << setw(60) << "save command to file bat" << endl;
		cout << setw(20) << "kill" << setw(40) << "kill  (id of process)" << setw(60) << "to kill process with input id value" << endl;
		cout << setw(20) << "stop" << setw(40) << "stop  (id of process)" << setw(60) << "to stop process with input id value" << endl;
		cout << setw(20) << "resume" << setw(40) << "resume  (id of process)" << setw(60) << "to resume process with input id value" << endl;
		cout << setw(20) << "cd" << setw(40) << "cd  (path) " << setw(60) << "set currently directory to (path)" << endl;
		cout << setw(20) << "add_env_var" << setw(40) << "add_env_var (var name) (value) " << setw(60) << "add (value) to environment variable" << endl;
		cout << setw(20) << "del_env_var" << setw(40) << "del_env_var (var name) " << setw(60) << "delete environment has (var name)" << endl;
		cout << setw(20) << "read_env_var" << setw(40) << "read_env_var (var name) " << setw(60) << "see value of environment has (var name)" << endl;
	}
	else if (command == "date")
	{
		date();
	}
	else if (command == "time")
	{
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << setw(10) << duration.count() / (1e3) << " ms" << endl;
	}
	else if (command == "clear")
	{
		history.clear();
		system("cls");
	}
	else if (command == "dir")
	{
		listOfCurrent();
	}
	else if (command == "run_background")
	{
		openProcessInBackGround(target1);
	}
	else if (command == "run_foreground")
	{
		openProcessInForeGround(target1);
	}
	else if (command == "list")
	{
		listProcess();
	}
	else if (command == "run_bat")
	{
		ifstream file(target1);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				getCommandID(line);
			}
		}
		else
		{
			cout << "File " << s << " do not exist in this directory\n";
		}
		file.close();
	}
	else if (command == "stop")
	{
		if (!isNumber(target1))
		{
			cout << "INPUT PROPERLY VALU OF PROCESS ID" << endl;
			return;
		}
		stopProcessID(stoi(target1));
	}
	else if (command == "resume")
	{
		if (!isNumber(target1))
		{
			cout << "INPUT PROPERLY VALU OF PROCESS ID" << endl;
			return;
		}
		resumeProcessID(stoi(target1));
	}
	else if (command == "kill")
	{
		if (!isNumber(target1))
		{
			cout << "INPUT PROPERLY VALU OF PROCESS ID" << endl;
			return;
		}
		killProcessID(stoi(target1));
	}
	else if (command == "kill_all")
	{
		killAll();
	}
	else if (command == "add_env_var")
	{
		char char_array[10000];
		strcpy_s(char_array, target2.c_str());
		add_env(target1, char_array);

	}
	else if (command == "del_env_var")
	{
		del_env(target1);
	}
	else if (command == "read_env_var")
	{
		read_env(target1);
	}
	else if (command == "cd")
	{
		cd(target1);
	}
	else if (command == "save")
	{
		for (auto s : history)
		{
			ofstream file(target1);
			file << s;
			file.close();
		}
	}
	else if (command == "history")
	{
	for (auto s : history)
	{
		cout <<"  >>" << s << endl;
	}
	}
	else 
	{
		cout << "wrong command " << endl << "type " << '"' << "help" << '"' << " to see list of command" << endl;
	}
	history.push_back(s);
	command.clear();
	target1.clear();
	target2.clear();
	return ;
}