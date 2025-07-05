#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<list>

using namespace std;

class eventManage{
    private:
    unordered_map<string, vector<pair<string, string>>> events;  // <date, list of <time, title>>

    public:

    void addToEvents(){
        string date;
        string time;
        string title;

        cout<<"give the date of event(for eg. 'DD-MM-YYYY'): ";
        cin>> date;

        cout<<"provide the time of event(for eg. '08:30' , '23:30'): ";
        cin>> time;
        
        cin.ignore();   // ignores the line left by 'time'

        cout<<"enter title of the event: ";
        getline(cin, title);
        
        events[date].push_back(make_pair(time, title));

        //sort events by time
        sort(events[date].begin(), events[date].end());

        cout<<"Event added."<<endl;
        cout<<endl;
    }


    void deleteAnEvent() {
        string date;
        string time;
        string title;

        cout << "give the date of event(for eg. 'DD-MM-YYYY') that you want to delete / update: ";
        cin >> date;

        cout << "provide the time of event(for eg. '08:30' , '23:30') that you want to delete / update: ";
        cin >> time;

        cin.ignore();  // Clear newline left by previous cin

        cout << "enter title of the event that you want to delete / update: ";
        getline(cin, title);

        auto it = events.find(date);

        if(it == events.end()){
            cout<< "No events found on this date."<<endl;
            return;
        }
        
        auto& eventList = it->second;
        bool found = false;

        for (auto entry = eventList.begin(); entry != eventList.end(); ) {
            if (entry->first == time && entry->second == title) {
                entry = eventList.erase(entry);  // erase returns the next iterator
                found = true;
                cout<<"Event deleted successfully."<<endl;
                cout<<endl;
                break; // exit loop as event found and deleted

            } else {
                ++entry;
            }
        }

        if (eventList.empty()) {
            events.erase(date);
        }
            
        if (found == false) {
            cout << "Event not found." << endl;
            cout<<endl;
        }
    }
    

    void updateAnEvent() {

        deleteAnEvent();    // reusing the logic of deletion

        cout<<"provide the details that you want to update: "<<endl;
        addToEvents();     // reusing the logic of addition
    }


    void viewEvents() {
        string date;
        
        cout << "give the date(for eg. 'DD-MM-YYYY') whose events you want to view: ";
        cin >> date;

        auto it = events.find(date);

        if(it == events.end()){
            cout<< "No events found on this date."<<endl;
            return;
        }

        auto& eventList = it->second;
        cout<< date<<":"<<endl;

        for(auto entry = eventList.begin(); entry != eventList.end(); entry++){
            
            cout<< entry->first << " -> "<< entry->second <<endl;
        }
        cout<<endl;
    }
};


void enterCommands(eventManage &section){
    
     while (true) {
                string command;
                cout << "Choose an action: add / delete / update / view / exit: ";
                cin >> command;
                cout<<endl;
                transform(command.begin(), command.end(), command.begin(), ::tolower);

                if (command == "add") {
                    section.addToEvents();
                }
                else if (command == "delete") {
                    section.deleteAnEvent();
                }
                else if (command == "update") {
                    section.updateAnEvent();
                }
                else if (command == "view") {
                    section.viewEvents();
                }
                else if (command == "exit") {
                    break;
                }
                else {
                    cout << "Invalid action. Try again."<<endl;
                }
            }

}


int main(){
    
    eventManage office;
    eventManage home;
    eventManage trading;
    
    while(true){

        string section;
        cout<< "choose a section from: trading / office / home / exit: ";
        cin>> section;
        cout<<endl;
        transform(section.begin(), section.end(), section.begin(), ::tolower);

        if(section == "office"){
            enterCommands(office);
        }

        else if(section == "home"){
            enterCommands(home);            
        }

        else if(section == "trading"){
            enterCommands(trading);            
        }

        else if(section == "exit"){
            break;
        }

        else{
            cout<<"Invalid section. Try again."<<endl;
        }

    }

    return 0;
}
