%% --------------------------------------------------------------  
%% (C)Copyright 2001,2007,                                         
%% International Business Machines Corporation,                    
%% Sony Computer Entertainment, Incorporated,                      
%% Toshiba Corporation,                                            
%%                                                                 
%% All Rights Reserved.                                            
%% --------------------------------------------------------------  
%% PROLOG END TAG zYx                                              

Summary: SDK Libraries and Examples Structure Overview

Target: Not Applicable

Description:

        The SDK Libraries and Examples RPMs have been partitioned into 
        the following subcomponents. This README provides a list of the 
        rpm packages, the directory locations (within the install packages)
        and brief description of the contents. Each rpm listed contains a
        tar file that contains the source code. That source can either be 
        expanded under /opt/cell/sdk/src, or can be expanded by a user into a
        local sandbox.

        cell-libs-source-3.0-#.noarch.rpm
                              Series of libraries and reusable header 
                              files. These are exported to $SDKLIB_<target>
                              or $SDKINC_<target> directories (respectively). 
                              Complete documentation for all library functions 
                              and header files is available in 
                              /opt/cell/sdk/docs/libraries_SDK.pdf.


        cell-demos-source-3.0-#.noarch.rpm
        cell-examples-source-3.0-#.noarch.rpm
        cell-tutorial-source-3.0-#.noarch.rpm
                              Series of code examples and demos used to show
                              different aspects of the Cell SDK.


        The SDK Libraries and Samples contains standardized directory names 
        that reflect the cpu, function, or environment for which the code is 
        meant to run.

        CPU
           ppu          Code contained in a ppu directory is compiled
                        for execution on a PPU.
           ppu64        Code contained in a ppu64 directory is compiled
                        for execution on a PPU in comformance with the 
                        64-bit ABI.
           spu          Code contained in a spu directory is compiled
                        for execution on a SPU.


