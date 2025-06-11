#include<bits/stdc++.h>
using namespace std;

string notes,Notes;
int k,num,Size=0,flag=0;
char note;

class Stack{
    private:
        int top;
        char* arr;
    public:
        Stack(int size){
            arr = new char[size];
            top = -1;
        }
        int pop(){
            if (top == -1){
                return -1;
            }
            return arr[top--];
        }
        void push(int x){
            arr[++top] = x;
        }
        int size(){
            return top + 1;
        }
        int top_element(){
            if (top == -1){
                return -1;
            }
            return arr[top];
        }
        void empty(){
            top = -1;
        }
};

int main()
{
    cin>>notes>> k;
    for(int i=0;i<notes.size();i++)
    {
        if(notes[i]>='A' && notes[i]<='G')
        {
            note = notes[i++];
            num = notes[i++] - '0';
            if(num > 9 || num < 1)
            {
                cout<<-1;
                return 0;
            }
            Notes.append(num, note);
            Size+= num;
            if(notes[i]!='-' && i<notes.size())
            {
                cout<<-1;
                return 0;
            }
        }
        else
        {
            cout<<-1;
            return 0;
        }
    }
    Stack s(Size);
    Stack buffer(k);
    num=0;
    while(cin>>notes)
    {
        num++;
        for(int i=0;i<notes.size();i++)
        {
            if(notes[i]<'A' || notes[i]>'G')
            {
                cout<<-1;
                return 0;
            }
        }
        int location_a = 0,location_b = 0;
        for(location_a=0;location_a<Size;location_a++)
        {
            s.push(Notes[location_a]);
            flag=0;
            while(s.top_element()==notes[location_b] && flag==0)
            {
                for(int i=0;i<k;i++)
                {
                    if(s.size()==0)
                    {
                        flag=1;
                        break;
                    }
                    note=s.pop();
                    buffer.push(note);
                    if(note != notes[location_b++])
                    {
                        flag=1;
                        while(buffer.size()>0)
                        {
                            location_b--;
                            note=buffer.pop();
                            s.push(note);
                        }
                        break;
                    }
                }
                buffer.empty();
            }
        }
        if(location_b!=notes.size())
        {
            cout<<"false"<<endl;
        }
        else
        {
            cout<<"true"<<endl;
        }
        s.empty();
    }
    if(num==0)
    {
        cout<<-1;
    }
    return 0;
}