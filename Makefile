CXX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -std=c++11 
EXEC = firewall.exe
HFILES = string.h field.h ip.h port.h 
CPPFILES = string.cpp field.cpp ip.cpp port.cpp
RM = rm -rf *.o libfirewall.so firewall.exe


all:firewall

libfirewall.so: $(CPPFILES) $(HFILES)
	$(CXX) $(CXXFLAGS) -fpic -shared $(CPPFILES) -o libfirewall.so

firewall: libfirewall.so string.cpp field.cpp ip.cpp port.cpp 
	$(CXXLINK) $(CXXFLAGS) main.cpp -o firewall.exe -lfirewall -linput -L.

clean:
	$(RM)