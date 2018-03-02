#include <iostream>
#include <vector>

// Boost includes
#include <boost/shared_ptr.hpp>

// Ros includes
#include <ros/ros.h>
#include <rws2018_libs/team.h>
#include <tf/transform_broadcaster.h>

using namespace std;

namespace rws_bramos
{
class Player
{
public:
  Player(string argin_name)
  {
    name = argin_name;
  }

  string name;

  // Overloaded setter for team_nam
  int setTeamName(int index = 2)
  {
    if (index == 0)
    {
      setTeamName("red");
    }
    else if (index == 1)
    {
      setTeamName("green");
    }
    else if (index == 2)
    {
      setTeamName("blue");
    }
    else
    {
      setTeamName("none");
    }
  }

  // Setter for team_nam
  int setTeamName(string argin_team)
  {
    if (argin_team == "red" || argin_team == "green" || argin_team == "blue")
    {
      team_name = argin_team;
      return 1;
    }
    else
    {
      return 0;
    }
  }

  // Getter of team_name
  string getTeamName(void)
  {
    return team_name;
  }

private:
  string team_name;
};

class MyPlayer : public Player
{
public:
  boost::shared_ptr<Team> red_team;
  boost::shared_ptr<Team> green_team;
  boost::shared_ptr<Team> blue_team;
  boost::shared_ptr<Team> my_team;
  boost::shared_ptr<Team> my_preys;
  boost::shared_ptr<Team> my_hunters;
  tf::TransformBroadcaster br;  // declare the broadcaster

  MyPlayer(string argin_name, string argin_team) : Player(argin_name)
  {
    red_team = boost::shared_ptr<Team>(new Team("red"));
    green_team = boost::shared_ptr<Team>(new Team("green"));
    blue_team = boost::shared_ptr<Team>(new Team("blue"));

    if (red_team->playerBelongsToTeam(name))
    {
      my_team = red_team;
      my_preys = green_team;
      my_hunters = blue_team;
      setTeamName("red");
    }
    else if (blue_team->playerBelongsToTeam(name))
    {
      my_preys = red_team;
      my_hunters = green_team;
      my_team = blue_team;
      setTeamName("blue");
    }
    else if (green_team->playerBelongsToTeam(name))
    {
      my_hunters = red_team;
      my_team = green_team;
      my_preys = blue_team;
      setTeamName("green");
    }

    printReport();
  }

  void move(void)
  {
    tf::Transform transform;  // declare the transformation object
    transform.setOrigin(tf::Vector3(-3, 5, 0.0));
    tf::Quaternion q;
    q.setRPY(0, 0, M_PI / 3);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "bramos"));
  }

  void printReport()
  {
    ROS_INFO_STREAM("My name is " << name << " and my team is " << getTeamName().c_str() << endl);
    ROS_INFO("My name is %s and my team is %s", name.c_str(), getTeamName().c_str());
  }
};

}  // end of namespace

int main(int argc, char** argv)
{
  ros::init(argc, argv, "bramos");
  ros::NodeHandle n;

  // Creating an instance of class Player
  rws_bramos::MyPlayer my_player("bramos", "red");

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    my_player.move();

    ros::spinOnce();
    loop_rate.sleep();
  }
}
