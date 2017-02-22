/******************************************************************************
	DONE		Add the joint positions for the Important pose.
			

				Add the keystroke functionality for the breakout point

						take a scanf character then move in X and Y direction 
						Other character to exit the while loop
	
Add Poses
	1. For the space just before the pen holder. It shouldn't come from the side BUT straight back

	2. Move to waveRight using this pose.





*
******************************************************************************/

#include "youbot_driver/youbot/YouBotBase.hpp"
#include "youbot_driver/youbot/YouBotManipulator.hpp"
#include "youbot_driver/youbot/YouBotGripper.hpp"
#include <fstream>
#include <iostream>

using namespace youbot;

/* create handles for youBot base and manipulator (if available) */
	YouBotBase* myYouBotBase = 0;
	YouBotManipulator* myYouBotManipulator = 0;
/* Variable for the arm. */
JointAngleSetpoint desiredJointAngle;


double joints[5];




void moveYouBot(double j1,double j2,double j3,double j4,double j5)
{
	desiredJointAngle.angle = j1 * radian;
	myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);

	desiredJointAngle.angle = j2 * radian;
	myYouBotManipulator->getArmJoint(2).setData(desiredJointAngle);

	desiredJointAngle.angle = j3 * radian;
	myYouBotManipulator->getArmJoint(3).setData(desiredJointAngle);

	desiredJointAngle.angle = j4 * radian;
	myYouBotManipulator->getArmJoint(4).setData(desiredJointAngle);

	desiredJointAngle.angle = j5 * radian;
	myYouBotManipulator->getArmJoint(5).setData(desiredJointAngle);
}

void goHome()
{
	joints[0] = 0.05;
	joints[1] = 0.05;
	joints[2] = -0.05;
	joints[3] = 0.03;
	joints[4] = 0.12;

	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);
	LOG(info) << "Going home, mama!";
}

void goRight()
{	

	joints[0] = 2.0;
	joints[1] = 0.9;
	joints[2] = -2.9;
	joints[3] = 0.97;
	joints[4] = 2.8;

	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);
	LOG(info) << "Right way!";
}

void goLeft()
{	

	joints[0] = 4.6;
	joints[1] = 0.9;
	joints[2] = -2.9;
	joints[3] = 0.97;
	joints[4] = 2.8;

	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);
	LOG(info) << "Left not wrong!";
}

void goStraightBeforeFlag()
{
	joints[0] = 2.9;
	joints[1] = 1.0;
	joints[2] = -3.4;
	joints[3] = 0.67;
	joints[4] = 2.9;


	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);
	LOG(info) << "I see the Thing :)";
}


void goBeforeFlag()
{

	joints[0] = 2.9;
	joints[1] = 0.6;
	joints[2] = -4.0;
	joints[3] = 1.7;
	joints[4] = 2.9;


	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);
	LOG(info) << "Should I pick it up?";
}


void goSlightY(double diff)
{
	joints[2] += diff;
	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);

}


void goSlightX(double diff)
{
	joints[0] += diff;
	moveYouBot(joints[0], joints[1], joints[2], joints[3], joints[4]);

}



