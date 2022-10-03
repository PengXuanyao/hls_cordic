############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordic
set_top cordic
add_files src/cordic.cpp
add_files -tb src/mysin.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src/mycos.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src/myalpha.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src/cordic_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "s_pipeline" -flow_target vivado
set_part {xc7z010-clg400-1}
create_clock -period 10 -name default
source "./cordic/s_pipeline/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -format ip_catalog
