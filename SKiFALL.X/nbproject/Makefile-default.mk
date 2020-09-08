#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c BotHSM.c TemplateES_Main.c EventChecker.c Stepper.c Ping.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/361624770/AD.o ${OBJECTDIR}/_ext/361624770/BOARD.o ${OBJECTDIR}/_ext/361624770/Beacon.o ${OBJECTDIR}/_ext/361624770/Bumpers.o ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o ${OBJECTDIR}/_ext/361624770/ES_Framework.o ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o ${OBJECTDIR}/_ext/361624770/ES_PostList.o ${OBJECTDIR}/_ext/361624770/ES_Queue.o ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o ${OBJECTDIR}/_ext/361624770/ES_Timers.o ${OBJECTDIR}/_ext/361624770/Gun.o ${OBJECTDIR}/_ext/361624770/IO_Ports.o ${OBJECTDIR}/_ext/361624770/LED.o ${OBJECTDIR}/_ext/361624770/Motors.o ${OBJECTDIR}/_ext/361624770/Tape.o ${OBJECTDIR}/_ext/361624770/Trackwire.o ${OBJECTDIR}/_ext/361624770/pwm.o ${OBJECTDIR}/_ext/361624770/serial.o ${OBJECTDIR}/_ext/361624770/timers.o ${OBJECTDIR}/BotHSM.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/EventChecker.o ${OBJECTDIR}/Stepper.o ${OBJECTDIR}/Ping.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/361624770/AD.o.d ${OBJECTDIR}/_ext/361624770/BOARD.o.d ${OBJECTDIR}/_ext/361624770/Beacon.o.d ${OBJECTDIR}/_ext/361624770/Bumpers.o.d ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/361624770/ES_Framework.o.d ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/361624770/ES_PostList.o.d ${OBJECTDIR}/_ext/361624770/ES_Queue.o.d ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d ${OBJECTDIR}/_ext/361624770/ES_Timers.o.d ${OBJECTDIR}/_ext/361624770/Gun.o.d ${OBJECTDIR}/_ext/361624770/IO_Ports.o.d ${OBJECTDIR}/_ext/361624770/LED.o.d ${OBJECTDIR}/_ext/361624770/Motors.o.d ${OBJECTDIR}/_ext/361624770/Tape.o.d ${OBJECTDIR}/_ext/361624770/Trackwire.o.d ${OBJECTDIR}/_ext/361624770/pwm.o.d ${OBJECTDIR}/_ext/361624770/serial.o.d ${OBJECTDIR}/_ext/361624770/timers.o.d ${OBJECTDIR}/BotHSM.o.d ${OBJECTDIR}/TemplateES_Main.o.d ${OBJECTDIR}/EventChecker.o.d ${OBJECTDIR}/Stepper.o.d ${OBJECTDIR}/Ping.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/361624770/AD.o ${OBJECTDIR}/_ext/361624770/BOARD.o ${OBJECTDIR}/_ext/361624770/Beacon.o ${OBJECTDIR}/_ext/361624770/Bumpers.o ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o ${OBJECTDIR}/_ext/361624770/ES_Framework.o ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o ${OBJECTDIR}/_ext/361624770/ES_PostList.o ${OBJECTDIR}/_ext/361624770/ES_Queue.o ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o ${OBJECTDIR}/_ext/361624770/ES_Timers.o ${OBJECTDIR}/_ext/361624770/Gun.o ${OBJECTDIR}/_ext/361624770/IO_Ports.o ${OBJECTDIR}/_ext/361624770/LED.o ${OBJECTDIR}/_ext/361624770/Motors.o ${OBJECTDIR}/_ext/361624770/Tape.o ${OBJECTDIR}/_ext/361624770/Trackwire.o ${OBJECTDIR}/_ext/361624770/pwm.o ${OBJECTDIR}/_ext/361624770/serial.o ${OBJECTDIR}/_ext/361624770/timers.o ${OBJECTDIR}/BotHSM.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/EventChecker.o ${OBJECTDIR}/Stepper.o ${OBJECTDIR}/Ping.o

