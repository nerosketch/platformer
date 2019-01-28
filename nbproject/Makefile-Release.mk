#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DebugRectSprite.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/GameStage.o \
	${OBJECTDIR}/InputEvent.o \
	${OBJECTDIR}/Level.o \
	${OBJECTDIR}/Light.o \
	${OBJECTDIR}/Menu.o \
	${OBJECTDIR}/ObjectLoader.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/SoundManager.o \
	${OBJECTDIR}/StageManager.o \
	${OBJECTDIR}/StartMenu.o \
	${OBJECTDIR}/TextButton.o \
	${OBJECTDIR}/TextPanel.o \
	${OBJECTDIR}/TiledLevel.o \
	${OBJECTDIR}/TiledSprite.o \
	${OBJECTDIR}/Unit.o \
	${OBJECTDIR}/base.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/resources.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`pkg-config --cflags sdl2` 
CXXFLAGS=`pkg-config --cflags sdl2` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib/oxygine-framework/libs ./lib/oxygine-framework/liboxygine-framework.a ./lib/oxygine-framework/./lib/oxygine-sound/liboxygine-sound.a ./lib/oxygine-sound/tremor/libtremor.a lib/oxygine-freetype/liboxygine-freetype.a ./lib/oxygine-framework/libs/SDL2main.lib -lpthread -lGL -lglut -lGLU -lpng -lz -lSDL2 -ljpeg -logg -lopenal -lfreetype

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: ./lib/oxygine-framework/liboxygine-framework.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: ./lib/oxygine-framework/./lib/oxygine-sound/liboxygine-sound.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: ./lib/oxygine-sound/tremor/libtremor.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: lib/oxygine-freetype/liboxygine-freetype.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: ./lib/oxygine-framework/libs/SDL2main.lib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/platphormer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/DebugRectSprite.o: DebugRectSprite.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DebugRectSprite.o DebugRectSprite.cpp

${OBJECTDIR}/Game.o: Game.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/GameStage.o: GameStage.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GameStage.o GameStage.cpp

${OBJECTDIR}/InputEvent.o: InputEvent.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InputEvent.o InputEvent.cpp

${OBJECTDIR}/Level.o: Level.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Level.o Level.cpp

${OBJECTDIR}/Light.o: Light.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Light.o Light.cpp

${OBJECTDIR}/Menu.o: Menu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Menu.o Menu.cpp

${OBJECTDIR}/ObjectLoader.o: ObjectLoader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ObjectLoader.o ObjectLoader.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/SoundManager.o: SoundManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SoundManager.o SoundManager.cpp

${OBJECTDIR}/StageManager.o: StageManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StageManager.o StageManager.cpp

${OBJECTDIR}/StartMenu.o: StartMenu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StartMenu.o StartMenu.cpp

${OBJECTDIR}/TextButton.o: TextButton.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TextButton.o TextButton.cpp

${OBJECTDIR}/TextPanel.o: TextPanel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TextPanel.o TextPanel.cpp

${OBJECTDIR}/TiledLevel.o: TiledLevel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TiledLevel.o TiledLevel.cpp

${OBJECTDIR}/TiledSprite.o: TiledSprite.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TiledSprite.o TiledSprite.cpp

${OBJECTDIR}/Unit.o: Unit.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Unit.o Unit.cpp

${OBJECTDIR}/base.o: base.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base.o base.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/resources.o: resources.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I./lib/oxygine-framework/oxygine/src -I./lib/oxygine-sound/src -I./lib/oxygine-freetype/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/resources.o resources.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
