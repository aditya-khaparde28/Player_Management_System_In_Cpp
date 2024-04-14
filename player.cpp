#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Player {
private:
    int jerseyNumber;
    string playerName;
    int runs;
    int wickets;
    int matchesPlayed;

public:
    // Constructors
    Player() : jerseyNumber(0), playerName(""), runs(0), wickets(0), matchesPlayed(0) {}
    Player(int jersey, const string& name, int runsScored, int wicketsTaken, int matches)
        : jerseyNumber(jersey), playerName(name), runs(runsScored), wickets(wicketsTaken), matchesPlayed(matches) {}

    // Accessors
    int getJerseyNumber() const { return jerseyNumber; }
    string getPlayerName() const { return playerName; }
    int getRuns() const { return runs; }
    int getWickets() const { return wickets; }
    int getMatchesPlayed() const { return matchesPlayed; }

    // Modifiers
    void setJerseyNumber(int num) { jerseyNumber = num; }
    void setPlayerName(const string& name) { playerName = name; }
    void setRuns(int runsScored) { runs = runsScored; }
    void setWickets(int wicketsTaken) { wickets = wicketsTaken; }
    void setMatchesPlayed(int matches) { matchesPlayed = matches; }

    // Overloaded operator for comparing players by runs
    bool operator<(const Player& other) const {
        return runs > other.runs; // Sort in descending order of runs
    }
};

class PlayerManager {
private:
    vector<Player> players;

public:
    // Function to add a player
    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    // Function to remove a player
    void removePlayer(int jerseyNumber) {
        auto it = find_if(players.begin(), players.end(),
                          [jerseyNumber](const Player& player) { return player.getJerseyNumber() == jerseyNumber; });
        if (it != players.end()) {
            players.erase(it);
            cout << "Player removed successfully!\n";
        } else {
            cout << "Player not found with Jersey Number " << jerseyNumber << ".\n";
        }
    }

    // Function to search for a player
    void searchPlayer(int choice, int searchValue) {
        auto it = find_if(players.begin(), players.end(), [choice, searchValue](const Player& player) {
            if (choice == 1)
                return player.getJerseyNumber() == searchValue;
            else if (choice == 2)
                return player.getPlayerName() == to_string(searchValue);
            else
                return false;
        });

        if (it != players.end()) {
            cout << "Player found:\n";
            cout << "Jersey Number: " << it->getJerseyNumber() << endl;
            cout << "Player Name: " << it->getPlayerName() << endl;
            cout << "Runs: " << it->getRuns() << endl;
            cout << "Wickets: " << it->getWickets() << endl;
            cout << "Matches Played: " << it->getMatchesPlayed() << endl;
        } else {
            cout << "Player not found.\n";
        }
    }

    // Function to update player details
    void updatePlayer(int jerseyToUpdate, int runs, int wickets, int matches) {
        auto it = find_if(players.begin(), players.end(),
                          [jerseyToUpdate](const Player& player) { return player.getJerseyNumber() == jerseyToUpdate; });
        if (it != players.end()) {
            it->setRuns(runs);
            it->setWickets(wickets);
            it->setMatchesPlayed(matches);
            cout << "Player data updated successfully!\n";
        } else {
            cout << "Player not found with Jersey Number " << jerseyToUpdate << ".\n";
        }
    }

    // Function to sort players by runs
    void sortByRuns() {
        sort(players.begin(), players.end());
        cout << "Top 3 Players by Runs:\n";
        int count = min(3, static_cast<int>(players.size()));
        for (int i = 0; i < count; ++i) {
            cout << "Rank " << i + 1 << ":\n";
            cout << "Jersey Number: " << players[i].getJerseyNumber() << endl;
            cout << "Player Name: " << players[i].getPlayerName() << endl;
            cout << "Runs: " << players[i].getRuns() << endl;
            cout << "Wickets: " << players[i].getWickets() << endl;
            cout << "Matches Played: " << players[i].getMatchesPlayed() << endl;
            cout << "-----------------\n";
        }
    }

