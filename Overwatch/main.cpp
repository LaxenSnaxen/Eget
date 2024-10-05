#include <iostream>
#include <map>
#include <string>
#include <list>
using namespace std;

class hero
{
    public:
        string name;
        string role;
        string poke;
        string rush;
        string dive;
        string defenceOrOffense;

        map<string, string> playStyle = {{"Poke", poke}, {"Rush", rush,}, {"Dive", dive}, {"Preferred direction of attack", defenceOrOffense}} ;

        hero(string name, string role, string poke, string rush, string dive, string defenceOrOffense) : name(name), role(role), poke(poke), rush(rush), dive(dive), defenceOrOffense(defenceOrOffense)
            {};
        
        void info()
            {
                cout << "Name: " << name << endl;
                cout << "Role: " << role << endl;
                cout << "Poke: " << playStyle["Poke"] << endl;
                cout << "Rush: " << playStyle["Rush"] << endl;
                cout << "Dive: " << playStyle["Dive"] << endl;
                cout << "Preferred pattern of attack: " << playStyle["Preferred direction of attack"] << endl;
            }
};

    /*
    Class   Name            Name                Role            Poke            Dive            Rush            Preferred direction of attack
    */
    hero    ana             ("Ana",             "Flex Support", "Playable",     "Compatible",   "Playable",     "Equal  ");
    hero    ashe            ("Ashe",            "Main DPS",  "Compatible",   "Incompatible", "Incompatible",    "Defense");
    hero    baptiste        ("Baptiste",        "Flex Support", "Compatible",   "Playable",     "Compatible",   "Equal  ");
    hero    bastion         ("Bastion",         "Main DPS",     "Playable",     "Incompatible", "Compatible",   "Offense");
    hero    brigitte        ("Brigitte",        "Main Support", "Incompatible", "Playable",     "Compatible",   "Offense");
    hero    dva             ("D.Va",            "Tank",         "Incompatible", "Compatible",   "Playable",     "Offense");         
    hero    doomfist        ("Doomfist",        "Tank",         "Counter",      "Compatible",   "Incompatible", "Offense");     
    hero    echo            ("Echo",            "Flex DPS",     "Playable",     "Compatible",   "Counter",      "Offense"); 
    hero    genji           ("Genji",           "Flex DPS",     "Counter",      "Compatible",   "Playable",     "Offense"); 
    hero    hanzo           ("Hanzo",           "Main DPS",     "Compatible",   "Incompatible", "Playable",     "Defense"); 
    hero    illari          ("Illari",          "Main Support", "Playable",     "Playable",     "Compatible",   "Defense"); 
    hero    junkerQueen     ("Junker Queen",    "Tank",         "Incompatible", "Playable",     "Compatible",   "Offense");     
    hero    junkrat         ("Junkrat",         "Flex DPS",     "Counter",      "Counter",      "Playable",     "Equal  "); 
    hero    juno            ("Juno",            "Flex Support", "Playable",     "Compatible",   "Compatible",   "Offense");
    hero    kiriko          ("Kiriko",          "Flex Support", "Incompatible", "Compatible",   "Playable",     "Offense"); 
    hero    lifeweaver      ("Lifeweaver",      "Main Support", "Compatible",   "Counter",      "Incompatible", "Defense");     
    hero    lucio           ("Lucio",           "Main Support", "Incompatible", "Playable",     "Compatible",   "Offense"); 
    hero    mauga           ("Mauga",           "Tank",         "Playable",     "Incompatible", "Compatible",   "Offense"); 
    hero    mcree           ("Mcree",           "Main DPS",     "Playable",     "Playable",     "Compatible",   "Offense"); 
    hero    mei             ("Mei",             "Flex",         "Playable",     "Incompatible", "Compatible",   "Defense");
    hero    mercy           ("Mercy",           "Main Support", "Compatible",   "Playable",     "Incompatible", "Equal  "); 
    hero    moira           ("Moira",           "Flex Support", "Incompatible", "Playable",     "Compatible",   "Offense"); 
    hero    orisa           ("Orisa",           "Tank",         "Playable",     "Playable",     "Playable",     "Offense"); 
    hero    pharah          ("Pharah",          "Flex DPS",     "Compatible",   "Incompatible", "Counter",      "Equal  "); 
    hero    ramattra        ("Ramattra",        "Tank",         "Playable",     "Counter",      "Compatible",   "Equal  ");     
    hero    reaper          ("Reaper",          "Main DPS",     "Incompatible", "Compatible",   "Compatible",   "Offense"); 
    hero    reinhardt       ("Reinhardt",       "Tank",         "Incompatible", "Playable",     "Compatible",   "Defense");     
    hero    roadhog         ("Roadhog",         "Tank",         "Playable",     "Incompatible", "Compatible",   "Offense"); 
    hero    sigma           ("Sigma",           "Tank",         "Compatible",   "Incompatible", "Playable",     "Equal  "); 
    hero    sojourn         ("Sojourn",         "Main DPS",     "Playable",     "Playable",     "Playable",     "Offense"); 
    hero    soldier         ("Soldier",         "Main DPS",     "Playable",     "Incompatible", "Playable",     "Offense"); 
    hero    sombra          ("Sombra",          "Main DPS",     "Counter",      "Compatible",   "Incompatible", "Offense"); 
    hero    symmetra        ("Symmetra",        "Main DPS",     "Playable",     "Incompatible", "Compatible",   "Equal  ");     
    hero    torbjorn        ("Torbjörn",        "Flex DPS",     "Compatible",   "Counter",      "Playable",     "Defense");     
    hero    tracer          ("Tracer",          "Flex DPS",     "Counter",      "Compatible",   "Playable",     "Offense"); 
    hero    venture         ("Venture",         "Flex DPS",     "Incompatible", "Compatible",   "Compatible",   "Offense"); 
    hero    widowmaker      ("Widowmaker",      "Main DPS",     "Compatible",   "Incompatible", "Incompatible", "Defense");     
    hero    winston         ("Winston",         "Tank",         "Incompatible", "Compatible",   "Playable",     "Offense"); 
    hero    wreckingBall    ("Wrecking Ball",   "Tank",         "Counter",      "Compatible",   "Incompatible", "Offense");       
    hero    zarya           ("Zarya",           "Tank",         "Incompatible", "Playable",     "Compatible",   "Offense"); 
    hero    zenyatta        ("Zenyatta",        "Flex Support", "Compatible",   "Playable",     "Incompatible", "Equal  ");     
    
    list <hero> tank =     {dva, doomfist, junkerQueen, mauga, orisa, ramattra, reinhardt, roadhog, sigma, winston, wreckingBall, zarya};
    list <hero> dps =      {ashe, bastion, echo, genji, hanzo, junkrat, mcree, mei, pharah, reaper, sojourn, soldier, sombra, symmetra, torbjorn, tracer, venture, widowmaker};
    list <hero> support =  {ana, baptiste, brigitte, illari, juno, kiriko, lifeweaver, lucio, mercy, moira, zenyatta};

//void getHeroes(string role, string playStyle = "None")
//    {
//        map<string, hero> heroClass = {{"Tank", tank}, {"DPS", dps}, {"Support", support}};
//
//        if (role == "Tank")
//        {
//            playStyle = "None";
//        }
//        if (playStyle == "None")
//        {
//            for (int hero = 0; hero < size(heroClass[role]); hero++)
//            {
//                list[hero].info();
//                cout << endl;
//            }
//        }
//        else
//        {
//
//        }
//    }

int main()
{
    map<string, hero> heroClass = {{"Tank", tank}, {"DPS", dps}, {"Support", support}};
    //getHeroes("Tank");
    cout << heroClass["Tank"] << endl;
    cin.get();
}