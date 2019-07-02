dienstplan.exe: dienst.cc
	g++ -O1 dienst.cc -o dienstplan.exe
	
clean:
	rm dienstplan.exe
	
