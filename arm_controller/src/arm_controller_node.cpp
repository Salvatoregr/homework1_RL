#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

void JointStateCallback(const sensor_msgs::JointState& msg){
for(int i=0;i<4;i++){
  ROS_INFO("Joint Position %d: [%lf]",i, msg.position[i]);}
}


int main(int argc, char **argv)
{

  ros::init(argc,argv,"arm_controller_node");	//I'm creating and initializing the node, giving it a name
  ros::NodeHandle nodeHandle;		        //takes care of managing the node
    
  //ros::Subscriber subscriber = nodeHandle.subscribe("/joint_states",10,JointStateCallback);  FOR RVIZ
  ros::Subscriber subscriber = nodeHandle.subscribe("/arm/joint_states",5,JointStateCallback); //FOR GAZEBO
  
  //ros::spin();
  
  ros::Publisher JointStatePublisher1=nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J1_controller/command",1);
  ros::Publisher JointStatePublisher2=nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J2_controller/command",1);
  ros::Publisher JointStatePublisher3=nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J3_controller/command",1);
  ros::Publisher JointStatePublisher4=nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J4_controller/command",1);
  
  while(ros::ok()){
    std_msgs::Float64 pos1,pos2,pos3,pos4;
    pos1.data=0.28;
    pos2.data=0.45;
    pos3.data=0.725;
    pos4.data=0.81;
    JointStatePublisher1.publish(pos1);
    JointStatePublisher2.publish(pos2);
    JointStatePublisher3.publish(pos3);
    JointStatePublisher4.publish(pos4);
    ros::spinOnce();
    
  }
  
  
return 0;
}



