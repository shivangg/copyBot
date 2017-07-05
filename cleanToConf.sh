sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116 

sudo apt-get -y update

sudo apt-get -y install ros-indigo-desktop-full

echo "source /opt/ros/indigo/setup.zsh" >> ~/.zshrc

source ~/.zshrc
sudo ldconfig /opt/ros/indigo/lib

sudo apt-get -y install ros-indigo-youbot-driver
export YOUBOT_CONFIG_FOLDER_LOCATION=/opt/ros/indigo/etc/youbot_driver/config/

sudo apt-get -y install ros-indigo-youbot-driver-ros-interface ros-indigo-youbot-description
sudo setcap cap_net_raw+ep /opt/ros/indigo/lib/youbot_driver_ros_interface/youbot_driver_ros_interface
sudo ldconfig /opt/ros/indigo/lib

sudo apt-get -y install ros-indigo-moveit

sudo apt-get -y install ros-indigo-openni-launch
sudo apt-get -y install ros-indigo-joy

sudo apt-get -y install libx32ncurses5-dev

sudo apt-get -y install libsdl2-dev
sudo apt-get -y install libsdl1.2-dev
