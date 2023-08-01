# CMakeList.txt: проект CMake для SLAE_resolving; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (SLAE_solving "SLAE_solving.cpp" "SLAE_solving.h"  "MatrixOperations.h" "Rand_single_or_double.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SLAE_solving PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
