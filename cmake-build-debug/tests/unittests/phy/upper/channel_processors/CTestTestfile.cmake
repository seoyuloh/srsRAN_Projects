# CMake generated Testfile for 
# Source directory: /home/seoyul/srsRAN_Projects/tests/unittests/phy/upper/channel_processors
# Build directory: /home/seoyul/srsRAN_Projects/cmake-build-debug/tests/unittests/phy/upper/channel_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pdcch_processor_unittest "pdcch_processor_unittest")
set_tests_properties(pdcch_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;33;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(ssb_processor_unittest "ssb_processor_unittest")
set_tests_properties(ssb_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/seoyul/srsRAN_Projects/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;37;add_test;/home/seoyul/srsRAN_Projects/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
subdirs("pdsch")
subdirs("pucch")
subdirs("pusch")
subdirs("uci")
set_directory_properties(PROPERTIES LABELS "phy")
