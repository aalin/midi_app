cmake_minimum_required(VERSION 2.6)
project(midi_app)

set(CAMKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra")

find_library(COREFOUNDATION CoreFoundation "/")
find_library(COREMIDI CoreMidi "/")
find_library(CORESERVICES CoreServices "/")
find_library(PTHREAD pthread "/")


set(MAIN_SOURCES
	main
	midi_app
	bcr2000
	midi_event
	event_queue
	pattern
	player

	note_generators/drummer
)

add_executable(midi_app ${MAIN_SOURCES})
target_link_libraries(midi_app ${COREFOUNDATION} ${COREMIDI} ${CORESERVICES} ${PTHREAD})
