#include <iostream>

class Player
{
public:
  Player(std::string argin_name)
  {
    // this->name = name;
    name = argin_name;
  }

  std::string name;

  // Accessor for team_name
  void set TeamName(std::string argin_team)
  {
    team_name = argin_team;
    // adicionar restrições que só permitam equipas green, red, blue
  }

private:
  // não pode ser usado fora da class
  std::string team_name;
};

int main()
{
  std::string player_name = "bramos";
  // Creating an instance of class Player
  Player player(player_name);

  std::cout << "Created an instance of class player with public name " << player.name << std::endl;
}