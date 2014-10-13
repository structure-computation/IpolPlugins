LIBRARIES = \
	IploACEPlugin \
	IploLSDPlugin \
	IploSCAPlugin \
	IploTVDPlugin 
	
SHELL = /bin/bash
	
all: 
	for i in ${LIBRARIES}; do \
		make -C $$i; \
	done
	