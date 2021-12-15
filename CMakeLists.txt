# CMakeList.txt: проект CMake для FolderSyncCMakeVS; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)

project ("FolderSync")

# Добавьте источник в исполняемый файл этого проекта.

add_executable (FolderSync main.cpp
			foldSync.cpp
			foldSync.h
		)

set_property(TARGET FolderSyncCMakeVS PROPERTY CXX_STANDARD 20)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
