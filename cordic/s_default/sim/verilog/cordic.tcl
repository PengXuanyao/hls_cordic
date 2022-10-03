
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set cos_out_group [add_wave_group cos_out(wire) -into $coutputgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/cos_out_ap_vld -into $cos_out_group -color #ffff00 -radix hex
add_wave /apatb_cordic_top/AESL_inst_cordic/cos_out -into $cos_out_group -radix hex
set sin_out_group [add_wave_group sin_out(wire) -into $coutputgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/sin_out_ap_vld -into $sin_out_group -color #ffff00 -radix hex
add_wave /apatb_cordic_top/AESL_inst_cordic/sin_out -into $sin_out_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set full_alpha_group [add_wave_group full_alpha(wire) -into $cinputgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/full_alpha -into $full_alpha_group -radix hex
set blocksiggroup [add_wave_group "Block-level IO Handshake" -into $designtopgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_start -into $blocksiggroup
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_done -into $blocksiggroup
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_idle -into $blocksiggroup
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_ready -into $blocksiggroup
set resetgroup [add_wave_group "Reset" -into $designtopgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_rst -into $resetgroup
set clockgroup [add_wave_group "Clock" -into $designtopgroup]
add_wave /apatb_cordic_top/AESL_inst_cordic/ap_clk -into $clockgroup
set testbenchgroup [add_wave_group "Test Bench Signals"]
set tbinternalsiggroup [add_wave_group "Internal Signals" -into $testbenchgroup]
set tb_simstatus_group [add_wave_group "Simulation Status" -into $tbinternalsiggroup]
set tb_portdepth_group [add_wave_group "Port Depth" -into $tbinternalsiggroup]
add_wave /apatb_cordic_top/AUTOTB_TRANSACTION_NUM -into $tb_simstatus_group -radix hex
add_wave /apatb_cordic_top/ready_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_cordic_top/done_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_cordic_top/LENGTH_full_alpha -into $tb_portdepth_group -radix hex
add_wave /apatb_cordic_top/LENGTH_sin_out -into $tb_portdepth_group -radix hex
add_wave /apatb_cordic_top/LENGTH_cos_out -into $tb_portdepth_group -radix hex
set tbcoutputgroup [add_wave_group "C Outputs" -into $testbenchgroup]
set tb_cos_out_group [add_wave_group cos_out(wire) -into $tbcoutputgroup]
add_wave /apatb_cordic_top/cos_out_ap_vld -into $tb_cos_out_group -color #ffff00 -radix hex
add_wave /apatb_cordic_top/cos_out -into $tb_cos_out_group -radix hex
set tb_sin_out_group [add_wave_group sin_out(wire) -into $tbcoutputgroup]
add_wave /apatb_cordic_top/sin_out_ap_vld -into $tb_sin_out_group -color #ffff00 -radix hex
add_wave /apatb_cordic_top/sin_out -into $tb_sin_out_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_full_alpha_group [add_wave_group full_alpha(wire) -into $tbcinputgroup]
add_wave /apatb_cordic_top/full_alpha -into $tb_full_alpha_group -radix hex
save_wave_config cordic.wcfg
run all
quit