int main(int argc, char const * argv[]) 
{

	/* configuration flags for different system configuration (e.g. base without arm)*/
	bool youBotHasBase = false;
	bool youBotHasArm = false;

	/* define velocities */
	double translationalVelocity = 0.05; //meter_per_second
	double rotationalVelocity = 0.2; //radian_per_second

	//create a Gripper Bar spacing variable
	youbot::GripperBarSpacingSetPoint barSpacing;
	
	try {
		myYouBotBase = new YouBotBase("youbot-base", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotBase->doJointCommutation();

		youBotHasBase = true;
	} catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasBase = false;
	}

	try {
		myYouBotManipulator = new YouBotManipulator("youbot-manipulator", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotManipulator->doJointCommutation();
		myYouBotManipulator->calibrateManipulator();

		youBotHasArm = true;
	} catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasArm = false;
	}

	/*
	* Variable for the base.
	* Here "boost units" is used to set values in OODL, that means you have to set a value and a unit.
	*/
	quantity<si::velocity> longitudinalVelocity = 0 * meter_per_second;
	quantity<si::velocity> transversalVelocity = 0 * meter_per_second;
	quantity<si::angular_velocity> angularVelocity = 0 * radian_per_second;

	JointAngleSetpoint desiredJointAngle;	

	try {
		
		if (youBotHasBase && youBotHasArm) 
		{

/////////////////////////////to move the youbot_base using data from infile////////////////////////////////////////////

				// fstream infile;
				// double j1, j2, j3, j4, j5;		//use xyzrpy array
				// double home[5], beforeFlag[5],waveRight[5], waveLeft[5];

				double lj1 = 0.0110692, lj2 = 0.0110692, lj3 = -5.03655, lj4 = 0.0321239, lj5 = 0.120619, joint_diff;							//last joint position


				goStraightBeforeFlag();
				SLEEP_MILLISEC(2500);

				goBeforeFlag();
				SLEEP_MILLISEC(1500);

					
				char ch;
				double diffX;
				double diffY;

				barSpacing.barSpacing = 0.02 * meter;
				myYouBotManipulator->getArmGripper().setData(barSpacing);
				SLEEP_MILLISEC(1000);


				// q to quit
				// WASD format


				while(ch!='q')
				{
					cin >> ch;

					if (ch=='w')
					{
						diffY = 0.05;
						goSlightY(diffY);
					}
					else if (ch=='s')
					{
						diffY = -0.05;
						goSlightY(diffY);
					}
					else if (ch=='a')
					{
						diffX = 0.05;
						goSlightX(diffX);
					}
					else if (ch=='d')
					{
						diffX = -0.05;
						goSlightX(diffX);
					}

					
					
					
				}

				barSpacing.barSpacing = 0.0 * meter;
				myYouBotManipulator->getArmGripper().setData(barSpacing);
				SLEEP_MILLISEC(2000);


				goStraightBeforeFlag();
				SLEEP_MILLISEC(1500);


				goRight();
				SLEEP_MILLISEC(2000);
				
				goLeft();
				SLEEP_MILLISEC(3000);
				
				goHome();
				SLEEP_MILLISEC(3000);



		 // while(1)
			//  {
			// 	infile.open("/home/shivangg/leap.txt");
			// 	//inputting datastream & logging to the terminal
			// 	infile /* >>  leapX >> leapY >> leapR*/  >> j1 >> j2 >> j3 >> j4 >> j5 >> atStart >> atEnd >> loopEnabled;
			// 	//cout << "leapX " << leapX << "\t" << leapY << "\t" << leapR << "\t";
			// 	leapX=00;
			// 	leapY=00;
			// 	leapR/=5;
			// 	cout << endl;


			// 	//mapping to keep values in limits 


			// 	longitudinalVelocity = leapY * meter_per_second;
			// 	transversalVelocity = leapX * meter_per_second;
			// 	angularVelocity = leapR * radian_per_second;

				
			// 	//myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);

			// 	//coercion the limit values
			// 	if (j1 > 5.83014)	j1 = 5.83014;
			// 	if (j2 > 2.60799)	j2 = 2.60799;
			// 	if (j3 > -0.005708)	j3 = -0.005708;
			// 	if (j4 > 3.4192)	j4 = 3.4192;
			// 	if (j5 > 3.4192)	j5 = 3.4192;

			// 	if (j1 < 0.0110692)	j1 = 0.0110692;
			// 	if (j2 < 0.0110692)	j2 = 0.0110692;
			// 	if (j3 < -5.03655)	j3 = -5.03655;
			// 	if (j4 < 0.0321239)	j4 = 0.0321239;
			// 	if (j5 < 0.120619)	j5 = 0.120619;


			// 	//Do not move the joint if the diffween the old and new values is less than 0.1

			// 	if (j1 >= lj1)		joint_diff = j1 -lj1;
			// 	else				joint_diff = lj1 - j1;
			// 	if (joint_diff < 0.1) j1 = lj1;
				
			// 	if (j2 >= lj2)		joint_diff = j2 -lj2;
			// 	else				joint_diff = lj2 - j2;
			// 	if (joint_diff < 0.1) j2 = lj2;

			// 	if (j3 >= lj3)		joint_diff = j3 -lj3;
			// 	else				joint_diff = lj3 - j3;
			// 	if (joint_diff < 0.1) j3 = lj3;

			// 	if (j4 >= lj4)		joint_diff = j4 -lj4;
			// 	else				joint_diff = lj4 - j4;
			// 	if (joint_diff < 0.1) j4 = lj4;

			// 	if (j5 >= lj5)		joint_diff = j5 -lj5;
			// 	else				joint_diff = lj5 - j5;
			// 	if (joint_diff < 0.1) j5 = lj5;

			// 	// atStart and atEnd are flags to set the initial and final points
			// 	// startPos and endPos are initial and final joint values. 

			// 	if (atStart)
			// 	{
			// 		startPos[0] = j1;
			// 		startPos[1] = j2;
			// 		startPos[2] = j3;
			// 		startPos[3] = j4;
			// 		startPos[4] = j5;

			// 		cout << startPos[0] << startPos[1] << startPos[2] << startPos[3] << startPos[4];
			// 	}

			// 	if (atEnd)
			// 	{
			// 		endPos[0] = j1;
			// 		endPos[1] = j2;
			// 		endPos[2] = j3;
			// 		endPos[3] = j4;
			// 		endPos[4] = j5;
			// 		cout << endPos[0] << endPos[1] << endPos[2] << endPos[3] << endPos[4];
			// 	}

			// 	if (loopEnabled)
			// 	{
				
			// 	cout << "loopEnabled";
			// 	moveYouBot(startPos[0],startPos[1],startPos[2],startPos[3],startPos[4]);

			// 	SLEEP_MILLISEC(4000);

			// 	moveYouBot(endPos[0],endPos[1],endPos[2],endPos[3],endPos[4]);

			// 	SLEEP_MILLISEC(4000);

			// 	}


			// 	if (!loopEnabled)
			// 	{
			// 		cout << "normal working";
			// 		moveYouBot(j1, j2, j3, j4 ,j5);
			// 	}

			// 	lj1 = j1;	//put the value of current joint into last joint   
			// 	lj2 = j2;	//put the value of current joint into last joint  
			// 	lj3 = j3;	//put the value of current joint into last joint  
			// 	lj4 = j4;	//put the value of current joint into last joint  
			// 	lj5 = j5;	//put the value of current joint into last joint  




			// 		infile.close();
			// 		SLEEP_MILLISEC(50);
			// }
		}

	} 
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "unhandled exception" << std::endl;
	}

	/* clean up */
	if (myYouBotBase) {
		delete myYouBotBase;
		myYouBotBase = 0;
	}
	if (myYouBotManipulator) {
		delete myYouBotManipulator;
		myYouBotManipulator = 0;
	}

	LOG(info) << "Done.";

	return 0;
}

