#ifndef H_PARKING
#define H_PARKING

#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <stack>  

using namespace std;

class car
{
public:
    car(int id, const std::string &license) : id(id), license(license) {}

    /// Call this to increment the numbner of times the car has been moved.
    void move() { ++num_moves; }

    /// @return the number of times that the car has been moved.
    int get_num_moves() const { return num_moves; }

    /// @return A reference to the license for this car.
    const std::string &get_license() const { return license; }

    /// Overload the << so this can print itself.
    friend std::ostream& operator<<(std::ostream& lhs, const car& rhs)
    {
        lhs << "Car " << rhs.id << " with license plate \"" << rhs.license << "\"";
        return lhs;
    }

private:
    int id;                 ///< The ID number for this car (assigned by the garage)
    std::string license;    ///< license plate of this car.
    int num_moves = {0};    ///< how many times the car was moved within the garage.
};

class garage
{
public:
        garage(size_t limit = 10) : parking_lot_limit(limit) {}

        // Function used for testing that output the current state of the deque
        void printLot(){
            cout << endl << endl;
            for (car c: parking_lot){
                cout << "\t\t " << c << endl;
            }
            cout << endl << endl;
        }

        /// @param license The license of the car that has arrived.                                                           
        void arrival(const std::string &license){
            // Create a car with an incremented id
            car ocar(next_car_id++, license);

            cout << ocar << " has arrived.\n";
            // If the parking lot is full
            if (parking_lot.size() >= parking_lot_limit) {
                cout << "    But the garage is full!\n";
            }
            else { // If the parking lot is not full, add the car to the back of the deque
                parking_lot.push_back(ocar);
            }

            // printLot();
        }

        /// @param license The license of the car that has departed.                                                          
        void departure(const std::string &license){
            // Compare each license plate in the parking lot to the parameter
            deque<car>::iterator ptr;
            for (ptr = parking_lot.begin(); ptr != parking_lot.end(); ptr++){
                if (ptr->get_license() == license){   // If there is a match...
                    stack<car> cstack;

                    // Old Version of code -->
                            // Iterate through parking lot, removing elements from the back
                            // for (int j = parking_lot.size() - 1; j >= i; j--){

                    // Iterate through parking lot, removing elements from the front
                    for (deque<car>::iterator ptr2 = parking_lot.begin(); ptr2 != ptr + 1; ptr2++){
                        // 1. Call the move function on the car that is to be moved
                        // 2. Push the car into the stack
                        // 3. Remove the car from the deque
                        ptr2->move();
                        cstack.push(move(*ptr2));
                        parking_lot.pop_front();
                    }

                    // No need to increment moves for the to be removed car, as it was already moved to the stack
                    cout << cstack.top();
                    cout << " has departed," << endl; 
                    int numMoves = cstack.top().get_num_moves();
                    cout << "    car was moved " << numMoves << " time";
                    string mvplural = (numMoves == 1)? "" : "s";
                    cout << mvplural;
                    cout << " in the garage.\n";

                    cstack.pop();

                    for (unsigned int j = 0; j < cstack.size(); j+=0){ // j is += 0 BECAUSE THE SIZE OF CSTACK IS REDUCED WHEN pop() IS CALLED
                        parking_lot.push_front(move(cstack.top()));
                        cstack.pop();
                    }

                    // printLot();

                    return;
                }
            }
            // If the for loop terminates, there was no match to the license plate
            cout << "No car with license plate \"" << license << "\" is in the garage.\n";
        }

private:
        int next_car_id = { 1 };
        std::deque<car> parking_lot;
        size_t parking_lot_limit;
};

#endif