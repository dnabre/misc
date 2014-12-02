proc_info - Get time process started
====

You'll fine here example code for getting process information (for a provided pid) on FreeBSD(10.x), NetBSD(6.1.5), and Mac OS X (10.9, Mavericks). I'll add OpenBSD for completeness when I get a chance.

The specific info in the code is the time the process was started, but the data structure retrieved from the kernel has all the rest of the information on the process (there's comment point to the header where the struct is described), you might want. 

Licensed as listed, though wouldn't mind hearing if it was userful to anyone. 


History
==== 


This code came from a stackoverflow question (note, FreeBSD specific): 

[How can a process inquire, when it was started?](http://stackoverflow.com/questions/26391097/how-can-a-process-inquire-when-it-was-started/26752218#26752218)

Stackoverflow user, Mikhail T., provided a good answer that grab some stuff from a sysctl call to 
get the information. This worked perfectly, but it seemed inelegant to me. I figured there should
be a way to access this information through a nice API of some sort. 

Two hours of reading through the source for ps(1) and hacking around, and I had some code that
used the libkvm (Kernel Data Access Library) to get the information.

The basic way this works is to grab kinfo_proc struct based on its pid. This struct contains tons
of information on the process, everything that ps can show you and more. 

After getting it working, I was curious whether the libkvm API was consistant across BSDs. It's pretty close, but not exactly. The main differnce is details of field names/types of the kinfo_proc struct. This also lead me to put together working versions for NetBSD
