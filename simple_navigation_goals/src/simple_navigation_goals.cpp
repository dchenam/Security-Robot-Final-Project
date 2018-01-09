#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

/** function declarations **/
bool moveToGoal(double xGoal, double yGoal);

/** declare the coordinates of interest **/
double xGoal1 = 3.68838095665;
double yGoal1 = 2.62702989578;
double xGoal2 = -4.33983612061;
double yGoal2 = 2.31118774414;

bool goalReached = false;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  ros::spinOnce();

  int i = 1;
  while(true){
      i = i % 2;
      if( i==0 ){
        goalReached = moveToGoal(xGoal1,yGoal1);
      }else{
        goalReached = moveToGoal(xGoal2,yGoal2);
      }
      if(goalReached){
        ROS_INFO("Goal Reach!");
        ros::spinOnce();
      }else{
        ROS_INFO("Something goes wrong");
      }
      i++;
  }

  // move_base_msgs::MoveBaseGoal goal1;
  // move_base_msgs::MoveBaseGoal goal2;
  // goal1.target_pose.header.frame_id = "map";
  // goal1.target_pose.pose.position.x = 3.68838095665;
  // goal1.target_pose.pose.position.y = 2.62702989578;
  // goal1.target_pose.pose.orientation.z = -0.727393273189;
  // goal1.target_pose.pose.orientation.w = 0.686220828975;

  // goal2.target_pose.header.frame_id = "map";
  // goal2.target_pose.pose.position.x = -4.33983612061;
  // goal2.target_pose.pose.position.y = 2.31118774414;
  // goal2.target_pose.pose.orientation.z = 0.0;
  // goal2.target_pose.pose.orientation.w = 1.0;
  // int seq = 0;
  // int i = 1;
  // while(true){
  //   ROS_INFO("starting loop");
  //   i = i % 2;
  // //tell the action client that we want to spin a thread by default
  //   MoveBaseClient ac("move_base", true);
  //   move_base_msgs::MoveBaseGoal goal;
  //   //wait for the action server to come up
  //   while(!ac.waitForServer(ros::Duration(5.0))){
  //     ROS_INFO("Waiting for the move_base action server to come up");
  //   }

  //   if(i==0){
  //     goal = goal1;
  //   }else{
  //     goal = goal2;
  //   }
  //   goal.target_pose.header.stamp = ros::Time::now();
  //   goal.target_pose.header.seq = seq;
    
  //   ROS_INFO("Sending goal");
  //   ac.sendGoal(goal);
  //   ac.waitForResult();
  //   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  //     ROS_INFO("Hooray, the base moved to goal");
  //   else
  //     ROS_INFO("The base failed to move to goal for some reason");
    
  //   i++;
  // }
  return 0;
}

bool moveToGoal(double xGoal, double yGoal){

   //define a client for to send goal requests to the move_base server through a SimpleActionClient
   actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

   //wait for the action server to come up
   while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
   }

   move_base_msgs::MoveBaseGoal goal;

   //set up the frame parameters
   goal.target_pose.header.frame_id = "map";
   goal.target_pose.header.stamp = ros::Time::now();

   /* moving towards the goal*/

   goal.target_pose.pose.position.x =  xGoal;
   goal.target_pose.pose.position.y =  yGoal;
   goal.target_pose.pose.position.z =  0.0;
   goal.target_pose.pose.orientation.x = 0.0;
   goal.target_pose.pose.orientation.y = 0.0;
   goal.target_pose.pose.orientation.z = 0.0;
   goal.target_pose.pose.orientation.w = 1.0;

   ROS_INFO("Sending goal location ...");
   ac.sendGoal(goal);

   ac.waitForResult();

   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("You have reached the destination");
      return true;
   }
   else{
      ROS_INFO("The robot failed to reach the destination");
      return false;
   }

}
