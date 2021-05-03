PROJECT(ConstrainedIK_Group)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)
CMAKE_POLICY(VERSION 2.6)

#SET(CMAKE_CXX_FLAGS "-std=c++0x")
SET(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

GET_FILENAME_COMPONENT (CurrentPath ${CMAKE_CURRENT_LIST_FILE} PATH)

# search for simox
FIND_PACKAGE(Simox REQUIRED)

SET(DEMO_BASE_DIR ${PROJECT_SOURCE_DIR})
ADD_DEFINITIONS(-DDEMO_BASE_DIR="${DEMO_BASE_DIR}")

IF(Simox_USE_COIN_VISUALIZATION)

        FILE(GLOB demo_SRCS 
            ${PROJECT_SOURCE_DIR}/ConstrainedIK.cpp
            ${PROJECT_SOURCE_DIR}/ConstrainedIKWindow.cpp
            ${PROJECT_SOURCE_DIR}/MySingleConstraintIK.cpp
            ${PROJECT_SOURCE_DIR}/MyDualConstraintIK.cpp
            ${PROJECT_SOURCE_DIR}/MyCustomConstraint.cpp
        )

        FILE(GLOB demo_INCS 
            ${PROJECT_SOURCE_DIR}/ConstrainedIKWindow.h
            ${PROJECT_SOURCE_DIR}/MySingleConstraintIK.h
            ${PROJECT_SOURCE_DIR}/MyDualConstraintIK.h
            ${PROJECT_SOURCE_DIR}/MyCustomConstraint.h
            ${PROJECT_SOURCE_DIR}/SolutionSwitch.h
        )



    ################################## moc'ing ##############################
    set(mocFiles
        ${PROJECT_SOURCE_DIR}/ConstrainedIKWindow.h
    )

    set(uiFiles
        ${PROJECT_SOURCE_DIR}/ConstrainedIK.ui
    )

    add_definitions( -DDEMO_PATH=\"${PROJECT_SOURCE_DIR}\" )

    # create the executable
    SimoxQtApplication(${PROJECT_NAME} "${demo_SRCS}" "${demo_INCS}" "${mocFiles}" "${uiFiles}")
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} Saba VirtualRobot)
ENDIF()
