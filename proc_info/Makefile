LDFLAGS = -lkvm
CFLAGS = -Wall 

help: 
	echo "Must specific OS target {linux,netbsd,openbsd,freebsd,mac}"

linux: linux_proc_info
linux_proc: linux_proc_info
linux_proc_info: linux_proc_info.o
linux_proc_info.o: linux_proc_info.c

netbsd: netbsd_proc_info
netbsd_proc_info: netbsd_proc_info.o
netbsd_proc_info.o: netbsd_proc_info.c

mac: mac_proc_info
mac_proc_info: mac_proc_info.o
	${CC} mac_proc_info.o  ${CFLAGS} -o mac_proc_info
mac_proc_info.o: mac_proc_info.c
	${CC} mac_proc_info.c -c ${CFLAGS} -o mac_proc_info.o

freebsd: freebsd_proc_info
freebsd_proc_info: freebsd_proc_info.o
freebsdbsd_proc_info.o: freebsd_proc_info.c

openbsd: openbsd_proc_info
openbsd_proc_info: openbsd_proc_info.o
openbsd_proc_info.o: openbsd_proc_info.c



clean:
	rm -f openbsd_proc_info
	rm -f openbsd_proc_info.o
	rm -f freebsd_proc_info
	rm -f freebsd_proc_info.o
	rm -f mac_proc_info
	rm -f mac_proc_info.o
	rm -f linux_proc_info
	rm -f linux_proc_info.o
	rm -f netbsd_proc_info
	rm -f netbsd_proc_info.o
	
