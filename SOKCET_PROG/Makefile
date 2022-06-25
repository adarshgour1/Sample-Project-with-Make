#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
# 'make run' will run you main file and generate log file in log folder
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g3

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= $(PWD)/output

# define source directory
SRC		:= $(PWD)/src

# define source directory
OBJ		:= $(PWD)/obj

# define include directory header files
INCLUDE	:= $(PWD)/include

# define lib directory
LIB		:= $(PWD)/lib

#log directory
LOG = $(PWD)/log

#time stamp
CURRENT_TIME = $(shell date "+%Y%m%d-%H.%M.%S")

SOURCEDIRS	:= $(shell find $(SRC) -type d)
OBJDIRS		:= $(shell find $(OBJ) -type d)
LOGDIRS		:= $(shell find $(LOG) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(shell find $(SOURCEDIRS)/* -maxdepth 1 | grep -v main)


# define the C object files 
OBJECTS		:= $(SOURCES:$(SOURCEDIRS)/%.cpp=$(OBJDIRS)/%.o)


all: $(OBJECTS)
	@tput setaf 27
	@echo
	@echo -----------------Generating Binaries------------------------------
	@echo
	@tput setaf 213
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUT)/SENDER $(SOURCEDIRS)/sender_main.cpp $(OBJECTS) $(LFLAGS) $(LIBS)
	@echo
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUT)/RECIVER $(SOURCEDIRS)/reciver_main.cpp $(OBJECTS) $(LFLAGS) $(LIBS)
	@tput setaf 27
	@echo
	@echo -----------------All Binaries Generated--------------------------
	@echo
	@tput setaf 7

$(LIBDIRS)/comnLib.a : $(OBJECTS)

$(OBJECTS):$(SOURCES)
	@tput setaf 27
	@echo
	@echo -----------------Generating Object Files------------------------------
	@echo
	@tput setaf 3
	@echo $< : $@
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@
	@tput setaf 27
	@echo
	@echo -----------------Object Files Generated------------------------------
	@echo
	@tput setaf 7

.PHONY: clean
clean:
	$(RM) $(OBJDIRS)/*.o
	@echo Cleanup complete!

run:
	$(RM) log/*.log
	@echo ----------------SENDER started--------------
	@./output/SENDER > $(LOGDIRS)/SENDER-$(CURRENT_TIME).log 2>&1 &
	@echo ----------------RECIVER started--------------
	@./output/RECIVER > $(LOGDIRS)/RECIVER-$(CURRENT_TIME).log 2>&1 &

