
execute_process(
COMMAND git rev-parse --abbrev-ref HEAD
WORKING_DIRECTORY "/home/seoyul/srsRAN_Projects"
OUTPUT_VARIABLE GIT_BRANCH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
COMMAND git log -1 --format=%h
WORKING_DIRECTORY "/home/seoyul/srsRAN_Projects"
OUTPUT_VARIABLE GIT_COMMIT_HASH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Generating build information")
configure_file(
  /home/seoyul/srsRAN_Projects/lib/support/versioning/hashes.h.in
  /home/seoyul/srsRAN_Projects/cmake-build-debug/hashes.h
)
