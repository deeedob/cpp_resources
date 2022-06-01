cmake_minimum_required(VERSION 3.2)
set(DIR_NAME "${DIR_NAME}_Behavioral-Patterns")

add_executable(${DIR_NAME}Transition-Table State-Machine/transition_table.cpp)
add_executable(${DIR_NAME}State-Abstract State-Machine/abstract_state.cpp)
add_executable(${DIR_NAME}Observer Observer/observer.cpp)