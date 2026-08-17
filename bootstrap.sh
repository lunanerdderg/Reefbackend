#!/bin/sh

# Make sure all commands are installed
listOfCommands="echo cd mv curl git cmake ctest"
for command in $listOfCommands; do
  if ! type "$command" > /dev/null; then
    echo "ERROR: '$command' is not installed."
    exit 1
  fi
done
ldconfigVar="true"
if ! type "ldconfig" > /dev/null; then
    ldconfigVar="false"
    echo
    echo "'ldconfig' is not installed. After the program is finished running, please update your symlinks and shared library cache manually, or install ldconfig."
fi


# Commands
# # First "cd" into the Reefback directory
# # CPR
echo
echo "Install CPR library"
git clone https://github.com/lunanerdderg/cpr-capture.git
mv cpr-capture cpr
cd cpr && mkdir build && cd build
cmake .. -DCPR_BUILD_TESTS=ON
cmake --build . --parallel
ctest -VV

# # ldconfig
if [ "$ldconfigVar" = "true" ]; then
  echo
  echo "Update libraries + symlinks systemwide. (If you do not wish to do this, you can safely terminate the program now. 'ldconfig' runs with sudo permissions)"
  sudo ldconfig
fi
echo
echo "Done!"

# Instructions:
# # Right-click Reefbackend in "Projects" sidebar and click "Build options..."
# # Go to "Linker settings" and add "/usr/local/lib/libcpr.so"
