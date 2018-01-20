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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=main_Logic.c RTC.c Initialization.c UART.c OneSecond_Function.c RPM_Measurement.c ISR.c state.c ERROR_HANDLING.c RAMP_UP.c PITCHING.c RS485_COMMUNICATION.c Power_Meter.c SLIP_CALCULATIONS.c EEPROM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main_Logic.p1 ${OBJECTDIR}/RTC.p1 ${OBJECTDIR}/Initialization.p1 ${OBJECTDIR}/UART.p1 ${OBJECTDIR}/OneSecond_Function.p1 ${OBJECTDIR}/RPM_Measurement.p1 ${OBJECTDIR}/ISR.p1 ${OBJECTDIR}/state.p1 ${OBJECTDIR}/ERROR_HANDLING.p1 ${OBJECTDIR}/RAMP_UP.p1 ${OBJECTDIR}/PITCHING.p1 ${OBJECTDIR}/RS485_COMMUNICATION.p1 ${OBJECTDIR}/Power_Meter.p1 ${OBJECTDIR}/SLIP_CALCULATIONS.p1 ${OBJECTDIR}/EEPROM.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main_Logic.p1.d ${OBJECTDIR}/RTC.p1.d ${OBJECTDIR}/Initialization.p1.d ${OBJECTDIR}/UART.p1.d ${OBJECTDIR}/OneSecond_Function.p1.d ${OBJECTDIR}/RPM_Measurement.p1.d ${OBJECTDIR}/ISR.p1.d ${OBJECTDIR}/state.p1.d ${OBJECTDIR}/ERROR_HANDLING.p1.d ${OBJECTDIR}/RAMP_UP.p1.d ${OBJECTDIR}/PITCHING.p1.d ${OBJECTDIR}/RS485_COMMUNICATION.p1.d ${OBJECTDIR}/Power_Meter.p1.d ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d ${OBJECTDIR}/EEPROM.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main_Logic.p1 ${OBJECTDIR}/RTC.p1 ${OBJECTDIR}/Initialization.p1 ${OBJECTDIR}/UART.p1 ${OBJECTDIR}/OneSecond_Function.p1 ${OBJECTDIR}/RPM_Measurement.p1 ${OBJECTDIR}/ISR.p1 ${OBJECTDIR}/state.p1 ${OBJECTDIR}/ERROR_HANDLING.p1 ${OBJECTDIR}/RAMP_UP.p1 ${OBJECTDIR}/PITCHING.p1 ${OBJECTDIR}/RS485_COMMUNICATION.p1 ${OBJECTDIR}/Power_Meter.p1 ${OBJECTDIR}/SLIP_CALCULATIONS.p1 ${OBJECTDIR}/EEPROM.p1

