Notification-Notifier
=====================
An unnecessarily complicated series of programs for an incredibly basic result: showing that you received a 
notification!

When a notification arrives, the phone lets the computer know by sending a http request, using tasker. When a page
is opened, computer looks at the request to see what kind of notification it was, and then lets the arduino know 
by sending a char over serial. Then arduino starts to display the notification on the connected LEDs. 

Server.py should be running on the computer. Don't forget to change the ip to your computer's ip address, and
the serial port to the port arduino is connected.

Tasker part is left for your own imagination and needs. Of course you can change this, but by default you should
send requests using "http://x.x.x.x/?mars=X" and the program running on the computer will act accordingly.
