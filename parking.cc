/* 	Garrett Jennings | ZID: z1927185
	Parking Garage Assignment
	CS340 - 3
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "parking.h"
/// @param line The line read from the command line to be parsed
/// @param license The license of the car
/// @param xact_type The char that indicates what behavior is called: arrival or departure   
void get_input_vals(const std::string &line, char &xact_type, std::string &license){
        // THE BELOW CODE WAS ADAPTED FROM THE LINKED STACK OVERFLOW ARTICLE
    string copy = line;
    string delimiter = ":";

    size_t pos = 0;
    // Parse the line for xact_type, the char
    pos = copy.find(delimiter);
    xact_type = line[pos - 1];
    copy.erase(0, pos + delimiter.length());
    // Parse the line for license, the license plate string
    pos = copy.find(delimiter);
    license = copy.substr(0, pos);
}

int main(){
    garage gar;

    string line;
    while(getline(cin, line) ){ // Read input from cin line by line
        char act;
        string license;
        get_input_vals(line, act, license); // Parse values from cin

        switch(act){    // Different behavior based on user input
            case 'A' :  // Arrival
                gar.arrival(license);
                break;
            
            case 'D' :  // Departure
                gar.departure(license);
                break;
            
            default :
                cout << "\'" << act << "\': invalid action!\n";   
        }

        cout << endl;
    }
}