#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class Person // класс - человек
{
public:
    string first_name; // поля класса
    string second_name;
    string third_name;
    string full_name;
    unsigned int age;
    unsigned int height;

    Person(string first_name, string second_name, string third_name, unsigned int age,
        unsigned int height) // конструктор класса
    {
        this->first_name = first_name; // инициализация членов класса
        this->second_name = second_name;
        this->third_name = third_name;
        full_name = first_name + " " + second_name + " " + third_name;
        this->age = age;
        this->height = height;
    }

};


class FootballPlayer : public Person // класс футбольный игрок, который наследуется от класса человек
{
public:
    string position;  // поля
    unsigned int transfer_price;

    FootballPlayer(string first_name, string second_name, string third_name,
        unsigned int age, unsigned int height, string position,
        unsigned int transfer_price) : Person(first_name, second_name, third_name, age, height) // конструктор текущего класса на основе класса родителя
    {
        this->position = position;
        this->transfer_price = transfer_price;
    }
};

class FootballCoach : public Person // класс футбольный тренер
{
public:
    vector<string> tactics; // вектор строк для тактик 
    unsigned short experience;

    FootballCoach(string first_name, string second_name, string third_name,
        unsigned int age, unsigned int height,
        unsigned short experience) : Person(first_name, second_name, third_name, age, height), tactics() // конструктор, плюс инициализация структуры данных типа vector для хранения списка такстик
    {
        this->experience = experience;
    }

    void AddTactic(string tactic) // метод по добавлению тренеру тактики
    {
        this->tactics.push_back(tactic);
        return;
    }
};

class TeamDetails // детали футбольной команды
{
public:
    vector<FootballPlayer> goalkeepers;
    vector<FootballPlayer> defenders;
    vector<FootballPlayer> midfielders;
    vector<FootballPlayer> forwards;
    vector<string> tactics;

    TeamDetails() : goalkeepers(), defenders(), midfielders(), forwards(), tactics() // конструктор с иницаилизацие векторов
    {
    }

};

class Team // класс - команда
{
public:
    vector<FootballPlayer> players; // все игроки
    vector<FootballPlayer> firs_eleven; // стартовый состав
    vector<FootballCoach> coaches; // тренера
    string name;
    string country;
    unsigned int tactics[4];
     
    Team(string name, string country, unsigned int tactics[4]) : players(), coaches(), firs_eleven() // конструктор
    {
        this->name = name;
        this->country = country;
        for (unsigned int i = 0; i < 4; i++)
        {
            this->tactics[i] = tactics[i];
        }
    }

    TeamDetails GetDetails() // получить детали команды 
    {
        TeamDetails this_team_details;

        for (unsigned int i = 0; i < this->players.size(); i++) // проход по списку всех игроков и сортировка их по специализации
        {
            if (players[i].position == "goalkeeper") this_team_details.goalkeepers.push_back(players[i]);
            else if (players[i].position == "defender") this_team_details.defenders.push_back(players[i]);
            else if (players[i].position == "midfielder") this_team_details.midfielders.push_back(players[i]);
            else if (players[i].position == "forward") this_team_details.forwards.push_back(players[i]);
            else continue;
        }

        for (unsigned int i = 0; i < this->coaches.size(); i++) // проход по тренерам для информации о доступных команде тактик
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

    void AddPlayer(FootballPlayer player) // метод добавления игрока в команду
    {
        this->players.push_back(player);
        return;
    }

    void AddCoach(FootballCoach coach) // метод добавления тренера в команду
    {
        this->coaches.push_back(coach);
        return;
    }

    void FEGen() // генерация стратового состава из доступных игроков
    {
        TeamDetails details = GetDetails();

        if ((details.forwards.size() < tactics[0]) || (details.midfielders.size() < tactics[1]) || (details.defenders.size() < tactics[2])
            || (details.goalkeepers.size() < tactics[3]))
        {
            cerr << "Not enough players" << endl;
            return;
        } // если не хватает игроков, то ошибка

        for (unsigned int i = 0; i < tactics[0]; i++) firs_eleven.push_back(details.forwards[i]); // добавляем игроков в стартовый состав
        for (unsigned int i = 0; i < tactics[1]; i++) firs_eleven.push_back(details.midfielders[i]);
        for (unsigned int i = 0; i < tactics[2]; i++) firs_eleven.push_back(details.defenders[i]);
        for (unsigned int i = 0; i < tactics[3]; i++) firs_eleven.push_back(details.goalkeepers[i]);

        return;
    }

};

class Match // класс матч
{
public:
    vector<Team> teams;
    vector<pair<pair<string, string>, pair<unsigned int, unsigned int>>> results; // вектор пар элементов вида (Команда - Команда) - Счет
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

