# 1. Define the executable name
# This is what the students will run (e.g., Task-5.exe)
add_executable(Task-6 main.cpp
    Classes/TBankAccount.h
    Classes/TBankAccount.cpp
        Classes/TSort.cpp
        Classes/TSort.h
        Classes/TLinkedList.cpp
        Classes/TLinkedList.h
        Classes/EBankAccountType.h)

# 2. Link the Common Library
# This command connects the executable to your StructureReader code.
# Because we used 'PUBLIC' in the reader's setup, Task-6 
# automatically knows where to find "StructureReaderLib.h".
target_link_libraries(Task-6 PRIVATE StructureReader DebugUtils)

# 3. Handle the Data Files (The "Structure" folder) use excaped quotes to be Linux friendly
target_compile_definitions(Task-6 PRIVATE STRUCTURE_DIR=\"${STRUCTURE_PATH}\")