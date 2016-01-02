
# get header to show in project
#FILE(GLOB_RECURSE LibFiles "include/*.h")
FILE(GLOB_RECURSE LibFiles "*.h")
add_custom_target(headers SOURCES ${LibFiles})



