/******************************************************************************

*
*Gripper Position limits 0 <= 0.0115 meter AND 0.02 meter also!!
*
******************************************************************************/

#include "youbot_driver/youbot/YouBotBase.hpp"
#include "youbot_driver/youbot/YouBotManipulator.hpp"
#include "youbot_driver/youbot/YouBotGripper.hpp"
#include <fstream>
#include <iostream>

using namespace youbot;

int main(int argc, char const * argv[]) {

	double leapX;

	/* configuration flags for different system configuration (e.g. base without arm)*/
	bool youBotHasBase = false;
	bool youBotHasArm = false;

	/* define velocities */
	double translationalVelocity = 0.05; //meter_per_second
	double rotationalVelocity = 0.2; //radian_per_second

	/* create handles for youBot base and manipulator (if available) */
	YouBotBase* myYouBotBase = 0;
	YouBotManipulator* myYouBotManipulator = 0;

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

	/* Variable for the arm. */
	JointAngleSetpoint desiredJointAngle;

	try {
		/*
		 * Simple sequence of commands to the youBot:
		 */

		if (youBotHasBase) {

			// /* forward */
			// longitudinalVelocity = translationalVelocity * meter_per_second;
			// transversalVelocity = 0 * meter_per_second;
			// myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
			// LOG(info) << "drive forward";
			// SLEEP_MILLISEC(2000);

			// /* backwards */
			// longitudinalVelocity = -translationalVelocity * meter_per_second;
			// transversalVelocity = 0 * meter_per_second;
			// myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
			// LOG(info) << "drive backwards";
			// SLEEP_MILLISEC(2000);

			// /* left */
			// longitudinalVelocity = 0 * meter_per_second;
			// transversalVelocity = translationalVelocity * meter_per_second;
			// angularVelocity = 0 * radian_per_second;
			// myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
			// LOG(info) << "drive left";
			// SLEEP_MILLISEC(2000);

			// /* right */
			// longitudinalVelocity = 0 * meter_per_second;
			// transversalVelocity = -translationalVelocity * meter_per_second;
			// angularVelocity = 0 * radian_per_second;
			// myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
			// LOG(info) << "drive right";
			// SLEEP_MILLISEC(2000);

			// /* stop base */
			// longitudinalVelocity = 0 * meter_per_second;
			// transversalVelocity = 0 * meter_per_second;
			// angularVelocity = 0 * radian_per_second;
			// myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
			// LOG(info) << "stop base";
		}

		fstream infile;

		if (youBotHasArm) {

			while(1)
			{
				infile.open("/home/shivangg/grip.txt");
					cout << "yoyo" << endl;
					//inputting datastream & logging to the terminal
					infile >>  leapX;

					cout << leapX <<endl;

				barSpacing.barSpacing = leapX* meter;
				myYouBotManipulator->getArmGripper().setData(barSpacing);
				//SLEEP_MILLISEC(5000)

				// barSpacing.barSpacing = 0.0 * meter;
				// myYouBotManipulator->getArmGripper().setData(barSpacing);

				infile.close();

				SLEEP_MILLISEC(50);
			}
			/* unfold arm 
			 * all of the following constants are empirically determined to move the arm into the desired position 
			 */
			// desiredJointAngle.angle = 2.56244 * radian;
			// myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);

			// desiredJointAngle.angle = 1.04883 * radian;
			// myYouBotManipulator->getArmJoint(2).setData(desiredJointAngle);

			// desiredJointAngle.angle = -2.43523 * radian;
			// myYouBotManipulator->getArmJoint(3).setData(desiredJointAngle);

			// desiredJointAngle.angle = 1.73184 * radian;
			// myYouBotManipulator->getArmJoint(4).setData(desiredJointAngle);

			// double gripperPosition = 1;

			// desiredJointAngle.angle = gripperPosition * radian;
			// myYouBotManipulator->getArmJoint(5).setData(desiredJointAngle);

			 // LOG(info) << argv[1];
			 // = atoi(argv[1]);
			 //  	cin >> gripperPosition;
				// cout << gripperPosition;
			 
			 //to move the joint5(gripper) according to mousePosition
				//open input file stream
				// fstream infile;

/*			 while(gripperPosition)
			 {
				infile.open("/opt/lampp/htdocs/myprojects/NiYantra/dataX.txt");
				infile >> gripperPosition;
				cout << "mousePosition " << gripperPosition << "\t";
				gripperPosition/=260;
				cout << "gripperPosition " << gripperPosition << endl;

				//end if position is 0
				if (gripperPosition == 0)
				{
					break;
				}


				//mapping to keep values in limits 
				if (gripperPosition < 0.2)
				{
						gripperPosition = 0.2;
				}

				desiredJointAngle.angle = gripperPosition * radian;
				myYouBotManipulator->getArmJoint(5).setData(desiredJointAngle);

				infile.close();
				SLEEP_MILLISEC(50);
			}
*/			LOG(info) << "unfold arm";
			SLEEP_MILLISEC(4000);

			/* fold arm (approx. home position) using empirically determined values for the positions */
			// desiredJointAngle.angle = 0.11 * radian;
			// myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);

			// desiredJointAngle.angle = 0.11 * radian;
			// myYouBotManipulator->getArmJoint(2).setData(desiredJointAngle);

			// desiredJointAngle.angle = -0.11 * radian;
			// myYouBotManipulator->getArmJoint(3).setData(desiredJointAngle);
			
			// desiredJointAngle.angle = 0.11 * radian;
			// myYouBotManipulator->getArmJoint(4).setData(desiredJointAngle);

			// desiredJointAngle.angle = 0.12 * radian;
			// myYouBotManipulator->getArmJoint(5).setData(desiredJointAngle);
			
			// LOG(info) << "fold arm";
			// SLEEP_MILLISEC(4000);
		}

	} catch (std::exception& e) {
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

