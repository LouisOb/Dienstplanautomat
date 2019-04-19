dienstplan.exe: dienst.cc
	g++ dienst.cc -o dienstplan.exe
	
clean:
	rm dienstplan.exe
	
