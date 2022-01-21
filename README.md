
 
# Automated Door System
#### Java and Arduino Iteration
 
The Automated Door Opening System is a major project created in both Java and Arduino
for a first year Engineering course. This project is an iteration of my MATLAB
version of this project. 
 
This version interfaces between Arduino and Java and uses JavaFX
to create an interactive GUI operating with the physical system. 
 
### Context
In my first year 'Computational Thinking through Mechatronics' course,
the class was tasked with creating any project we liked as long as it hard a physical
hardware component (Arduino) and it was programmed using MATLAB.
 
During the time, COVID was near its peak during the second wave which 
inspired me to create some sort of system (or prototype of a system) 
that could help a group of people affected by the current impacts of the
virus in our communities. I targeted small businesses that wouldn't be able to afford
industry used door systems by coming up with a way for this system to be installed
onto doors that open at 90 degrees rather than slide apart. The interactive GUI
then also allows businesses to track how many people are entering their store.
 
While trying to stay within the scope of our assignment and time allocated to 
us, I decided to create prototype of a door opening system allowing users
to open a door simply by waving their hand in front of it resulting in a reduced amount of  germs
being spread by people touching a door handle.
 
 
 
## Features
Having come up with this idea, I implemented other features such as:
* GUI capabilities that: 
   * Allow the door to be manually opened and closed
   * Completely toggle the system on and off
   * View a live graph of the amount of times the door has been opened
* Detecting when an object or person is blocking the door so it doesn't close on them
* Light & sound indicators that tell you the state of the system
* A 'night-mode' that disables access to the door when it becomes dark
 
## How it works
The following is a video DEMO of the system: [![Demo](https://i.imgur.com/41d3LHi.png)](https://youtu.be/Mdk2C0ArVRQ?t=76)
 
**The components used in this project are as follows:**
* `An Arduino Groove Board`
* `Servo Motor`
* `PIR Motion Sensor`
* `Ultrasonic Sound Sensor`
* `Photoresistor`
* `Piezo Buzzer`
* `RGB LED`
* `Push Button`
* `Bread Board`
 
#### Hardware Component
*The following is a simple system diagram of how the components are connected to each other.*
 
![Parts Diagram](https://i.imgur.com/tIAgg5m.png)
 
The servo would be attached to a door (or place holder object acting as door) 
which rotates in a 90 degree motion. On the backside of the same object, 
the ultrasonic sensor is placed, and is used to check if an object is the 
door's closing path. The motion sensor would be placed at the front of the 
door to detect motion, the LDR is placed outside of the door to detect 
lighting levels and other components are placed near the door (with LEDs 
being visible) to be connected to a breadboard that connects everything to 
the Arduino.
 
When the program is launched, the system is always checking to make
sure it is day time (using the LDR). If it's night, a blue light is emitted from the RGB LED indicating that the system is off.
If it's day time (bright), the rest of the system works 
and the RGB LED turns green to indicate that it is daytime. We then always check for 
an input signal from the PIR motion sensor. If there is a signal, the servo is
then turned on to open a door, the RGB LED turns red and a 'chime' plays 
on the buzzer. After a couple of seconds the door is then rotated back 
using the servo along with the 'chime' played in reverse unless the 
ultrasonic sound sensor detects an object that is close to the backside of the door. 
If there is an object near the door, the servo doesn't close the door. 
Instead a red light begins flashing with a repeated beeping played by the
buzzer (telling you something is blocking the door). If the button is 
pressed, everything turns off and the system is terminated.
 
#### GUI Component
 
When the program begins, a GUI app is launched on the computer.
This GUI contains two buttons at the top, a `toggle system on/off` button and a `force open door` button.
When the `toggle system on/off` button is pressed, the system is turned off until pressed again. 
When the `force door open` button is pressed, the door will open just as it would when a hand motion is detected. The system must be on in order for this button to work.
 
![Buttons](https://i.imgur.com/ooB12T8.png)
 
Additionally, GUI window has a graph that displays a live feed of
the amount of people that use the door. This allows the door owner to track how many people
are entering their store (or room that uses the door) and the times at which this happens.
Every time someone enters the room, the line graph moves up. 
 
*For this picture, the `# of door opens` was set to a max of 10 to make the graph easier to read for demonstration purposes.*
![Graph](https://i.imgur.com/zHCcHDw.png)
 
 
## Implementation
This project was targeted towards local business in our community that may not have the
time or money to implement an industry used door within the store. Despite not being able to physically create this implementation,
I still decided to create diagrams of how this system would operate in a real word setting.
 
I wanted the door to be opened with a metal arm connected to a pivot attached to a servo. This would allow
this system to work on businesses that already have an existing door that opens at 90 degrees.
 
This is how the system works when the door is opened:
 
*Closed state*
![pivot1](https://i.imgur.com/zPOahL0.png!)
 
*Opening state*
![pivot2](https://i.imgur.com/QgTGSv2.png)
 
*Opened state*
![pivot3](https://i.imgur.com/fXsgAd2.png)
 
Here's a 3D model of the system created in TinkerCAD showing the placements of the components on the door.
 
![3dmodel](https://i.imgur.com/Lfs22x4.png)
 
*These diagrams and models are simply prototypes and would have to go through many different re-evaluations to be implemented.* 