    void AddResult(Team team1, Team team2, pair<unsigned int, unsigned int> result) // доабвление результата
    {
        this->results.push_back(pair<pair<string, string>, pair<unsigned int, unsigned int>>
        (pair<string, string>(team1.name, team2.name), pair<unsigned int, unsigned int>(result)));
        return;
    }

};


int main()
{
    FootballPlayer player_1("Past", "Yevhen", "Sergiyovich", 32, 186, "goalkeeper", 500000); // создание игркоков
    FootballPlayer player_2("Litovka", "Igor", "Yuriyovich", 32, 193, "goalkeeper", 200000);
    FootballPlayer player_3("Tatarenko", "Maxym", "Mykolayevich", 21, 184, "goalkeeper", 50000);
    FootballPlayer player_4("Favorov", "Denys", "Volodymyrovych", 29, 184, "defender", 900000);
    FootballPlayer player_5("Gitchenko", "Andriy", "Igorevich", 35, 188, "defender", 200000);
    FootballPlayer player_6("Mostoviy", "Andriy", "Volodymyrovych", 32, 180, "defender", 300000);
    FootballPlayer player_7("Imerekow", "Maxym", "Igorevich", 29, 190, "defender", 700000);
    FootballPlayer player_8("Konoplya", "Efim", "Dmitriievich", 20, 180, "defender", 800000);
    FootballPlayer player_9("Ermakow", "Vitaliy", "Myhailovich", 28, 186, "defender", 200000);
    FootballPlayer player_10("Tamm", "Joonas", " ", 28, 192, "defender", 300000);
    FootballPlayer player_11("Pryndeta", "Vitaliy", "Valeriyovich", 27, 196, "defender", 200000);
    FootballPlayer player_12("Kalitwintsew", "Vladyslav", "Mykolayevich", 27, 178, "midfielder", 900000);
    FootballPlayer player_13("Kartushow", "Ehor", "Olexandrovych", 29, 179, "midfielder", 700000);
    FootballPlayer player_14("Ogirya", "Vladyslav", "Leonidovych", 30, 177, "midfielder", 500000);
    FootballPlayer player_15("Kuzyk", "Orest", "Tarasovych", 25, 174, "midfielder", 400000);
    FootballPlayer player_16("Dombrovskiy", "Andriy", "Anatolievych", 24, 173, "midfielder", 400000);
    FootballPlayer player_17("Totovickiy", "Andriy", "Olexandrovych", 27, 177, "midfielder", 650000);
    FootballPlayer player_18("Arweladze", "Levan", "Giviievych", 27, 181, "midfielder", 400000);
    FootballPlayer player_19("Starenkiy", "Sergiy", "Mykolayevich", 35, 178, "midfielder", 100000);
    FootballPlayer player_20("Zapadnya", "Artur", "Volodymyrovych", 30, 183, "midfielder", 200000);
    FootballPlayer player_21("Gutsulyak", "Oleksiy", "Olexandrovych", 22, 187, "midfielder", 300000);
    FootballPlayer player_22("Shewtsow", "Ilya", "Sergiyovich", 20, 182, "midfielder", 50000);
    FootballPlayer player_23("Filipow", "Olexandr", "Olexandrovych", 27, 182, "forward", 1000000);
    FootballPlayer player_24("Hlyobas", "Dmytro", "Victorovych", 26, 178, "forward", 900000);
    FootballPlayer player_25("Budkowskiy", "Filip", "Vyacheslavovych", 28, 194, "forward", 700000);
    FootballCoach coach_1("Riabokin'", "Olexandr", "Dmitriievich", 56, 193, 20); // создание тренеров
    coach_1.AddTactic("4-2-4"); // добавление тактик тренеру


    unsigned int tactics[4] = { 1, 5, 4, 1 }; // тактика команды
    Team team_1("Desna", "Chernihiv", tactics); // создание команды
    team_1.AddPlayer(player_1); // добавление игроков в комнду
    team_1.AddPlayer(player_2);
    team_1.AddPlayer(player_3);
    team_1.AddPlayer(player_4);
    team_1.AddPlayer(player_5);
    team_1.AddPlayer(player_6);
    team_1.AddPlayer(player_7);
    team_1.AddPlayer(player_8);
    team_1.AddPlayer(player_9);
    team_1.AddPlayer(player_10);
    team_1.AddPlayer(player_11);
    team_1.AddPlayer(player_12);
    team_1.AddPlayer(player_13);
    team_1.AddPlayer(player_14);
    team_1.AddPlayer(player_15);
    team_1.AddPlayer(player_16);
    team_1.AddPlayer(player_17);
    team_1.AddPlayer(player_18);
    team_1.AddPlayer(player_19);
    team_1.AddPlayer(player_20);
    team_1.AddPlayer(player_21);
    team_1.AddPlayer(player_22);
    team_1.AddPlayer(player_23);
    team_1.AddPlayer(player_24);
    team_1.AddPlayer(player_25);

    team_1.AddCoach(coach_1); // добавление тренеров в команду

    team_1.FEGen(); // сбор стартового состава

    cout << "First eleven: " << endl; // вывод стартового состава
    for (unsigned int i = 0; i < team_1.firs_eleven.size(); i++) cout << team_1.firs_eleven[i].full_name << "--" << team_1.firs_eleven[i].position << endl;

    TeamDetails team_1_details; // детали команды
    team_1_details = team_1.GetDetails(); // получение деталей 

    cout << "Team_Name: " << team_1.name << " Country: " << team_1.country << endl; // вывод деталей
    cout << "Goalkeepers: " << team_1_details.goalkeepers.size() << endl;
    cout << "Defenders: " << team_1_details.defenders.size() << endl;
    cout << "Midfielders: " << team_1_details.midfielders.size() << endl;
    cout << "Forwards: " << team_1_details.forwards.size() << endl;
    cout << "Used tactics: " << tactics[0] << '-' << tactics[1] << '-' << tactics[2] << '-' << tactics[3] << endl;

    Match match_1; // создание матча
    Team team_2("Dinamo", "Ukraine", tactics); // создание команды
    match_1.AddTeam(team_1); // добавление команды в матч 
    match_1.AddTeam(team_2);
    match_1.AddResult(team_1, team_2, pair<unsigned int, unsigned int>(0, 1)); // добавление результатов игры

    cout << "Match: " << match_1.results[0].first.first << " vs " << match_1.results[0].first.second << " result: " // вывод информации о матче
        << match_1.results[0].second.first << ":" << match_1.results[0].second.second << endl;

    return 0;
}
