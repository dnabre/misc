Example of a basic unix daemon
This is a very basic daemon that grab a large hunk of private anonymous memory
and sits on it. 

When killed, it writes a file "ps_$TIMESTAMP.log" with teh contents of "ps
aux" in it.

The purpose of this program is be a big juicy target for the OOM-killer and to
take a snapshot of process/cpu/ram information as it dies. 