# Source Files
SOURCEFILES=C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c BotHSM.c TemplateES_Main.c EventChecker.c Stepper.c Ping.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX320F128H
ProjectDir="C:\Users\jquiamba\Documents\SKiFALL\SKiFALL.X"
ProjectName=SKiFALL
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\Users\jquiamba\Documents\SKiFALL\CMPE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/361624770/AD.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/AD.o.d" -o ${OBJECTDIR}/_ext/361624770/AD.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/BOARD.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/BOARD.o.d" -o ${OBJECTDIR}/_ext/361624770/BOARD.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Beacon.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Beacon.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Beacon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Beacon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Beacon.o.d" -o ${OBJECTDIR}/_ext/361624770/Beacon.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Bumpers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Bumpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Bumpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Bumpers.o.d" -o ${OBJECTDIR}/_ext/361624770/Bumpers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Framework.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Framework.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_PostList.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_PostList.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Queue.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Queue.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_TattleTale.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Timers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Timers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Gun.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Gun.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Gun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Gun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Gun.o.d" -o ${OBJECTDIR}/_ext/361624770/Gun.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/IO_Ports.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/361624770/IO_Ports.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/LED.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/LED.o.d" -o ${OBJECTDIR}/_ext/361624770/LED.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Motors.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Motors.o.d" -o ${OBJECTDIR}/_ext/361624770/Motors.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Tape.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Tape.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Tape.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Tape.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Tape.o.d" -o ${OBJECTDIR}/_ext/361624770/Tape.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Trackwire.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Trackwire.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Trackwire.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Trackwire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Trackwire.o.d" -o ${OBJECTDIR}/_ext/361624770/Trackwire.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/pwm.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/pwm.o.d" -o ${OBJECTDIR}/_ext/361624770/pwm.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/serial.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/serial.o.d" -o ${OBJECTDIR}/_ext/361624770/serial.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/timers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/timers.o.d" -o ${OBJECTDIR}/_ext/361624770/timers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BotHSM.o: BotHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BotHSM.o.d 
	@${RM} ${OBJECTDIR}/BotHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/BotHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/BotHSM.o.d" -o ${OBJECTDIR}/BotHSM.o BotHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/EventChecker.o: EventChecker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/EventChecker.o 
	@${FIXDEPS} "${OBJECTDIR}/EventChecker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/EventChecker.o.d" -o ${OBJECTDIR}/EventChecker.o EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Ping.o: Ping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ping.o.d 
	@${RM} ${OBJECTDIR}/Ping.o 
	@${FIXDEPS} "${OBJECTDIR}/Ping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/Ping.o.d" -o ${OBJECTDIR}/Ping.o Ping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/361624770/AD.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/AD.o.d" -o ${OBJECTDIR}/_ext/361624770/AD.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/BOARD.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/BOARD.o.d" -o ${OBJECTDIR}/_ext/361624770/BOARD.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Beacon.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Beacon.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Beacon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Beacon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Beacon.o.d" -o ${OBJECTDIR}/_ext/361624770/Beacon.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Beacon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Bumpers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Bumpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Bumpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Bumpers.o.d" -o ${OBJECTDIR}/_ext/361624770/Bumpers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_CheckEvents.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Framework.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Framework.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_KeyboardInput.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_PostList.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_PostList.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Queue.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Queue.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_TattleTale.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_TattleTale.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/ES_Timers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/361624770/ES_Timers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Gun.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Gun.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Gun.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Gun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Gun.o.d" -o ${OBJECTDIR}/_ext/361624770/Gun.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Gun.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/IO_Ports.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/361624770/IO_Ports.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/LED.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/LED.o.d" -o ${OBJECTDIR}/_ext/361624770/LED.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Motors.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Motors.o.d" -o ${OBJECTDIR}/_ext/361624770/Motors.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Tape.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Tape.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Tape.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Tape.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Tape.o.d" -o ${OBJECTDIR}/_ext/361624770/Tape.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Tape.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/Trackwire.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/Trackwire.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/Trackwire.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/Trackwire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/Trackwire.o.d" -o ${OBJECTDIR}/_ext/361624770/Trackwire.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/Trackwire.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/pwm.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/pwm.o.d" -o ${OBJECTDIR}/_ext/361624770/pwm.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/serial.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/serial.o.d" -o ${OBJECTDIR}/_ext/361624770/serial.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/361624770/timers.o: C\:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/361624770" 
	@${RM} ${OBJECTDIR}/_ext/361624770/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/361624770/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/361624770/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/361624770/timers.o.d" -o ${OBJECTDIR}/_ext/361624770/timers.o C:/Users/jquiamba/Documents/SKiFALL/CMPE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BotHSM.o: BotHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BotHSM.o.d 
	@${RM} ${OBJECTDIR}/BotHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/BotHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/BotHSM.o.d" -o ${OBJECTDIR}/BotHSM.o BotHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/EventChecker.o: EventChecker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/EventChecker.o 
	@${FIXDEPS} "${OBJECTDIR}/EventChecker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/EventChecker.o.d" -o ${OBJECTDIR}/EventChecker.o EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Ping.o: Ping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ping.o.d 
	@${RM} ${OBJECTDIR}/Ping.o 
	@${FIXDEPS} "${OBJECTDIR}/Ping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/Users/jquiamba/Documents/SKiFALL/CMPE118/include" -MMD -MF "${OBJECTDIR}/Ping.o.d" -o ${OBJECTDIR}/Ping.o Ping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/Users/jquiamba/Documents/SKiFALL/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/Users/jquiamba/Documents/SKiFALL/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SKiFALL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\Users\jquiamba\Documents\SKiFALL\CMPE118\scripts\Enum_To_String.py]"
	@python C:\Users\jquiamba\Documents\SKiFALL\CMPE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
