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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c Motors.c Bumpers.c Tape.c Stepper.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1323505475/AD.o ${OBJECTDIR}/_ext/1323505475/BOARD.o ${OBJECTDIR}/_ext/1323505475/LED.o ${OBJECTDIR}/_ext/1323505475/RC_Servo.o ${OBJECTDIR}/_ext/1323505475/pwm.o ${OBJECTDIR}/_ext/1323505475/serial.o ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o ${OBJECTDIR}/_ext/1323505475/IO_Ports.o ${OBJECTDIR}/Motors.o ${OBJECTDIR}/Bumpers.o ${OBJECTDIR}/Tape.o ${OBJECTDIR}/Stepper.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1323505475/AD.o.d ${OBJECTDIR}/_ext/1323505475/BOARD.o.d ${OBJECTDIR}/_ext/1323505475/LED.o.d ${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d ${OBJECTDIR}/_ext/1323505475/pwm.o.d ${OBJECTDIR}/_ext/1323505475/serial.o.d ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d ${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d ${OBJECTDIR}/Motors.o.d ${OBJECTDIR}/Bumpers.o.d ${OBJECTDIR}/Tape.o.d ${OBJECTDIR}/Stepper.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1323505475/AD.o ${OBJECTDIR}/_ext/1323505475/BOARD.o ${OBJECTDIR}/_ext/1323505475/LED.o ${OBJECTDIR}/_ext/1323505475/RC_Servo.o ${OBJECTDIR}/_ext/1323505475/pwm.o ${OBJECTDIR}/_ext/1323505475/serial.o ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o ${OBJECTDIR}/_ext/1323505475/IO_Ports.o ${OBJECTDIR}/Motors.o ${OBJECTDIR}/Bumpers.o ${OBJECTDIR}/Tape.o ${OBJECTDIR}/Stepper.o

# Source Files
SOURCEFILES=C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c Motors.c Bumpers.c Tape.c Stepper.c



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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\Users\jquiamba\Documents\Finale\CMPE118\bootloader320.ld"
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
${OBJECTDIR}/_ext/1323505475/AD.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/AD.o.d" -o ${OBJECTDIR}/_ext/1323505475/AD.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/BOARD.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/BOARD.o.d" -o ${OBJECTDIR}/_ext/1323505475/BOARD.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/LED.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/LED.o.d" -o ${OBJECTDIR}/_ext/1323505475/LED.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/RC_Servo.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1323505475/RC_Servo.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/pwm.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/pwm.o.d" -o ${OBJECTDIR}/_ext/1323505475/pwm.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/serial.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/serial.o.d" -o ${OBJECTDIR}/_ext/1323505475/serial.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d" -o ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/IO_Ports.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1323505475/IO_Ports.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Motors.o: Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motors.o.d 
	@${RM} ${OBJECTDIR}/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Motors.o.d" -o ${OBJECTDIR}/Motors.o Motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Bumpers.o: Bumpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/Bumpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Bumpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Bumpers.o.d" -o ${OBJECTDIR}/Bumpers.o Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Tape.o: Tape.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Tape.o.d 
	@${RM} ${OBJECTDIR}/Tape.o 
	@${FIXDEPS} "${OBJECTDIR}/Tape.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Tape.o.d" -o ${OBJECTDIR}/Tape.o Tape.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1323505475/AD.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/AD.o.d" -o ${OBJECTDIR}/_ext/1323505475/AD.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/BOARD.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/BOARD.o.d" -o ${OBJECTDIR}/_ext/1323505475/BOARD.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/LED.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/LED.o.d" -o ${OBJECTDIR}/_ext/1323505475/LED.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/RC_Servo.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1323505475/RC_Servo.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/pwm.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/pwm.o.d" -o ${OBJECTDIR}/_ext/1323505475/pwm.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/serial.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/serial.o.d" -o ${OBJECTDIR}/_ext/1323505475/serial.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o.d" -o ${OBJECTDIR}/_ext/1323505475/TestHarnessMain.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/TestHarnessMain.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1323505475/IO_Ports.o: C\:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1323505475" 
	@${RM} ${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323505475/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/1323505475/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1323505475/IO_Ports.o C:/Users/jquiamba/Documents/Finale/Bot_TestHarness.X/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Motors.o: Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Motors.o.d 
	@${RM} ${OBJECTDIR}/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Motors.o.d" -o ${OBJECTDIR}/Motors.o Motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Bumpers.o: Bumpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/Bumpers.o 
	@${FIXDEPS} "${OBJECTDIR}/Bumpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Bumpers.o.d" -o ${OBJECTDIR}/Bumpers.o Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Tape.o: Tape.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Tape.o.d 
	@${RM} ${OBJECTDIR}/Tape.o 
	@${FIXDEPS} "${OBJECTDIR}/Tape.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Tape.o.d" -o ${OBJECTDIR}/Tape.o Tape.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/Users/jquiamba/Documents/Finale/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/Users/jquiamba/Documents/Finale/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Bot_TestHarness.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


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
