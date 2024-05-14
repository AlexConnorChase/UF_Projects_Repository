#include <iostream>
#include <iomanip>
#include <set>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//Website Object
class Website{
private:
    string name;
    float outDegree;
    float arith;
    float rank;
    float temp;
    vector<string> pointedFrom;
public:
    explicit Website(string wName);
    void insertSite(string site);
    void plusSite();
    void printSite();
    float getArith();
    void changeRank(float val);
    void changeArith();
    void changeTemp(map<string,Website> w);
};

//Construct Website Timing O(1)
Website::Website(string wName) {
    this->name = wName;
    this->outDegree = 0.0;
    this->arith = 0.0;
    this->rank = 0.0;
    this->temp = 0.0;
}

//Print Website Timing O(1)
void Website::printSite() {
    cout << name << " " << setprecision(2) << fixed << this->rank << endl;
}

//Get Arith for math functions, Timing O(1)
float Website::getArith() {
    return this->arith;
}

//Insert site into pointsTo vector, Timing O(1)
void Website::insertSite(string site) {
    this->pointedFrom.push_back(site);
}

//Increase Out Degree for arithmetic, Timing O(1)
void Website::plusSite() {
    this->outDegree += 1.0;
}

//Change Website rank, Timing O(1);
void Website::changeRank(float val) {
    this->rank = val;
}

//Change rank / outdegree, Timing O(1)
void Website::changeArith() {
    this->arith = (this->rank/ this->outDegree);
}

//Change Temp to update pageRank
void Website::changeTemp(map<string, Website> w) { //Timing O(v)
    this->temp = 0.0;
    for(int i = 0; i < this->pointedFrom.size(); i++) { //Timing O(v) where v = number of vertices/ pointing websites
            this->temp += w.at(pointedFrom.at(i)).getArith();
    }
    this->rank = temp;
}

//Main function, Timing O(mn * v(n))
int main() { //Timing: O(nlogn) (for insertion) + O(nlogn) (for sort) + O(mn*v(n)) (for arithmetic) + O(n) (for print))
    int numLines, power;
    string from, to;
    map<string, Website> sites; //Store website by name
    set<string> sSet; // Set used to hold ONE of each website

    //Get Input
    cin >> numLines; //Gives us n
    cin >> power; // Gives us m

    //Insertion
    for (int i = 0; i < numLines; i++) { //Timing O(4 * nlogn)
        cin >> from;
        cin >> to;

        //Make new website for "to" and "from" site, if the site already exists, emplace ignores it and "from" is added in "to"'s pointer list
        sSet.emplace(from);
        sSet.emplace(to);
        Website w = Website(to);
        Website w1 = Website(from);
        sites.emplace(to, w);
        sites.emplace(from, w1);
        sites.at(to).insertSite(from);
        sites.at(from).plusSite();
    }

    //Sort Sites, Timing O(nlogn)
    vector<string> v(sSet.begin(), sSet.end()); //Vector to sort alphabetically
    sort(v.begin(),v.end());

    //Arithmetic, Timing O(mn* v(n)) Worst O(mn^2)
    for(int i = 0; i < v.size(); i++){ //Start with initial rankings, Timing O(n)
        sites.at(v.at(i)).changeRank(1.0/v.size());
    }
    for(int i = 1; i < power; i++){
        //Do arithmetic here
        auto it = sites.begin();
        //Change Arith variable, where Arith = pageRank / outDegree, Timing O(n)
        while(it != sites.end()){
            it->second.changeArith();
            it++;
        }
        it = sites.begin();
        // Go through each website, add the appropriate arith values and then updaate page rank, Timing O(n* v(n))
        // O(v(n)) v(n) = number of vertices/ pointing webstites of the given website
        while(it != sites.end()){
            it->second.changeTemp(sites);
            it++;
        }
    }

    //Print Sites, Timing O(n)
    for(int i = 0; i < v.size(); i++){
        sites.at(v.at(i)).printSite();
    }

    return 0;
}