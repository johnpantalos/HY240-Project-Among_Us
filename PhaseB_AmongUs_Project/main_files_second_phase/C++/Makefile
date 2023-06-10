####################################################
#                                                  #
# file: Makefile                                   #
#                                                  #
# @Author:   Skerdi Basha		                   #
# @Version:  1-12-2020                             #
# @email:    sbash@csd.uoc.gr	               	   #
#                                                  #
# Generic Makefile for the needs of project        #
#                                                  #
####################################################

# Declaration of variables
CC = g++
CFLAGS = -Wall -g

# File names	
EXEC = among_us
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
OBJECTS = ${SOURCES:src/%.cpp=obj/%.o}

default: $(EXEC)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include $(OBJECTS:obj/%.o=dep/%.d)
endif
endif

dep/%.d: src/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -M $< | \
		sed 's,[a-zA-Z0-9_\.]*.o:,$(<:src/%.cpp=obj/%.o):,' > $@

obj/%.o: src/%.cpp dep/%.d $(HEADERS)
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf obj dep

distclean: clean
	rm -rf among_us
