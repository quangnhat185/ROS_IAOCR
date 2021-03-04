### Design goal of ROS:
  - The application task can be decomposed into many independent subsystems, such as navigation, computer vision, grasping and so on.
  - The subsystems can be used for other tasks, such as doing security patrols, cleaning, delivering mail, and so on.
  - With proper hardware and geometry abstraction layers, the vast majority of the application software can run on any robot.

### ROS Graph
  - A ROS system is made up of many different programs running simultaneously and communicating with one another by passing __message__.
  - It is convenient to use the mathematical graph to present this collection of programs and messages: the programs are the graph __node__, and programs that communicate with another connected by __edges__.

### ROS core
  - Roscore is a service that provides connection information to nodes so that they can transmit messages to one another. __Every node connects to roscore at startup to register details of the message streams it publishes and the streams to which it wishes to subscribe.__
  - When a new node appears, roscore provides it with the information that it need to __form a direct peer-to-peer connection with other nodes publishing and subscribing to the same message topics.__

### Catkin
  - `catkin` is the ROS build system: the set of tools that ROS uses to generate executable programs, libraries, scripts, and interfaces that other code can use.
  - For causal `catkin` user, there are two files you need to know: `CMakeLists.txt` and `package.xml` used to add some specific information in order to have thing work properly.

### Workspaces
  - Before you start writing any ROS code, you need to set up a __workspace__ for this code to live in. A workspace is simply a set of directories in which a related set of ROS code lives.
  ```
  $ mkdir -p ~/catkin_ws/src
  $ cd ~/catkin_ws/src
  $ catkin_init_workspace
  $ cd ~/catkin_ws
  $ catkin_make
  ```

### ROS Packages
  - ROS software is organize into packages, each of which contains some combination of code, data, and documentation. The ROS ecosystem includes thousands of public available packages in open repositories, and many thousands more package behind organization firewalls.
  - Packages sit inside `workspaces`, in the `src` directory. Each package directory must include a `CMakeLists.txt` file and a `package.xml` file that describes the contents of the package and how `catkin` should interact with it.
  ```
  $ cd ~/catkin_ws/src
  $ catkin_create_pkg {package_name} rospy
  ```

### Rosrun
  - Package are just locations in the file system, and because ROS nodes are typically executable programs, one could manually `cd` around the file system to start all the ROS nodes of the interest.
  - However chasing down the directory would become tiresome in large filesystem, since nodes can be deeply buried in large directory hierarchies. To automate this task, we can use `rosrun` that will search a package for the requested program and pass it any parameters supplied on the command line.
  ```
  $ rosrun PACKAGE EXECUTABLE [ARGS]
  ```

### Roslaunch
  - roslaunch is a command-line tool designed to automate the launching of collections of ROS nodes.
  ```
  roslaunch PACKAGE LAUNCH_FILE
  ```
  - Launch files are XML files that describe a collection of XML file that describes a collection of nodes along with their topic remappings and parameters.
  ```
  <launch>
  <node name="talker" pkg="rospy_tutorials"
  type="talker.py" output="screen" />
  <node name="listener" pkg="rospy_tutorials"
  type="listener.py" output="screen" />
  </launch>
  ```
