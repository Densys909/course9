#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class Person
{
public:
    string first_name;
    string second_name;
    string third_name;
    string full_name;
    unsigned int age;
    unsigned int height;

    Person(string first_name, string second_name, string third_name, unsigned int age,
        unsigned int height)
    {
        this->first_name = first_name;
        this->second_name = second_name;
        this->third_name = third_name;
        full_name = first_name + " " + second_name + " " + third_name;
        this->age = age;
        this->height = height;
    }

};


class FootballPlayer : public Person
{
public:
    string position;
    unsigned int transfer_price;

    FootballPlayer(string first_name, string second_name, string third_name,
        unsigned int age, unsigned int height, string position,
        unsigned int transfer_price) : Person(first_name, second_name, third_name, age, height)
    {
        this->position = position;
        this->transfer_price = transfer_price;
    }
};

class FootballCoach : public Person
{
public:
    vector<string> tactics;
    unsigned short experience;

    FootballCoach(string first_name, string second_name, string third_name,
        unsigned int age, unsigned int height,
        unsigned short experience) : Person(first_name, second_name, third_name, age, height), tactics()
    {
        this->experience = experience;
    }

    void AddTactic(string tactic)
    {
        this->tactics.push_back(tactic);
        return;
    }
};

class TeamDetails
{
public:
    vector<FootballPlayer> goalkeepers;
    vector<FootballPlayer> defenders;
    vector<FootballPlayer> midfielders;
    vector<FootballPlayer> forwards;
    vector<string> tactics;

    TeamDetails() : goalkeepers(), defenders(), midfielders(), forwards(), tactics()
    {
    }

    /* void operator=(TeamDetails details)
     {
         this->goalkeepers = details.goalkeepers;
         this->defenders = details.defenders;
         this->midfielders = details.midfielders;
         this->forwards = details.forwards;
         this->tactics = details.tactics;
     }*/
};

class Team
{
public:
    vector<FootballPlayer> players;
    vector<FootballPlayer> firs_eleven;
    vector<FootballCoach> coaches;
    string name;
    string country;
    unsigned int tactics[4];

    Team(string name, string country, unsigned int tactics[4]) : players(), coaches(), firs_eleven()
    {
        this->name = name;
        this->country = country;
        for (unsigned int i = 0; i < 4; i++)
        {
            this->tactics[i] = tactics[i];
        }
    }

    TeamDetails GetDetails()
    {
        TeamDetails this_team_details;

        for (unsigned int i = 0; i < this->players.size(); i++)
        {
            if (players[i].position == "goalkeeper") this_team_details.goalkeepers.push_back(players[i]);
            else if (players[i].position == "defender") this_team_details.defenders.push_back(players[i]);
            else if (players[i].position == "midfielder") this_team_details.midfielders.push_back(players[i]);
            else if (players[i].position == "forward") this_team_details.forwards.push_back(players[i]);
            else continue;
        }

        for (unsigned int i = 0; i < this->coaches.size(); i++)
        {
            for (unsigned int j = 0; j < coaches[i].tactics.size(); j++)
            {
                if (find(this_team_details.tactics.begin(), this_team_details.tactics.end(), coaches[i].tactics[j])
                    != this_team_details.tactics.end()) continue;
                else this_team_details.tactics.push_back(coaches[i].tactics[j]);
            }
        }

        return this_team_details;

    }

    void AddPlayer(FootballPlayer player)
    {
        this->players.push_back(player);
        return;
    }

    void AddCoach(FootballCoach coach)
    {
        this->coaches.push_back(coach);
        return;
    }

