LIBRARIES = \
	IpolACEPlugin \
	IpolLSDPlugin \
	IpolSCAPlugin \
	IpolTVDPlugin 
	
SHELL = /bin/bash
	
all: 
	for i in ${LIBRARIES}; do \
		make -C $$i; \
	done
	