DIR_SOURCES_SOCA = -IServerPlugin -IServerPlugin/src  -I../../Soca/src  -IServerPlugin/LMT/include


all:
	make -C ../../Soca
	metil_comp -ne -j1 -O3 -g3 $(DIR_SOURCES_SOCA) -lQtGui ServerPlugin/src/main.cpp
