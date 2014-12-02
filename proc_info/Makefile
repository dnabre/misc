LDFLAGS = -lkvm
CFLAGS = -Wall 
all: proc_info
proc_info: proc_info.o
proc_info.o: proc_info.c

netbsd: netbsd_proc_info
netbsd_proc_info: netbsd_proc_info.o
netbsd_proc_info.o: netbsd_proc_info.c

mac: mac_proc_info
mac_proc_info: mac_proc_info.o
	${CC} mac_proc_info.o  ${CFLAGS} -o mac_proc_info
mac_proc_info.o: mac_proc_info.c
	${CC} mac_proc_info.c -c ${CFLAGS} -o mac_proc_info.o



clean:
	rm -f proc_info
	rm -f proc_info.o
	rm -f netbsd_proc_info
	rm -f netbsd_proc_info.o
	rm -f mac_proc_info
	rm -f mac_proc_info.o
