## Setting ROS Indigo for youbot

Steps
* Install ROS indigo-full-desktop from official instruction
* Install Youbot driver
	
	```shell
	sudo apt-get install ros-indigo-youbot-driver
	export YOUBOT_CONFIG_FOLDER_LOCATION=/opt/ros/indigo/etc/youbot_driver/config/
	```

* install Youbot ROS wrapper
	
	```shell
	sudo apt-get install ros-indigo-youbot-driver-ros-interface ros-indigo-youbot-description
	sudo setcap cap_net_raw+ep /opt/ros/indigo/lib/youbot_driver_ros_interface/youbot_driver_ros_interface
	sudo ldconfig /opt/ros/indigo/lib
	```

* install the MoveIt Controller !
	
	```shell
	sudo apt-get install ros-indigo-moveit
	```

* install openni_launch
	
	```shell
	sudo apt-get install ros-indigo-openni-launch
	```

* install the joypad package
	
	```shell	
	sudo apt-get install ros-indigo-joy
	```

* install Eigen3 if problems

	```shell
					# pkg_search_module(Eigen3 REQUIRED eigen3)
					include_directories(${EIGEN3_INCLUDE_DIR})
					add_definitions(${EIGEN3_DEFINITIONS})

					if(NOT EIGEN3_FOUND)
					    # Fallback to cmake_modules
					    find_package(cmake_modules REQUIRED)
					    find_package(Eigen REQUIRED)
					    set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
					    set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  
					    # Possibly map additional variables to the EIGEN3_ prefix.
					else()
					    set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
					endif()

					# catkin_package(
					#     ...
					#     DEPENDS Eigen
					#     ...
					# )

					# include_directories(
					#     ...
					#     ${Eigen_INCLUDE_DIRS}
					# )	

	```

* Delete/rename youbot-driver, youbot-oold and such packages because they were installed by apt-get

* Refer the controller of sven to make the yiming package work!

	**AND**

* try the kinematic solver of the yiming to work with Moveit! API



**Other way**

* take the end value, Pause(break point), run again.
