cplusplus-cpu-mem-monitor
=========================

IdeaConnect C++ CPU and Memory monitor is a simple tool written in C plus plus which monitors CPU and Memory usage on a Linux-based server and exposes the data through a simple UDP server allowing to create a variety of monitoring applications like dedicated dashboards.

# Requirements
App was used on both CentOS 6 and Debian Squeeze systems. To use you will require libgtop lib. You can download it using default package manager:


    yum install libgtop2
	On Debian use apt-get instead of yum.
	
Without that you will get:

    ./cpumemmon: error while loading shared libraries: libgtop-2.0.so.7: cannot open shared object file: No such file or directory

# Compile from Source Code
To compile from source code you can use the line:

    g++ -I/usr/include/libgtop-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/glib-2.0 -Wall cpumemmonitor.c -o cpumemmon -lgtop-2.0

If you get error:

    cpumemmonitor.c:10:21: error: glibtop.h: No such file or directory
    cpumemmonitor.c:11:25: error: glibtop/cpu.h: No such file or directory
    cpumemmonitor.c:12:25: error: glibtop/mem.h: No such file or directory

It means that your system lacks libgtop2-dev lib. You can install it using package manager:

	yum install libgtop2-devel
	
In case you are still getting the error check your includes folder (/usr/include). It may be also (/usr/local/include).
If you have a 32 bit system most likely you will need to point glib lib in the folder /usr/lib (or /usr/local/lib) instead of /usr/lib64.
Of course you may need to install glib (and glib-devel).

# Running
If you want app to run in the background just type

    nohup ./cpumemmon &

To turn it off simply kill it using 'kill -9 <pid>'.

App responds to any data on UDP port: 8095

By default app listens on any interface on port 8095

# How to change the port?
Simply modify the line:

    servaddr.sin_port=htons(8905);

to any other - for example for 6666:

    servaddr.sin_port=htons(6666);

If you experience any problems feel free to contact me: bartosz@ideaconnect.pl and I may provide assistance.

Thank you,
Bartosz