    void FEGen()
    {
        TeamDetails details = GetDetails();

        if ((details.forwards.size() < tactics[0]) || (details.midfielders.size() < tactics[1]) || (details.defenders.size() < tactics[2])
            || (details.goalkeepers.size() < tactics[3]))
        {
            cout << "Not enough players" << endl;
            return;
        }

        for (unsigned int i = 0; i < tactics[0]; i++) firs_eleven.push_back(details.forwards[i]);
        for (unsigned int i = 0; i < tactics[1]; i++) firs_eleven.push_back(details.midfielders[i]);
        for (unsigned int i = 0; i < tactics[2]; i++) firs_eleven.push_back(details.defenders[i]);
        for (unsigned int i = 0; i < tactics[3]; i++) firs_eleven.push_back(details.goalkeepers[i]);

        return;
    }

};

class Match
{
public:
    vector<Team> teams;
    vector<pair<pair<string, string>, pair<unsigned int, unsigned int>>> results;
    vector<pair<string, TeamDetails>> details;

    Match() : teams(), results(), details()
    {
    }

    void AddTeam(Team team)
    {
        this->teams.push_back(team);
        this->details.push_back(pair<string, TeamDetails>(team.name, team.GetDetails()));
        return;
    }

    void AddResult(Team team1, Team team2, pair<unsigned int, unsigned int> result)
    {
        this->results.push_back(pair<pair<string, string>, pair<unsigned int, unsigned int>>
        (pair<string, string>(team1.name, team2.name), pair<unsigned int, unsigned int>(result)));
        return;
    }

};


int main()
{
    FootballPlayer player_1("Ivanov", "Ivan", "Ivanovich", 22, 180, "goalkeeper", 10);
    FootballPlayer player_2("Ivanov", "Ivan", "Petrovich", 23, 181, "defender", 11);
    FootballPlayer player_3("Ivanov", "Ivan", "Vasilevich", 24, 182, "midfielder", 12);
    FootballPlayer player_4("Ivanov", "Ivan", "Sergeevich", 25, 183, "forward", 13);
    FootballPlayer player_5("Ivanov", "Ivan", "Nikitich", 26, 184, "forward", 14);

    FootballCoach coach_1("Sidorov", "Vasiliy", "Ivanovich", 22, 180, 5);
    coach_1.AddTactic("4-4-1");
    FootballCoach coach_2("Sidorov", "Vasiliy", "Petrovich", 23, 181, 6);
    coach_2.AddTactic("4-4-2");


    unsigned int tactics[4] = { 2, 1, 1, 1 };
    Team team_1("Desna", "Chernihiv", tactics);
    team_1.AddPlayer(player_1);
    team_1.AddPlayer(player_2);
    team_1.AddPlayer(player_3);
    team_1.AddPlayer(player_4);
    team_1.AddPlayer(player_5);

    team_1.AddCoach(coach_1);
    team_1.AddCoach(coach_2);

    team_1.FEGen();

    cout << "First eleven: " << endl;
    for (unsigned int i = 0; i < team_1.firs_eleven.size(); i++) cout << team_1.firs_eleven[i].full_name << "--" << team_1.firs_eleven[i].position << endl;

    TeamDetails team_1_details;
    team_1_details = team_1.GetDetails();

    cout << "Team_Name: " << team_1.name << " Country: " << team_1.country << endl;
    cout << "Goalkeepers: " << team_1_details.goalkeepers[0].full_name << endl;
    cout << "Defenders: " << team_1_details.defenders[0].full_name << endl;
    cout << "Midfielders: " << team_1_details.midfielders[0].full_name << endl;
    cout << "Forwards: " << team_1_details.forwards[0].full_name << " , " << team_1_details.forwards[1].full_name << endl;
    cout << "Used tactics: " << tactics[0] << '-' << tactics[1] << '-' << tactics[2] << '-' << tactics[3] << endl;

    Match match_1;
    Team team_2("Dinamo", "Kyiw", tactics);
    match_1.AddTeam(team_1);
    match_1.AddTeam(team_2);
    match_1.AddResult(team_1, team_2, pair<unsigned int, unsigned int>(0, 1));

    cout << "Match: " << match_1.results[0].first.first << " vs " << match_1.results[0].first.second << " result: "
        << match_1.results[0].second.first << ":" << match_1.results[0].second.second << endl;

    return 0;
}
