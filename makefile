CC=g++
FLAG=-Wall -Wextra -std=c++17
EX_FLAG=-O2
# EX_FLAG=-g -D EXEC_POLICE_SERIAL
TARGETS=tmp/common.o tmp/vec.o tmp/ray.o tmp/hittable.o tmp/hittable_objects.o tmp/camera.o tmp/material.o tmp/thread_pool.o
LIBS=pthread


# executables
bin/main: tmp/main.o
	$(CC) \
		tmp/main.o $(TARGETS) \
		-l $(LIBS) \
		-o bin/main

# temporary compile output
tmp/main.o: src/main.cpp $(TARGETS)
	$(CC) src/main.cpp $(FLAG) $(EX_FLAG) -c -o tmp/main.o
tmp/common.o: src/common.hpp src/common.cpp
	$(CC) src/common.cpp $(FLAG) $(EX_FLAG) -c -o tmp/common.o
tmp/vec.o: src/vec.hpp src/vec.cpp
	$(CC) src/vec.cpp $(FLAG) $(EX_FLAG) -c -o tmp/vec.o
tmp/ray.o: src/ray.hpp src/ray.cpp
	$(CC) src/ray.cpp $(FLAG) $(EX_FLAG) -c -o tmp/ray.o
tmp/hittable.o: src/hittable.hpp src/hittable.cpp
	$(CC) src/hittable.cpp $(FLAG) $(EX_FLAG) -c -o tmp/hittable.o
tmp/hittable_objects.o: src/hittable_objects.hpp src/hittable_objects.cpp
	$(CC) src/hittable_objects.cpp $(FLAG) $(EX_FLAG) -c -o tmp/hittable_objects.o
tmp/camera.o: src/camera.hpp src/camera.cpp
	$(CC) src/camera.cpp $(FLAG) $(EX_FLAG) -c -o tmp/camera.o
tmp/material.o: src/material.hpp src/material.cpp
	$(CC) src/material.cpp $(FLAG) $(EX_FLAG) -c -o tmp/material.o
tmp/thread_pool.o: src/thread_pool.hpp src/thread_pool.cpp
	$(CC) src/thread_pool.cpp $(FLAG) $(EX_FLAG) -c -o tmp/thread_pool.o



# clean up
purge:
	rm tmp/* -rf
	rm bin/* -rf
	rm dist/* -rf

