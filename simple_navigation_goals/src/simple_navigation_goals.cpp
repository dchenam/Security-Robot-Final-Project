#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

/** function declarations **/
bool moveToGoal(double xGoal, double yGoal);
        //toilet
        // x: 12.3343067169
        // y: -12.283946991

    //corridor
        //     x: 3.10740280151
        // y: -8.33006095886

    //dark little corner
        //     x: -0.140046596527
        // y: -13.3347625732


/** declare the coordinates of interest **/
double xToilet =  12.3343067169;
double yToilet = -12.283946991;
double xCorridor = 3.2757563591;
double yCorridor = -8.45731639862;
double xDark = -0.140046596527;
double yDark = -13.3347625732;

bool goalReached = false;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  ros::spinOnce();

  int i = 0;
  while(true){
      i = i % 3;
      if( i==0 ){
        goalReached = moveToGoal(xToilet,yToilet);
      }else if(i==1){
        goalReached = moveToGoal(xCorridor,yCorridor);
      }else{
        goalReached = moveToGoal(xDark,yDark);
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
