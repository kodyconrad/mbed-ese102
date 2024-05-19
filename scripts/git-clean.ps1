# Navigate to the parent directory of the script, which is the root of your git project
Set-Location -Path (Join-Path -Path $PSScriptRoot -ChildPath "..")

# Reset the head of the project
git reset --hard HEAD

# Clean up all files not in the head of the project
# The 'clean' command removes untracked files from your working directory
# The '-d' option tells it to remove untracked directories as well
# The '-x' option tells it to also remove files ignored by git
# The '-e !mbed-os/' option tells it to exclude the 'mbed-os' directory
git clean -d -x -e '!mbed-os/' -e '!.vscode/' -f