    // Function to sort players by wickets
    void sortByWickets() {
        sort(players.begin(), players.end(),
             [](const Player& a, const Player& b) { return a.getWickets() > b.getWickets(); });

        cout << "Top 5 Players by Wickets:\n";
        int count = min(5, static_cast<int>(players.size()));
        for (int i = 0; i < count; ++i) {
            cout << "Rank " << i + 1 << ":\n";
            cout << "Jersey Number: " << players[i].getJerseyNumber() << endl;
            cout << "Player Name: " << players[i].getPlayerName() << endl;
            cout << "Runs: " << players[i].getRuns() << endl;
            cout << "Wickets: " << players[i].getWickets() << endl;
            cout << "Matches Played: " << players[i].getMatchesPlayed() << endl;
            cout << "-----------------\n";
        }
    }

    // Function to print all players
    void printAllPlayers() {
        if (players.empty()) {
            cout << "No players in the system.\n";
            return;
        }
        cout << "Displaying All Players:\n";
        for (const auto& player : players) {
            cout << "Jersey Number: " << player.getJerseyNumber() << endl;
            cout << "Player Name: " << player.getPlayerName() << endl;
            cout << "Runs: " << player.getRuns() << endl;
            cout << "Wickets: " << player.getWickets() << endl;
            cout << "Matches Played: " << player.getMatchesPlayed() << endl;
            cout << "-----------------\n";
        }
    }
};

int main() {
    PlayerManager manager;
    int choice;
    do {
        cout << "\nPlayer Management System:\n";
        cout << "1. Add Player\n";
        cout << "2. Remove Player\n";
        cout << "3. Search Player\n";
        cout << "4. Update Player\n";
        cout << "5. Print Top 3 Players by Runs\n";
        cout << "6. Print Top 5 Players by Wickets\n";
        cout << "7. Display All Players\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int jersey;
                string name;
                int runs, wickets, matches;
                cout << "Enter details for the new player:\n";
                cout << "Jersey Number: ";
                cin >> jersey;
                cout << "Player Name: ";
                cin >> name;
                cout << "Runs: ";
                cin >> runs;
                cout << "Wickets: ";
                cin >> wickets;
                cout << "Matches Played: ";
                cin >> matches;
                manager.addPlayer(Player(jersey, name, runs, wickets, matches));
                break;
            }
            case 2: {
                int jerseyToRemove;
                cout << "Enter the Jersey Number of the player to remove: ";
                cin >> jerseyToRemove;
                manager.removePlayer(jerseyToRemove);
                break;
            }
            case 3: {
                int searchChoice, searchValue;
                cout << "Search player by:\n";
                cout << "1. Jersey Number\n";
                cout << "2. Player Name\n";
                cout << "Enter your choice: ";
                cin >> searchChoice;
                cout << "Enter search value: ";
                cin >> searchValue;
                manager.searchPlayer(searchChoice, searchValue);
                break;
            }
            case 4: {
                int jerseyToUpdate, runs, wickets, matches;
                cout << "Enter the Jersey Number of the player to update: ";
                cin >> jerseyToUpdate;
                cout << "Enter updated details for the player:\n";
                cout << "Runs: ";
                cin >> runs;
                cout << "Wickets: ";
                cin >> wickets;
                cout << "Matches Played: ";
                cin >> matches;
                manager.updatePlayer(jerseyToUpdate, runs, wickets, matches);
                break;
            }
            case 5:
                manager.sortByRuns();
                break;
            case 6:
                manager.sortByWickets();
                break;
            case 7:
                manager.printAllPlayers();
                break;
            case 8:
                cout << "Exiting From Player Management System.!\n";
                break;
            default:
                cout << "Invalid choice. Please enter an option from the above options.\n";
        }
    } while (choice != 8);

    return 0;
}
