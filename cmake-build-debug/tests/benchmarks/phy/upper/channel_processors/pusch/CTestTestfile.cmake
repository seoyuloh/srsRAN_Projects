# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/channel_processors/pusch
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/benchmarks/phy/upper/channel_processors/pusch
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pusch_processor_benchmark "pusch_processor_benchmark" "-m" "silent" "-R" "1" "-B" "1" "-T" "2" "-P" "scs15_5MHz_qpsk_rv0_1port_1layer")
set_tests_properties(pusch_processor_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/channel_processors/pusch/CMakeLists.txt;54;add_test;/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/channel_processors/pusch/CMakeLists.txt;0;")
