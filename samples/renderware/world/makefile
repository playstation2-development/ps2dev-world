###########################################################################
#
# File     : Makefile
#
# Abstract : Command line makefile used to build a RenderWare demo program.
#            This is a GNU Make makefile. A copy of GNU Make is required in 
#            order to use this file.
#
###########################################################################
#
# This file is a product of Criterion Software Ltd.
#
# This file is provided as is with no warranties of any kind and is
# provided without any obligation on Criterion Software Ltd. or Canon Inc. 
# to assist in its use or modification.
#
# Criterion Software Ltd. will not, under any circumstances, be liable for 
# any lost revenue or other damages arising from the use of this file.
#
# Copyright (c) 2000 Criterion Software Ltd.
# All Rights Reserved.
#
# RenderWare is a trademark of Canon Inc.
#
###########################################################################

# Define the projects to be built

DEMO = world

# include common makefile options

include ../../makeopt

CSRC =	$(SRC)/main.c		\
	$(SRC)/$(RWOS)/events.c	\
	$(COMMON)/camera.c	\
	$(COMMON)/menu.c	\
	$(SRC)/world.c		

# Add skeleton files

CSRC += $(SKEL)/skeleton.c	\
	$(SKELPS)/$(RWOS).c     \
	$(SKELSRC)

ifeq ($(RWMETRICS), 1)
CSRC += $(SKEL)/vecfont.c   \
        $(SKEL)/metrics.c
endif

RWLIBS += $(RWLIBDIR)/$(LP)rtimport.$(L) \
	$(RWLIBDIR)/$(LP)rtcharse.$(L)   \
	$(RWLIBDIR)/$(LP)rtbmp.$(L)	\
	$(RWLIBDIR)/$(LP)rtpng.$(L)	 \
	$(RWLIBDIR)/$(LP)rpworld.$(L)	 \
	$(RWLIBDIR)/$(LP)rwcore.$(L)	

include ../../maketarg