# Source Files
SOURCEFILES=main_Logic.c RTC.c Initialization.c UART.c OneSecond_Function.c RPM_Measurement.c ISR.c state.c ERROR_HANDLING.c RAMP_UP.c PITCHING.c RS485_COMMUNICATION.c Power_Meter.c SLIP_CALCULATIONS.c EEPROM.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F67K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main_Logic.p1: main_Logic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_Logic.p1.d 
	@${RM} ${OBJECTDIR}/main_Logic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main_Logic.p1  main_Logic.c 
	@-${MV} ${OBJECTDIR}/main_Logic.d ${OBJECTDIR}/main_Logic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_Logic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RTC.p1: RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTC.p1.d 
	@${RM} ${OBJECTDIR}/RTC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RTC.p1  RTC.c 
	@-${MV} ${OBJECTDIR}/RTC.d ${OBJECTDIR}/RTC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RTC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Initialization.p1: Initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initialization.p1.d 
	@${RM} ${OBJECTDIR}/Initialization.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Initialization.p1  Initialization.c 
	@-${MV} ${OBJECTDIR}/Initialization.d ${OBJECTDIR}/Initialization.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Initialization.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/UART.p1: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.p1.d 
	@${RM} ${OBJECTDIR}/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/UART.p1  UART.c 
	@-${MV} ${OBJECTDIR}/UART.d ${OBJECTDIR}/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/OneSecond_Function.p1: OneSecond_Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OneSecond_Function.p1.d 
	@${RM} ${OBJECTDIR}/OneSecond_Function.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/OneSecond_Function.p1  OneSecond_Function.c 
	@-${MV} ${OBJECTDIR}/OneSecond_Function.d ${OBJECTDIR}/OneSecond_Function.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/OneSecond_Function.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RPM_Measurement.p1: RPM_Measurement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RPM_Measurement.p1.d 
	@${RM} ${OBJECTDIR}/RPM_Measurement.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RPM_Measurement.p1  RPM_Measurement.c 
	@-${MV} ${OBJECTDIR}/RPM_Measurement.d ${OBJECTDIR}/RPM_Measurement.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RPM_Measurement.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ISR.p1: ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ISR.p1.d 
	@${RM} ${OBJECTDIR}/ISR.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ISR.p1  ISR.c 
	@-${MV} ${OBJECTDIR}/ISR.d ${OBJECTDIR}/ISR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ISR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/state.p1: state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state.p1.d 
	@${RM} ${OBJECTDIR}/state.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/state.p1  state.c 
	@-${MV} ${OBJECTDIR}/state.d ${OBJECTDIR}/state.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/state.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ERROR_HANDLING.p1: ERROR_HANDLING.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ERROR_HANDLING.p1.d 
	@${RM} ${OBJECTDIR}/ERROR_HANDLING.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ERROR_HANDLING.p1  ERROR_HANDLING.c 
	@-${MV} ${OBJECTDIR}/ERROR_HANDLING.d ${OBJECTDIR}/ERROR_HANDLING.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ERROR_HANDLING.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RAMP_UP.p1: RAMP_UP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RAMP_UP.p1.d 
	@${RM} ${OBJECTDIR}/RAMP_UP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RAMP_UP.p1  RAMP_UP.c 
	@-${MV} ${OBJECTDIR}/RAMP_UP.d ${OBJECTDIR}/RAMP_UP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RAMP_UP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PITCHING.p1: PITCHING.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PITCHING.p1.d 
	@${RM} ${OBJECTDIR}/PITCHING.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PITCHING.p1  PITCHING.c 
	@-${MV} ${OBJECTDIR}/PITCHING.d ${OBJECTDIR}/PITCHING.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PITCHING.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RS485_COMMUNICATION.p1: RS485_COMMUNICATION.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485_COMMUNICATION.p1.d 
	@${RM} ${OBJECTDIR}/RS485_COMMUNICATION.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RS485_COMMUNICATION.p1  RS485_COMMUNICATION.c 
	@-${MV} ${OBJECTDIR}/RS485_COMMUNICATION.d ${OBJECTDIR}/RS485_COMMUNICATION.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RS485_COMMUNICATION.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Power_Meter.p1: Power_Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Power_Meter.p1.d 
	@${RM} ${OBJECTDIR}/Power_Meter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Power_Meter.p1  Power_Meter.c 
	@-${MV} ${OBJECTDIR}/Power_Meter.d ${OBJECTDIR}/Power_Meter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Power_Meter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SLIP_CALCULATIONS.p1: SLIP_CALCULATIONS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d 
	@${RM} ${OBJECTDIR}/SLIP_CALCULATIONS.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SLIP_CALCULATIONS.p1  SLIP_CALCULATIONS.c 
	@-${MV} ${OBJECTDIR}/SLIP_CALCULATIONS.d ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/EEPROM.p1: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/EEPROM.p1  EEPROM.c 
	@-${MV} ${OBJECTDIR}/EEPROM.d ${OBJECTDIR}/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main_Logic.p1: main_Logic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_Logic.p1.d 
	@${RM} ${OBJECTDIR}/main_Logic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main_Logic.p1  main_Logic.c 
	@-${MV} ${OBJECTDIR}/main_Logic.d ${OBJECTDIR}/main_Logic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_Logic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RTC.p1: RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RTC.p1.d 
	@${RM} ${OBJECTDIR}/RTC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RTC.p1  RTC.c 
	@-${MV} ${OBJECTDIR}/RTC.d ${OBJECTDIR}/RTC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RTC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Initialization.p1: Initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initialization.p1.d 
	@${RM} ${OBJECTDIR}/Initialization.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Initialization.p1  Initialization.c 
	@-${MV} ${OBJECTDIR}/Initialization.d ${OBJECTDIR}/Initialization.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Initialization.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/UART.p1: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.p1.d 
	@${RM} ${OBJECTDIR}/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/UART.p1  UART.c 
	@-${MV} ${OBJECTDIR}/UART.d ${OBJECTDIR}/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/OneSecond_Function.p1: OneSecond_Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OneSecond_Function.p1.d 
	@${RM} ${OBJECTDIR}/OneSecond_Function.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/OneSecond_Function.p1  OneSecond_Function.c 
	@-${MV} ${OBJECTDIR}/OneSecond_Function.d ${OBJECTDIR}/OneSecond_Function.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/OneSecond_Function.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RPM_Measurement.p1: RPM_Measurement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RPM_Measurement.p1.d 
	@${RM} ${OBJECTDIR}/RPM_Measurement.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RPM_Measurement.p1  RPM_Measurement.c 
	@-${MV} ${OBJECTDIR}/RPM_Measurement.d ${OBJECTDIR}/RPM_Measurement.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RPM_Measurement.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ISR.p1: ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ISR.p1.d 
	@${RM} ${OBJECTDIR}/ISR.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ISR.p1  ISR.c 
	@-${MV} ${OBJECTDIR}/ISR.d ${OBJECTDIR}/ISR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ISR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/state.p1: state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state.p1.d 
	@${RM} ${OBJECTDIR}/state.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/state.p1  state.c 
	@-${MV} ${OBJECTDIR}/state.d ${OBJECTDIR}/state.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/state.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ERROR_HANDLING.p1: ERROR_HANDLING.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ERROR_HANDLING.p1.d 
	@${RM} ${OBJECTDIR}/ERROR_HANDLING.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ERROR_HANDLING.p1  ERROR_HANDLING.c 
	@-${MV} ${OBJECTDIR}/ERROR_HANDLING.d ${OBJECTDIR}/ERROR_HANDLING.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ERROR_HANDLING.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RAMP_UP.p1: RAMP_UP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RAMP_UP.p1.d 
	@${RM} ${OBJECTDIR}/RAMP_UP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RAMP_UP.p1  RAMP_UP.c 
	@-${MV} ${OBJECTDIR}/RAMP_UP.d ${OBJECTDIR}/RAMP_UP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RAMP_UP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PITCHING.p1: PITCHING.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PITCHING.p1.d 
	@${RM} ${OBJECTDIR}/PITCHING.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PITCHING.p1  PITCHING.c 
	@-${MV} ${OBJECTDIR}/PITCHING.d ${OBJECTDIR}/PITCHING.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PITCHING.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/RS485_COMMUNICATION.p1: RS485_COMMUNICATION.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485_COMMUNICATION.p1.d 
	@${RM} ${OBJECTDIR}/RS485_COMMUNICATION.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/RS485_COMMUNICATION.p1  RS485_COMMUNICATION.c 
	@-${MV} ${OBJECTDIR}/RS485_COMMUNICATION.d ${OBJECTDIR}/RS485_COMMUNICATION.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/RS485_COMMUNICATION.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Power_Meter.p1: Power_Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Power_Meter.p1.d 
	@${RM} ${OBJECTDIR}/Power_Meter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Power_Meter.p1  Power_Meter.c 
	@-${MV} ${OBJECTDIR}/Power_Meter.d ${OBJECTDIR}/Power_Meter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Power_Meter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SLIP_CALCULATIONS.p1: SLIP_CALCULATIONS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d 
	@${RM} ${OBJECTDIR}/SLIP_CALCULATIONS.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SLIP_CALCULATIONS.p1  SLIP_CALCULATIONS.c 
	@-${MV} ${OBJECTDIR}/SLIP_CALCULATIONS.d ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SLIP_CALCULATIONS.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/EEPROM.p1: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/EEPROM.p1  EEPROM.c 
	@-${MV} ${OBJECTDIR}/EEPROM.d ${OBJECTDIR}/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/RT01-Logic_RV2_-20.01.18.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
