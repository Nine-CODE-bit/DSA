#include<bits/stdc++.h>
using namespace std;

vector<char> notes;
set<string> repeatNotes;

int main()
{
    string line;
    getline(cin, line);
    stringstream ss(line);
    string note;
    while(getline(ss, note, '-'))
    {
        if(note.empty()) continue;
        char noteName = note[0];
        int repeatCount = stoi(note.substr(1));
        for(int i=0;i<repeatCount;i++)
        {
            notes.push_back(noteName);
        }
    }
    int flag = 0;
    for(int i=0; i < notes.size() - 4; i++)
    {
        for(int j=i+1; j < notes.size() - 3; j++)
        {
            flag = 0;
            for(int k=0; k < 4; k++)
            {
                if(notes[i+k] != notes[j+k])
                {
                    flag=1;
                    break;
                }
            }
            if(flag == 0)
            {
                string repeatNote = "";
                for(int k=0; k < 4; k++)
                {
                    repeatNote += notes[i+k];
                }
                repeatNotes.insert(repeatNote);
                break;
            }
        }
    }
    for(const string& note : repeatNotes)
    {
        cout << note << endl;
    }
    return 0;
}