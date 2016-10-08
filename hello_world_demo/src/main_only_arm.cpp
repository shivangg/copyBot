/******************************************************************************
* Copyright (c) 2011
* Locomotec
*
* Author:
* Sebastian Blumenthal
*
*
* This software is published under a dual-license: GNU Lesser General Public
* License LGPL 2.1 and BSD license. The dual-license implies that users of this
* code may choose which terms they prefer.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Locomotec nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License LGPL as
* published by the Free Software Foundation, either version 2.1 of the
* License, or (at your option) any later version or the BSD license.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License LGPL and the BSD license for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License LGPL and BSD license along with this program.
*
******************************************************************************/

#include "youbot_driver/youbot/YouBotBase.hpp"
#include "youbot_driver/youbot/YouBotManipulator.hpp"
#include <fstream>
#include <iostream>

using namespace youbot;

/* create handles for youBot base and manipulator (if available) */
	YouBotBase* myYouBotBase = 0;
	YouBotManipulator* myYouBotManipulator = 0;
/* Variable for the arm. */
JointAngleSetpoint desiredJointAngle;



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


int main(int argc, char const * argv[]) 
{

	/* configuration flags for different system configuration (e.g. base without arm)*/
	bool youBotHasBase = false;
	bool youBotHasArm = false;

	/* define velocities */
	double translationalVelocity = 0.05; //meter_per_second
	double rotationalVelocity = 0.2; //radian_per_second

	
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

	

	try {
		/*
		 * Simple sequence of commands to the youBot:
		 */

		if (youBotHasBase && youBotHasArm) 
		{

/////////////////////////////to move the youbot_base using data from infile////////////////////////////////////////////

				fstream infile;
				double leapX, leapY, leapR, j1, j2, j3, j4, j5,atStart, atEnd, loopEnabled;			//use xyzrpy array
				double startPos[5], endPos[5];
				double lj1 = 0.0110692, lj2 = 0.0110692, lj3 = -5.03655, lj4 = 0.0321239, lj5 = 0.120619, joint_diff;							//last joint position

		 while(1)
			 {
				infile.open("/opt/lampp/htdocs/myprojects/NiYantra/labviewdata/leap.txt");
				
				//inputting datastream & logging to the terminal
				infile /* >>  leapX >> leapY >> leapR*/  >> j1 >> j2 >> j3 >> j4 >> j5 >> atStart >> atEnd >> loopEnabled;
				//cout << "leapX " << leapX << "\t" << leapY << "\t" << leapR << "\t";
				leapX=00;
				leapY=00;
				leapR/=5;
				cout << endl;


				//mapping to keep values in limits 


				longitudinalVelocity = leapY * meter_per_second;
				transversalVelocity = leapX * meter_per_second;
				angularVelocity = leapR * radian_per_second;

				// if (longitudinalVelocity > 1.5)
				// {
				// 	longitudinalVelocity = 1.5;
				// }
				// if (longitudinalVelocity < -1.5)
				// {
				// 	longitudinalVelocity = -1.5;
				// }
				// if (transversalVelocity > 1.5)
				// {
				// 	transversalVelocity = 1.5;
				// }
				// if (transversalVelocity < -1.5)
				// {
				// 	transversalVelocity = -1.5;
				// }
				// if (angularVelocity > 1.5)
				// {
				// 	angularVelocity = 1.5;
				// }
				// if (angularVelocity < -1.5)
				// {
				// 	angularVelocity = -1.5;
				// }

				//myYouBotBase->setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);


			//coercion the limit values
			if (j1 > 5.83014)	j1 = 5.83014;
			if (j2 > 2.60799)	j2 = 2.60799;
			if (j3 > -0.005708)	j3 = -0.005708;
			if (j4 > 3.4192)	j4 = 3.4192;
			if (j5 > 3.4192)	j5 = 3.4192;

			if (j1 < 0.0110692)	j1 = 0.0110692;
			if (j2 < 0.0110692)	j2 = 0.0110692;
			if (j3 < -5.03655)	j3 = -5.03655;
			if (j4 < 0.0321239)	j4 = 0.0321239;
			if (j5 < 0.120619)	j5 = 0.120619;


			
			if (j1 >= lj1)		joint_diff = j1 -lj1;
			else				joint_diff = lj1 - j1;
			if (joint_diff < 0.1) j1 = lj1;
			
			if (j2 >= lj2)		joint_diff = j2 -lj2;
			else				joint_diff = lj2 - j2;
			if (joint_diff < 0.1) j2 = lj2;

			if (j3 >= lj3)		joint_diff = j3 -lj3;
			else				joint_diff = lj3 - j3;
			if (joint_diff < 0.1) j3 = lj3;

			if (j4 >= lj4)		joint_diff = j4 -lj4;
			else				joint_diff = lj4 - j4;
			if (joint_diff < 0.1) j4 = lj4;

			if (j5 >= lj5)		joint_diff = j5 -lj5;
			else				joint_diff = lj5 - j5;
			if (joint_diff < 0.1) j5 = lj5;

			if (atStart)
			{
				startPos[0] = j1;
				startPos[1] = j2;
				startPos[2] = j3;
				startPos[3] = j4;
				startPos[4] = j5;

				cout << startPos[0] << startPos[1] << startPos[2] << startPos[3] << startPos[4];
			}

			if (atEnd)
			{
				endPos[0] = j1;
				endPos[1] = j2;
				endPos[2] = j3;
				endPos[3] = j4;
				endPos[4] = j5;
				cout << endPos[0] << endPos[1] << endPos[2] << endPos[3] << endPos[4];
			}

			if (loopEnabled)
			{
			
			cout << "loopEnabled";
			moveYouBot(startPos[0],startPos[1],startPos[2],startPos[3],startPos[4]);

			SLEEP_MILLISEC(4000);

			moveYouBot(endPos[0],endPos[1],endPos[2],endPos[3],endPos[4]);

			SLEEP_MILLISEC(4000);

			}


			if (!loopEnabled)
			{
				cout << "normal working";
				moveYouBot(j1, j2, j3, j4 ,j5);
			}

			lj1 = j1;	//put the value of current joint into last joint   
			lj2 = j2;	//put the value of current joint into last joint  
			lj3 = j3;	//put the value of current joint into last joint  
			lj4 = j4;	//put the value of current joint into last joint  
			lj5 = j5;	//put the value of current joint into last joint  




				infile.close();
				SLEEP_MILLISEC(50);
			}
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

