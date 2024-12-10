# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/signal_processors
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/benchmarks/phy/upper/signal_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(dmrs_pdsch_processor_benchmark "dmrs_pdsch_processor_benchmark" "-D" "-s" "-R" "1")
set_tests_properties(dmrs_pdsch_processor_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/signal_processors/CMakeLists.txt;28;add_test;/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/signal_processors/CMakeLists.txt;0;")
add_test(srs_estimator_benchmark "srs_estimator_benchmark" "-D" "-s" "-R" "1")
set_tests_properties(srs_estimator_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/signal_processors/CMakeLists.txt;38;add_test;/home/seoyul/srsRAN_Projects/tests/benchmarks/phy/upper/signal_processors/CMakeLists.txt;0;")
