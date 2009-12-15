cmake_minimum_required(VERSION 2.6)
project(midi_app)

set(CAMKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra")

find_library(COREFOUNDATION CoreFoundation "/")
find_library(COREMIDI CoreMidi "/")
find_library(CORESERVICES CoreServices "/")
find_library(PTHREAD pthread "/")
find_package(BOOST)

include_directories(${BOOST_INCLUDE_DIRS})

set(MAIN_SOURCES
	main
	midi_app
	bcr2000
	midi_event
	event_queue
	pattern
	player
	scale

	note_generators/drummer
	note_generators/scale_player
)

add_executable(MidiApp ${MAIN_SOURCES})
target_link_libraries(MidiApp ${COREFOUNDATION} ${COREMIDI} ${CORESERVICES} ${PTHREAD})
