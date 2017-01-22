# --------------------------------------------------------------  
# (C)Copyright 2001,2007,                                         
# International Business Machines Corporation,                    
# Sony Computer Entertainment, Incorporated,                      
# Toshiba Corporation,                                            
#                                                                 
# All Rights Reserved.                                            
# --------------------------------------------------------------  
# PROLOG END TAG zYx                                              

########################################################################
#			Target
########################################################################

PROGRAM_ppu	= multiply


########################################################################
#			Local Defines
########################################################################

IMPORTS 	= ../spu/multiply_spu.a -lspe2 -lpthread


########################################################################
#			make.footer
########################################################################

ifdef CELL_TOP
	include $(CELL_TOP)/buildutils/make.footer
else
	include /opt/cell/sdk/buildutils/make.footer
endif
