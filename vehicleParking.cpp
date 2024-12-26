#include<iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <sstream>
#include <unordered_map>
#include <chrono> 

class Vehicle {
  private:
    int rowNum;
    int spotNum; //or we can say column number
    std::chrono::time_point<std::chrono::system_clock> parkingStartTime;
    std::chrono::time_point<std::chrono::system_clock> parkingEndTime;
  
  public:
    Vehicle(){
        rowNum = -1;
        spotNum = -1;
    }
    
    void occupySpot(int row, int col){
        rowNum = row;
        spotNum = col;
        parkingStartTime = std::chrono::system_clock::now();
    }
    
    void vacateSpot(){
        rowNum = -1;
        spotNum = -1;
    }
    
    int calculateParkingDurationInHours() {
        parkingEndTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = parkingEndTime - parkingStartTime;
        double timeInHour = elapsed_seconds.count();
        
        //  use parking starttime and currentTime
        return timeInHour;
    }
    
    virtual double calculateParkingFee() = 0;
    virtual string getType() = 0;
};


class Car : public Vehicle{
    public:
        string getType() {
            return "Car";
        }
    
        double calculateParkingFee(){
            return 5*calculateParkingDurationInHours();
        }
};

class Bike : public Vehicle{
    public:
        string getType() {
            return "Bike";
        }
    
        double calculateParkingFee(){
            return 2*calculateParkingDurationInHours();
        }
};

class Parking {
    private:
        int rows;
        int spotsPerRow;
        vector<vector<Vehicle*>> grid;
        
    public:
    
        void create(int r,int c){
            rows = r;
            spotsPerRow = c;
            
            grid.resize(r);
            for(int i=0; i<r; i++){
                grid[i].resize(c);
            }
        }
        
        pair<int,int> findVacantSpace(){
            
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < spotsPerRow; j++){
                    if(grid[i][j]==nullptr){
                        return {i,j};
                    }
                }
            }
            
            //if no vacant spot
            return {-1,-1};
        }
        
        void parkVehicle(Vehicle* v){
            pair<int,int> vacantSpace = findVacantSpace();
            
            if(vacantSpace.first==-1){
                cout<<"No parking Space Available"<<endl;
                return;
            }
            
            int row = vacantSpace.first, col = vacantSpace.second;
            v->occupySpot(row, col);
            grid[row][col] = v;
            cout<<"Vehicle parked at ("<<row<<", "<<col<<")"<<endl;
        }
        
        pair<int,int> getVehiclePosition(Vehicle *v){
            pair<int,int> position;
            
            for(int i=0;i<rows;i++){
                for(int j=0;j<spotsPerRow;j++){
                    if(grid[i][j]!= nullptr && grid[i][j]==v){
                        position = {i,j};
                        return position;
                    }
                }
            }
            
            position = {-1,-1};
            return position;
        }
        
        void removeVehicle(Vehicle *v){
            pair<int,int> position = getVehiclePosition(v);
            if(position.first==-1){
                cout<<"No such Vehicle is parked in parking !"<<endl;
                return;
            }
            
            int row = position.first;
            int col = position.second;
            grid[row][col] = nullptr;
            double parkingCharge = v->calculateParkingFee();
            cout<<"Please pay parking fees : "<<parkingCharge<<endl;
            v->vacateSpot();
        }
};

int main(){
    Vehicle *car = new Car();
    Vehicle *bike = new Bike();
    
    Parking p;
    p.create(3,2);
    pair<int,int> vacantSpace = p.findVacantSpace();
    p.parkVehicle(car);
    p.parkVehicle(bike);
    p.removeVehicle(bike);
    
    return 0;
}
